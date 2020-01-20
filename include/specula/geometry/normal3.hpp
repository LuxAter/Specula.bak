/**
 * @file normal3.hpp
 * @brief Normal3 definitions and operations
 * @version 0.1
 * @date 2020-01-20
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef SPECULA_MATH_NORMAL3_HPP_
#define SPECULA_MATH_NORMAL3_HPP_

#include <cmath>
#include <cstdlib>

#include "../compiler.hpp"
#include "../preprocessor.hpp"

#include "vector3.hpp"

namespace specula {
/**
 * @brief Normal3 class
 *
 * @tparam T value type of elements
 * @ingroup Geometry
 */
template <typename T> struct Normal3 {
  typedef T value_type;
  typedef std::size_t size_type;

  Normal3() : x(), y(), z() {}
  template <typename U>
  explicit Normal3(const Normal3<U> &n)
      : x(static_cast<T>(n.x)), y(static_cast<T>(n.y)), z(static_cast<T>(n.z)) {
  }
  template <typename U>
  explicit Normal3(const Vector3<U> &v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z)) {
  }
  template <typename U>
  Normal3(U x, U y, U z)
      : x(static_cast<T>(x)), y(static_cast<T>(y)), z(static_cast<T>(z)) {}

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

  template <typename U> SPECULA_CONSTEXPR Normal3<T> &operator+=(U s) {
    x += static_cast<T>(s);
    y += static_cast<T>(s);
    z += static_cast<T>(s);
    return *this;
  }
  template <typename U>
  SPECULA_CONSTEXPR Normal3<T> &operator+=(const Normal3<U> &v) {
    x += static_cast<T>(v.x);
    y += static_cast<T>(v.y);
    z += static_cast<T>(v.z);
    return *this;
  }
  template <typename U> SPECULA_CONSTEXPR Normal3<T> &operator-=(U s) {
    x -= static_cast<T>(s);
    y -= static_cast<T>(s);
    z -= static_cast<T>(s);
    return *this;
  }
  template <typename U>
  SPECULA_CONSTEXPR Normal3<T> &operator-=(const Normal3<U> &v) {
    x -= static_cast<T>(v.x);
    y -= static_cast<T>(v.y);
    z -= static_cast<T>(v.z);
    return *this;
  }
  template <typename U> SPECULA_CONSTEXPR Normal3<T> &operator*=(U s) {
    x *= static_cast<T>(s);
    y *= static_cast<T>(s);
    z *= static_cast<T>(s);
    return *this;
  }
  template <typename U>
  SPECULA_CONSTEXPR Normal3<T> &operator*=(const Normal3<U> &v) {
    x *= static_cast<T>(v.x);
    y *= static_cast<T>(v.y);
    z *= static_cast<T>(v.z);
    return *this;
  }
  template <typename U> SPECULA_CONSTEXPR Normal3<T> &operator/=(U s) {
    x /= static_cast<T>(s);
    y /= static_cast<T>(s);
    z /= static_cast<T>(s);
    return *this;
  }
  template <typename U>
  SPECULA_CONSTEXPR Normal3<T> &operator/=(const Normal3<U> &v) {
    x /= static_cast<T>(v.x);
    y /= static_cast<T>(v.y);
    z /= static_cast<T>(v.z);
    return *this;
  }

  T x, y, z;
};

typedef Normal3<Float> Normal3f;
typedef Normal3<Int> Normal3i;

template <typename T>
Vector3<T>::Vector3(const Normal3<T> &n) : x(n.x), y(n.y), z(n.z) {}

template <typename T>
SPECULA_CONSTEXPR Normal3<T> operator-(const Normal3<T> &v) {
  return Normal3<T>(-v.x, -v.y, -v.z);
}

template <typename T>
SPECULA_CONSTEXPR Normal3<T> operator+(const Normal3<T> &v, T s) {
  return Normal3<T>(v.x + s, v.y + s, v.z + s);
}
template <typename T>
SPECULA_CONSTEXPR Normal3<T> operator+(T s, const Normal3<T> &v) {
  return Normal3<T>(s + v.x, s + v.y, s + v.z);
}
template <typename T>
SPECULA_CONSTEXPR Normal3<T> operator+(const Normal3<T> &v1,
                                       const Normal3<T> &v2) {
  return Normal3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

template <typename T>
SPECULA_CONSTEXPR Normal3<T> operator-(const Normal3<T> &v, T s) {
  return Normal3<T>(v.x - s, v.y - s, v.z - s);
}
template <typename T>
SPECULA_CONSTEXPR Normal3<T> operator-(T s, const Normal3<T> &v) {
  return Normal3<T>(s - v.x, s - v.y, s - v.z);
}
template <typename T>
SPECULA_CONSTEXPR Normal3<T> operator-(const Normal3<T> &v1,
                                       const Normal3<T> &v2) {
  return Normal3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

template <typename T>
SPECULA_CONSTEXPR Normal3<T> operator*(const Normal3<T> &v, T s) {
  return Normal3<T>(v.x * s, v.y * s, v.z * s);
}
template <typename T>
SPECULA_CONSTEXPR Normal3<T> operator*(T s, const Normal3<T> &v) {
  return Normal3<T>(s * v.x, s * v.y, s * v.z);
}
template <typename T>
SPECULA_CONSTEXPR Normal3<T> operator*(const Normal3<T> &v1,
                                       const Normal3<T> &v2) {
  return Normal3<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

template <typename T>
SPECULA_CONSTEXPR Normal3<T> operator/(const Normal3<T> &v, T s) {
  return Normal3<T>(v.x / s, v.y / s, v.z / s);
}
template <typename T>
SPECULA_CONSTEXPR Normal3<T> operator/(T s, const Normal3<T> &v) {
  return Normal3<T>(s / v.x, s / v.y, s / v.z);
}
template <typename T>
SPECULA_CONSTEXPR Normal3<T> operator/(const Normal3<T> &v1,
                                       const Normal3<T> &v2) {
  return Normal3<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

template <typename T>
SPECULA_CONSTEXPR bool operator==(const Normal3<T> &v1, const Normal3<T> &v2) {
  return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}
template <typename T>
SPECULA_CONSTEXPR bool operator!=(const Normal3<T> &v1, const Normal3<T> &v2) {
  return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z;
}
} // namespace specula

#endif // SPECULA_MATH_NORMAL3_HPP_
