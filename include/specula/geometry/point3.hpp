#ifndef SPECULA_MATH_POINT3_HPP_
#define SPECULA_MATH_POINT3_HPP_

#include <cmath>
#include <cstdlib>

#include "../compiler.hpp"
#include "../preprocessor.hpp"

#include "vector2.hpp"
#include "vector3.hpp"

namespace specula {
template <typename T> struct Point3 {
  typedef T value_type;
  typedef std::size_t size_type;

  Point3() : x(), y(), z() {}
  template <typename U>
  explicit Point3(const Point3<T> &p)
      : x(static_cast<T>(p.x)), y(static_cast<T>(p.y)), z(static_cast<T>(p.z)) {
  }
  template <typename U>
  explicit Point3(const Vector3<T> &v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z)) {
  }
  template <typename U>
  Point3(U x, U y, U z)
      : x(static_cast<T>(x)), y(static_cast<T>(y)), z(static_cast<T>(z)) {}

  template <typename U> explicit operator Vector3<U>() const {
    return Vector3<U>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(z));
  }

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

  template <typename U> SPECULA_CONSTEXPR Point3<T> &operator+=(U s) {
    x += static_cast<T>(s);
    y += static_cast<T>(s);
    z += static_cast<T>(s);
    return *this;
  }
  template <typename U>
  SPECULA_CONSTEXPR Point3<T> &operator+=(const Point3<U> &v) {
    x += static_cast<T>(v.x);
    y += static_cast<T>(v.y);
    z += static_cast<T>(v.z);
    return *this;
  }
  template <typename U> SPECULA_CONSTEXPR Point3<T> &operator-=(U s) {
    x -= static_cast<T>(s);
    y -= static_cast<T>(s);
    z -= static_cast<T>(s);
    return *this;
  }
  template <typename U>
  SPECULA_CONSTEXPR Point3<T> &operator-=(const Point3<U> &v) {
    x -= static_cast<T>(v.x);
    y -= static_cast<T>(v.y);
    z -= static_cast<T>(v.z);
    return *this;
  }
  template <typename U> SPECULA_CONSTEXPR Point3<T> &operator*=(U s) {
    x *= static_cast<T>(s);
    y *= static_cast<T>(s);
    z *= static_cast<T>(s);
    return *this;
  }
  template <typename U>
  SPECULA_CONSTEXPR Point3<T> &operator*=(const Point3<U> &v) {
    x *= static_cast<T>(v.x);
    y *= static_cast<T>(v.y);
    z *= static_cast<T>(v.z);
    return *this;
  }
  template <typename U> SPECULA_CONSTEXPR Point3<T> &operator/=(U s) {
    x /= static_cast<T>(s);
    y /= static_cast<T>(s);
    z /= static_cast<T>(s);
    return *this;
  }
  template <typename U>
  SPECULA_CONSTEXPR Point3<T> &operator/=(const Point3<U> &v) {
    x /= static_cast<T>(v.x);
    y /= static_cast<T>(v.y);
    z /= static_cast<T>(v.z);
    return *this;
  }

  template <typename U>
  SPECULA_CONSTEXPR Point3<T> &operator+=(const Vector3<U> &v) {
    x += static_cast<T>(v.x);
    y += static_cast<T>(v.y);
    z += static_cast<T>(v.z);
    return *this;
  }
  template <typename U>
  SPECULA_CONSTEXPR Point3<T> &operator-=(const Vector3<U> &v) {
    x -= static_cast<T>(v.x);
    y -= static_cast<T>(v.y);
    z -= static_cast<T>(v.z);
    return *this;
  }

  T x, y, z;
};

template <typename T>
Vector2<T>::Vector2(const Point3<T> &p) : x(p.x), y(p.y) {}
template <typename T>
Vector3<T>::Vector3(const Point3<T> &p) : x(p.x), y(p.y), z(p.z) {}

template <typename T>
SPECULA_CONSTEXPR Point3<T> operator-(const Point3<T> &v) {
  return Point3<T>(-v.x, -v.y, -v.z);
}

template <typename T>
SPECULA_CONSTEXPR Point3<T> operator+(const Point3<T> &v, T s) {
  return Point3<T>(v.x + s, v.y + s, v.z + s);
}
template <typename T>
SPECULA_CONSTEXPR Point3<T> operator+(T s, const Point3<T> &v) {
  return Point3<T>(s + v.x, s + v.y, s + v.z);
}
template <typename T>
SPECULA_CONSTEXPR Point3<T> operator+(const Point3<T> &v1,
                                      const Point3<T> &v2) {
  return Point3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
template <typename T, typename U>
SPECULA_CONSTEXPR Point3<T> operator+(const Point3<T> &p, const Vector3<U> &v) {
  return Point3<T>(p.x + static_cast<T>(v.x), p.y + static_cast<T>(v.y),
                   p.z + static_cast<T>(v.z));
}

template <typename T>
SPECULA_CONSTEXPR Point3<T> operator-(const Point3<T> &v, T s) {
  return Point3<T>(v.x - s, v.y - s, v.z - s);
}
template <typename T>
SPECULA_CONSTEXPR Point3<T> operator-(T s, const Point3<T> &v) {
  return Point3<T>(s - v.x, s - v.y, s - v.z);
}
template <typename T>
SPECULA_CONSTEXPR Vector3<T> operator-(const Point3<T> &v1,
                                       const Point3<T> &v2) {
  return Vector3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}
template <typename T, typename U>
SPECULA_CONSTEXPR Point3<T> operator-(const Point3<T> &p, const Vector3<T> &v) {
  return Point2<T>(p.x - static_cast<T>(v.x), p.y - static_cast<T>(v.y),
                   p.z - static_cast<T>(v.z));
}

template <typename T>
SPECULA_CONSTEXPR Point3<T> operator*(const Point3<T> &v, T s) {
  return Point3<T>(v.x * s, v.y * s, v.z * s);
}
template <typename T>
SPECULA_CONSTEXPR Point3<T> operator*(T s, const Point3<T> &v) {
  return Point3<T>(s * v.x, s * v.y, s * v.z);
}
template <typename T>
SPECULA_CONSTEXPR Point3<T> operator*(const Point3<T> &v1,
                                      const Point3<T> &v2) {
  return Point3<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

template <typename T>
SPECULA_CONSTEXPR Point3<T> operator/(const Point3<T> &v, T s) {
  return Point3<T>(v.x / s, v.y / s, v.z / s);
}
template <typename T>
SPECULA_CONSTEXPR Point3<T> operator/(T s, const Point3<T> &v) {
  return Point3<T>(s / v.x, s / v.y, s / v.z);
}
template <typename T>
SPECULA_CONSTEXPR Point3<T> operator/(const Point3<T> &v1,
                                      const Point3<T> &v2) {
  return Point3<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

template <typename T>
SPECULA_CONSTEXPR bool operator==(const Point3<T> &v1, const Point3<T> &v2) {
  return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}
template <typename T>
SPECULA_CONSTEXPR bool operator!=(const Point3<T> &v1, const Point3<T> &v2) {
  return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z;
}
} // namespace specula

#endif // SPECULA_MATH_POINT3_HPP_
