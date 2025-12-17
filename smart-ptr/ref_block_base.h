#ifndef REF_BLOCK_BASE_H
#define REF_BLOCK_BASE_H

#include <atomic>
#include <memory>
#include <functional>
#include <cstddef>

#include "cpp_utility.h"


struct RefBlockBase {
    // atomic operation
    std::atomic<size_t> m_shared_count{1};   // when init, create the shared_ptr and own it
    std::atomic<size_t> m_weak_count{1};    // when init, m_shared_count as one "weak reference"

    virtual ~RefBlockBase() = default;

    // type erasure
    virtual void dispose_resource() = 0;
    virtual void destroy_self() = 0;
    virtual void* get_resource_ptr() { return nullptr; }


    // ---- thread safe counter operation ----
    void increment_shared() noexcept{
        m_shared_count.fetch_add(1, std::memory_order_relaxed);
    }

    void increment_weak() noexcept{
        m_weak_count.fetch_add(1, std::memory_order_relaxed);
    }

    void decrement_shared() noexcept {
        // fetch_sub return the value before minus
        // use  acq_rel (Acquire-Release) ensure memory safe
        if(m_shared_count.fetch_sub(1, std::memory_order_acq_rel) == 1){
            dispose_resource();
            decrement_weak();
        }
    }

    void decrement_weak() noexcept{
        if (m_weak_count.fetch_sub(1, std::memory_order_acq_rel) == 1){
            // weak counter oges 0, destroy control block
            destroy_self();
        }
    }

    bool try_increment_shared() noexcept {
        size_t count = m_shared_count.load(std::memory_order_relaxed);

        while(count != 0){
            // try to replace count with count + 1
            if(m_shared_count.compare_exchange_weak(count, count + 1, std::memory_order_acq_rel)){
                return true; // success
            }
        }
        return false;
    }
};

// for 'new'
// Y is the actual type, D is the del type
template <typename Y, typename D>
struct RefBlockImpl : public RefBlockBase {
    Y* m_resource;
    D m_deleter;

    RefBlockImpl(Y* res, D del)
        : m_resource(res), m_deleter(utility::move(del)){}

    void dispose_resource() override {
        // call the deleter
        m_deleter(m_resource);
    }

    void destroy_self() override {
        // destroy self
        delete this;
    }
};

template <typename T>
struct RefBlockMakeShared : public RefBlockBase{
    // T's data will followed directly after this struct
    // use an aligned char array for padding
    alignas(T) char m_storage[sizeof(T)];

    void* get_resource_ptr() override{
        return reinterpret_cast<T*>(m_storage);
    }

    void dispose_resource() override {
        // call the deconstruct but not release the memory
        reinterpret_cast<T*>(m_storage) -> ~T();
    }

    void destroy_self() override{
        delete this;
    }
};

#endif

