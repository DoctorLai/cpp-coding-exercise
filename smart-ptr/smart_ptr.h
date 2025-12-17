#ifndef SMART_PTR_H
#define SMART_PTR_H

#include <type_traits>
#include "cpp_utility.h"
#include "ref_block_base.h"

// forwared declaration
template <typename T>
class SharedPtr;

template <typename T>
class WeakPtr;

template <typename T, typename... Args>
SharedPtr<T> MakeShared(Args&&... args);

template <typename T>
class SharedPtr {
    // allow weaktptr to access private
    friend class WeakPtr<T>;
    template<typename U, typename... Args>
    friend SharedPtr<U> MakeShared(Args&&... args);

private:
    T* m_ptr = nullptr;

    RefBlockBase* m_block = nullptr;

    //private construck for weakptr lock  and MakeShared
    SharedPtr(T* ptr, RefBlockBase* block) noexcept
        : m_ptr(ptr), m_block(block) {}

public:
    // --- construct func ---

    // default
    SharedPtr() noexcept = default;

    // accept rao ptr
    explicit SharedPtr(T* ptr)
        : SharedPtr(ptr, std::default_delete<T>()){

    }

    // construct from nullptr
    SharedPtr(std::nullptr_t) noexcept
        : SharedPtr(){}

    // core construct with deleter
    template <typename Y, typename D,
              typename = typename std::enable_if<
                  !std::is_convertible<typename std::decay<D>::type, RefBlockBase*>::value>::type>
    SharedPtr(Y* ptr, D&& deleter)
        : m_ptr(ptr){
        using DeleterType = typename std::decay<D>::type;
        DeleterType deleter_copy = utility::forward<D>(deleter);
        try{
            // try to allocate for control block
            m_block = new RefBlockImpl<Y, DeleterType>(ptr, deleter_copy);
        }catch(...){
            // if new refblockimpl fails, delete ptr and through error
            deleter_copy(ptr);
            throw;
        }
    }

    // move constructor
    SharedPtr(SharedPtr&& other) noexcept
        : m_ptr(other.m_ptr), m_block(other.m_block) {
        other.m_ptr = nullptr;
        other.m_block = nullptr;
    }

    // --- deconstructor ---
    ~SharedPtr() noexcept {
        if (m_block){
            m_block->decrement_shared();
        }
    }

    // --- copy control ---
    SharedPtr(const SharedPtr& other)
        : m_ptr(other.m_ptr), m_block(other.m_block){
        if(m_block){
            m_block -> increment_shared();
        }
    }

    SharedPtr& operator=(const SharedPtr& other){
        if(this != &other){
            // 1. release old resource
            if(m_block){
                m_block -> decrement_shared();
            }

            // 2. copy new resource
            m_ptr = other.m_ptr;
            m_block = other.m_block;

            if(m_block){
                m_block->increment_shared();
            }
        }
        return *this;
    }

    // move assignment operator
    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            // 1. Release current resources
            if (m_block) {
                m_block->decrement_shared();
            }

            // 2. Take ownership from other
            m_ptr = other.m_ptr;
            m_block = other.m_block;

            // 3. Null other's resources
            other.m_ptr = nullptr;
            other.m_block = nullptr;
        }
        return *this;
    }

    SharedPtr& operator=(std::nullptr_t){
        if(m_block){
            m_block->decrement_shared();
            m_block = nullptr;
            m_ptr = nullptr;
        }
        return *this;
    }

    T* get() const noexcept {return m_ptr;}

    T& operator*() const noexcept {return *m_ptr;}
    T* operator->() const noexcept {return m_ptr;}

    size_t use_count() const noexcept{
        return m_block ? m_block->m_shared_count.load() : 0;
    }

    explicit operator bool() const noexcept {return m_ptr != nullptr;}

};


template <typename T>
class WeakPtr {
private:
    // weak ptr can not safely holding T*, cause T can be destroyed any time
    RefBlockBase* m_block = nullptr;

public:
    // allow shared ptr to access
    friend class SharedPtr<T>;

    WeakPtr() noexcept = default;

    WeakPtr(const SharedPtr<T>& shared) noexcept
        : m_block(shared.m_block){
        if (m_block){
            m_block->increment_weak();
        }
    }

    ~WeakPtr() noexcept {
        if(m_block){
            m_block -> decrement_weak();
        }
    }


    bool expired() const noexcept {
        return !m_block || m_block -> m_shared_count.load(std::memory_order_acquire) == 0;
    }

    SharedPtr<T> lock() const noexcept{
        if(expired()){
            return SharedPtr<T>();
        }
        if (m_block -> try_increment_shared()){
            return SharedPtr<T>(reinterpret_cast<T*>(m_block->get_resource_ptr()), m_block);
        }else{
            return SharedPtr<T>();
        }
    }
};

template <typename T, typename... Args>
SharedPtr<T> MakeShared(Args&&... args){
    // allocate one time for space for T and RefBlock
    // allocate refblockmakeshared, which includes already size for T
    RefBlockMakeShared<T>* block = new RefBlockMakeShared<T>();

    void* void_ptr = block->get_resource_ptr();
    T* ptr = static_cast<T*>(void_ptr);

    // placement new to construct T on this address
    try {
        ::new (ptr) T(utility::forward<Args>(args)...);

    } catch (...){
        delete block;
        throw;
    }

    // use private constructor to return sharedptr
    return SharedPtr<T>(ptr, block);
}

#endif

