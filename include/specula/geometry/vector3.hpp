/**
 * @file vector3.hpp
 * @brief Vector 3 definitions and operations
 * @version 0.1
 * @date 2020-01-20
 *
 * @copyright Copyright (c) 2020
 */
#ifndef SPECULA_MATH_VECTOR3_HPP_
#define SPECULA_MATH_VECTOR3_HPP_

#include <cmath>
#include <cstdlib>

#include "../compiler.hpp"
#include "../preprocessor.hpp"

namespace specula {
template <typename T> struct Point3;
template <typename T> struct Normal3;

/**
 * @brief Vector3 class
 *
 * @tparam T value type of elements
 * @ingroup Geometry
 */
template <typename T> struct Vector3 {
  typedef T value_type;
  typedef std::size_t size_type;

  Vector3() : x(), y(), z() {}
  template <typename U>
  Vector3(const Vector3<U> &v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z)) {
  }
  template <typename U>
  Vector3(U x, U y, U z)
      : x(static_cast<T>(x)), y(static_cast<T>(y)), z(static_cast<T>(z)) {}

  explicit Vector3(const Point3<T> &p);
  explicit Vector3(const Normal3<T> &n);

  static SPECULA_CONSTEXPR size_type size() { return 3; }

  T length_squared() const { return x * x + y * y + z * z; }
  T length() const { return std::sqrt(x * x + y * y + z * z); }

  SPECULA_CONSTEXPR T &operator[](size_type i) {
    SPECULA_ASSERT(i >= 0 && i <= this->size());
    switch (i) {
    default:
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    }
  }
  SPECULA_CONSTEXPR const T &operator[](size_type i) const {
    SPECULA_ASSERT(i >= 0 && i <= this->size());
    switch (i) {
    default:
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    }
  }

  template <typename U> SPECULA_CONSTEXPR Vector3<T> &operator+=(U s) {
    x += static_cast<T>(s);
    y += static_cast<T>(s);
    z += static_cast<T>(s);
    return *this;
  }
  template <typename U>
  SPECULA_CONSTEXPR Vector3<T> &operator+=(const Vector3<U> &v) {
    x += static_cast<T>(v.x);
    y += static_cast<T>(v.y);
    z += static_cast<T>(v.z);
    return *this;
  }
  template <typename U> SPECULA_CONSTEXPR Vector3<T> &operator-=(U s) {
    x -= static_cast<T>(s);
    y -= static_cast<T>(s);
    z -= static_cast<T>(s);
    return *this;
  }
  template <typename U>
  SPECULA_CONSTEXPR Vector3<T> &operator-=(const Vector3<U> &v) {
    x -= static_cast<T>(v.x);
    y -= static_cast<T>(v.y);
    z -= static_cast<T>(v.z);
    return *this;
  }
  template <typename U> SPECULA_CONSTEXPR Vector3<T> &operator*=(U s) {
    x *= static_cast<T>(s);
    y *= static_cast<T>(s);
    z *= static_cast<T>(s);
    return *this;
  }
  template <typename U>
  SPECULA_CONSTEXPR Vector3<T> &operator*=(const Vector3<U> &v) {
    x *= static_cast<T>(v.x);
    y *= static_cast<T>(v.y);
    z *= static_cast<T>(v.z);
    return *this;
  }
  template <typename U> SPECULA_CONSTEXPR Vector3<T> &operator/=(U s) {
    x /= static_cast<T>(s);
    y /= static_cast<T>(s);
    z /= static_cast<T>(s);
    return *this;
  }
  template <typename U>
  SPECULA_CONSTEXPR Vector3<T> &operator/=(const Vector3<U> &v) {
    x /= static_cast<T>(v.x);
    y /= static_cast<T>(v.y);
    z /= static_cast<T>(v.z);
    return *this;
  }

  T x, y, z;
};

typedef Vector3<Float> Vector3f;
typedef Vector3<Int> Vector3i;

template <typename T>
SPECULA_CONSTEXPR Vector3<T> operator-(const Vector3<T> &v) {
  return Vector3<T>(-v.x, -v.y, -v.z);
}

template <typename T>
SPECULA_CONSTEXPR Vector3<T> operator+(const Vector3<T> &v, T s) {
  return Vector3<T>(v.x + s, v.y + s, v.z + s);
}
template <typename T>
SPECULA_CONSTEXPR Vector3<T> operator+(T s, const Vector3<T> &v) {
  return Vector3<T>(s + v.x, s + v.y, s + v.z);
}
template <typename T>
SPECULA_CONSTEXPR Vector3<T> operator+(const Vector3<T> &v1,
                                       const Vector3<T> &v2) {
  return Vector3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

template <typename T>
SPECULA_CONSTEXPR Vector3<T> operator-(const Vector3<T> &v, T s) {
  return Vector3<T>(v.x - s, v.y - s, v.z - s);
}
template <typename T>
SPECULA_CONSTEXPR Vector3<T> operator-(T s, const Vector3<T> &v) {
  return Vector3<T>(s - v.x, s - v.y, s - v.z);
}
template <typename T>
SPECULA_CONSTEXPR Vector3<T> operator-(const Vector3<T> &v1,
                                       const Vector3<T> &v2) {
  return Vector3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

template <typename T>
SPECULA_CONSTEXPR Vector3<T> operator*(const Vector3<T> &v, T s) {
  return Vector3<T>(v.x * s, v.y * s, v.z * s);
}
template <typename T>
SPECULA_CONSTEXPR Vector3<T> operator*(T s, const Vector3<T> &v) {
  return Vector3<T>(s * v.x, s * v.y, s * v.z);
}
template <typename T>
SPECULA_CONSTEXPR Vector3<T> operator*(const Vector3<T> &v1,
                                       const Vector3<T> &v2) {
  return Vector3<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

template <typename T>
SPECULA_CONSTEXPR Vector3<T> operator/(const Vector3<T> &v, T s) {
  return Vector3<T>(v.x / s, v.y / s, v.z / s);
}
template <typename T>
SPECULA_CONSTEXPR Vector3<T> operator/(T s, const Vector3<T> &v) {
  return Vector3<T>(s / v.x, s / v.y, s / v.z);
}
template <typename T>
SPECULA_CONSTEXPR Vector3<T> operator/(const Vector3<T> &v1,
                                       const Vector3<T> &v2) {
  return Vector3<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

template <typename T>
SPECULA_CONSTEXPR bool operator==(const Vector3<T> &v1, const Vector3<T> &v2) {
  return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}
template <typename T>
SPECULA_CONSTEXPR bool operator!=(const Vector3<T> &v1, const Vector3<T> &v2) {
  return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z;
}
} // namespace specula

#endif // SPECULA_MATH_VECTOR3_HPP_
