#ifndef VECTOR4_HEADER
#define VECTOR4_HEADER

#include <cmath>

template<typename T>
struct Vector4 {
    constexpr Vector4<T>();
    constexpr Vector4<T>(T x, T y, T z, T t = 1);
    constexpr Vector4<T>(const Vector4<T>&)            = default;
    constexpr Vector4<T>& operator=(const Vector4<T>&) = default;
    ~Vector4()                                         = default;

    T getLen() const;

    Vector4<T> unit() const;

    T x;
    T y;
    T z;
    T t;
};

using Vector4f = Vector4<float>   ;
using Vector4u = Vector4<unsigned>;
using Vector4d = Vector4<double>  ;
using Vector4i = Vector4<int>     ;

//*************************************************************

template <typename T>
inline constexpr  Vector4<T>::Vector4() :
    x(0), y(0), z(0), t(0)
{}

template <typename T>
inline constexpr Vector4<T>::Vector4(T x, T y, T z, T t) :
    x(x), y(y), z(z), t(t)
{}

//*************************************************************

template<typename T>
inline T Vector4<T>::getLen() const {
    return sqrt(x*x + y*y + z*z + t*t);
}

template<typename T>
inline Vector4<T> Vector4<T>::unit() const {
    T len = getLen();
    
    return (len == 0. ? Vector4<T>() : Vector4<T>(x / len, y / len, z / len, t / len));
}

//*************************************************************

template<typename T>
inline Vector4<T> operator-(const Vector4<T>& vector) {
    return Vector4<T>(-vector.x, -vector.y, -vector.z, -vector.t);
}

template<typename T>
inline Vector4<T>& operator+=(Vector4<T>& vector1, const Vector4<T>& vector2) {
    vector1.x += vector2.x;
    vector1.y += vector2.y;
    vector1.z += vector2.z;
    vector1.t += vector2.t;

    return vector1;
}

template<typename T>
inline Vector4<T>& operator-=(Vector4<T>& vector1, const Vector4<T>& vector2) {
    vector1.x -= vector2.x;
    vector1.y -= vector2.y;
    vector1.z -= vector2.z;
    vector1.t -= vector2.t;

    return vector1;
}

template<typename T>
inline Vector4<T>& operator*=(Vector4<T>& vector1, const Vector4<T>& vector2) {
    vector1.x *= vector2.x;
    vector1.y *= vector2.y;
    vector1.z *= vector2.z;
    vector1.t *= vector2.t;

    return vector1;
}

template<typename T>
inline Vector4<T>& operator*=(Vector4<T>& vector, T num) {
    vector.x *= num;
    vector.y *= num;
    vector.z *= num;
    vector.t *= num;

    return vector;
}

//*************************************************************

template<typename T>
inline Vector4<T> operator+(const Vector4<T>& vector1, const Vector4<T>& vector2) {
    return {vector1.x + vector2.x,
            vector1.y + vector2.y,
            vector1.z + vector2.z,
            vector1.t + vector2.t};
}

template<typename T>
inline Vector4<T> operator-(const Vector4<T>& vector1, const Vector4<T>& vector2) {
    return {vector1.x - vector2.x,
            vector1.y - vector2.y,
            vector1.z - vector2.z,
            vector1.t - vector2.t};
}

template<typename T>
inline Vector4<T> operator*(const Vector4<T>& vector1, const Vector4<T>& vector2) {
    return {vector1.x * vector2.x,
            vector1.z * vector2.z,
            vector1.y * vector2.y,
            vector1.t * vector2.t};
}

template<typename T>
inline Vector4<T> operator*(const Vector4<T>& vector, const T num) {
    return {vector.x * num,
            vector.y * num,
            vector.z * num,
            vector.t * num};
}

template<typename T>
inline Vector4<T> operator*(const T num, const Vector4<T>& vector) {
    return (vector * num);
}

//*************************************************************

template<typename T>
inline bool operator==(const Vector4<T>& vector1, const Vector4<T>& vector2) {
    return vector1.x == vector2.x &&
           vector1.y == vector2.y &&
           vector1.z == vector2.z &&
           vector1.t == vector2.t;
}

template<typename T>
inline bool operator!=(const Vector4<T>& vector1, const Vector4<T>& vector2) {
    return !(vector1 == vector2);
}

//*************************************************************

template<typename T>
inline T DotProduct(const Vector4<T>& vector1, const Vector4<T>& vector2) {
    return (vector1.x * vector2.x +
            vector1.y * vector2.y +
            vector1.z * vector2.z + 
            vector1.t * vector2.t);
}

#endif // VECTOR4_HEADER

