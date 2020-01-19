#ifndef SPECULA_MATH_VECTOR2_HPP_
#define SPECULA_MATH_VECTOR2_HPP_

#include <cmath>
#include <cstdlib>

#include "../compiler.hpp"
#include "../preprocessor.hpp"

namespace specula {
template <typename T> struct Point2;
template <typename T> struct Point3;

template <typename T> struct Vector2 {
  typedef T value_type;
  typedef std::size_t size_type;

  Vector2() : x(), y() {}
  template <typename U>
  Vector2(const Vector2<U> &v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {}
  template <typename U>
  Vector2(U x, U y) : x(static_cast<T>(x)), y(static_cast<T>(y)) {}
  explicit Vector2(const Point2<T> &p);
  explicit Vector2(const Point3<T> &p);

  static SPECULA_CONSTEXPR size_type size() { return 2; }

  T length_squared() const { return x * x + y * y; }
  T length() const { return std::sqrt(x * x + y * y); }

  SPECULA_CONSTEXPR T &operator[](size_type i) {
    SPECULA_ASSERT(i >= 0 && i <= this->size());
    switch (i) {
    default:
    case 0:
      return x;
    case 1:
      return y;
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
    }
  }

  template <typename U> SPECULA_CONSTEXPR Vector2<T> &operator+=(U s) {
    x += static_cast<T>(s);
    y += static_cast<T>(s);
    return *this;
  }
  template <typename U>
  SPECULA_CONSTEXPR Vector2<T> &operator+=(const Vector2<U> &v) {
    x += static_cast<T>(v.x);
    y += static_cast<T>(v.y);
    return *this;
  }
  template <typename U> SPECULA_CONSTEXPR Vector2<T> &operator-=(U s) {
    x -= static_cast<T>(s);
    y -= static_cast<T>(s);
    return *this;
  }
  template <typename U>
  SPECULA_CONSTEXPR Vector2<T> &operator-=(const Vector2<U> &v) {
    x -= static_cast<T>(v.x);
    y -= static_cast<T>(v.y);
    return *this;
  }
  template <typename U> SPECULA_CONSTEXPR Vector2<T> &operator*=(U s) {
    x *= static_cast<T>(s);
    y *= static_cast<T>(s);
    return *this;
  }
  template <typename U>
  SPECULA_CONSTEXPR Vector2<T> &operator*=(const Vector2<U> &v) {
    x *= static_cast<T>(v.x);
    y *= static_cast<T>(v.y);
    return *this;
  }
  template <typename U> SPECULA_CONSTEXPR Vector2<T> &operator/=(U s) {
    x /= static_cast<T>(s);
    y /= static_cast<T>(s);
    return *this;
  }
  template <typename U>
  SPECULA_CONSTEXPR Vector2<T> &operator/=(const Vector2<U> &v) {
    x /= static_cast<T>(v.x);
    y /= static_cast<T>(v.y);
    return *this;
  }

  T x, y;
};

typedef Vector2<Float> Vector2f;
typedef Vector2<Int> Vector2i;

template <typename T>
SPECULA_CONSTEXPR Vector2<T> operator-(const Vector2<T> &v) {
  return Vector2<T>(-v.x, -v.y);
}

template <typename T>
SPECULA_CONSTEXPR Vector2<T> operator+(const Vector2<T> &v, T s) {
  return Vector2<T>(v.x + s, v.y + s);
}
template <typename T>
SPECULA_CONSTEXPR Vector2<T> operator+(T s, const Vector2<T> &v) {
  return Vector2<T>(s + v.x, s + v.y);
}
template <typename T>
SPECULA_CONSTEXPR Vector2<T> operator+(const Vector2<T> &v1,
                                       const Vector2<T> &v2) {
  return Vector2<T>(v1.x + v2.x, v1.y + v2.y);
}

template <typename T>
SPECULA_CONSTEXPR Vector2<T> operator-(const Vector2<T> &v, T s) {
  return Vector2<T>(v.x - s, v.y - s);
}
template <typename T>
SPECULA_CONSTEXPR Vector2<T> operator-(T s, const Vector2<T> &v) {
  return Vector2<T>(s - v.x, s - v.y);
}
template <typename T>
SPECULA_CONSTEXPR Vector2<T> operator-(const Vector2<T> &v1,
                                       const Vector2<T> &v2) {
  return Vector2<T>(v1.x - v2.x, v1.y - v2.y);
}

template <typename T>
SPECULA_CONSTEXPR Vector2<T> operator*(const Vector2<T> &v, T s) {
  return Vector2<T>(v.x * s, v.y * s);
}
template <typename T>
SPECULA_CONSTEXPR Vector2<T> operator*(T s, const Vector2<T> &v) {
  return Vector2<T>(s * v.x, s * v.y);
}
template <typename T>
SPECULA_CONSTEXPR Vector2<T> operator*(const Vector2<T> &v1,
                                       const Vector2<T> &v2) {
  return Vector2<T>(v1.x * v2.x, v1.y * v2.y);
}

template <typename T>
SPECULA_CONSTEXPR Vector2<T> operator/(const Vector2<T> &v, T s) {
  return Vector2<T>(v.x / s, v.y / s);
}
template <typename T>
SPECULA_CONSTEXPR Vector2<T> operator/(T s, const Vector2<T> &v) {
  return Vector2<T>(s / v.x, s / v.y);
}
template <typename T>
SPECULA_CONSTEXPR Vector2<T> operator/(const Vector2<T> &v1,
                                       const Vector2<T> &v2) {
  return Vector2<T>(v1.x / v2.x, v1.y / v2.y);
}

template <typename T>
SPECULA_CONSTEXPR bool operator==(const Vector2<T> &v1, const Vector2<T> &v2) {
  return v1.x == v2.x && v1.y == v2.y;
}
template <typename T>
SPECULA_CONSTEXPR bool operator!=(const Vector2<T> &v1, const Vector2<T> &v2) {
  return v1.x != v2.x || v1.y != v2.y;
}
} // namespace specula

#endif // SPECULA_MATH_VECTOR2_HPP_
