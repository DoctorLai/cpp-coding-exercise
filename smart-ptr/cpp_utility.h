#ifndef CPP_UTILITY_H
#define CPP_UTILITY_H

namespace utility{

// remove_reference
template <class T> struct remove_reference {using type = T;};
template <class T> struct remove_reference<T&> {using type = T;};
template <class T> struct remove_reference<T&&> {using type = T;};


// move
template <class T>
constexpr typename remove_reference<T>::type&& move(T&& t) noexcept{
    return static_cast<typename remove_reference<T>::type&&>(t);
}


// forward (optional, for perfect forwarding)
template <class T>
constexpr T&& forward(typename remove_reference<T>::type& t) noexcept{
    return static_cast<T&&>(t);
}

template <class T>
constexpr T&& forward(typename remove_reference<T>::type&& t) noexcept{
    return static_cast<T&&>(t);
}

}

#endif //CPP_UTILITY_H