#pragma once

template <typename T>
struct remove_ref {
    using type = T;
};

template <typename T>
struct remove_ref<T&> {
    using type = T;
};

template <typename T>
struct remove_ref<T&&> {
    using type = T;
};

// cast to rval ref
template <typename T>
remove_ref<T>&& move(T&& val) {
    return static_cast<remove_ref<T>&&>(val);
}

// lval to lval ref, rval to rval ref
template <typename T>
T&& forward(T&& val) {
    
}
