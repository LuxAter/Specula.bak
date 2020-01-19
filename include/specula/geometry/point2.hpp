#ifndef SPECULA_MATH_POINT2_HPP_
#define SPECULA_MATH_POINT2_HPP_

#include <cmath>
#include <cstdlib>

#include "../compiler.hpp"
#include "../preprocessor.hpp"

#include "vector2.hpp"

namespace specula {
template <typename T> struct Point2 {
  typedef T value_type;
  typedef std::size_t size_type;

  Point2() : x(), y() {}
  template <typename U>
  explicit Point2(const Point2<U> &p)
      : x(static_cast<T>(p.x)), y(static_cast<T>(p.y)) {}
  template <typename U>
  Point2(U x, U y) : x(static_cast<T>(x)), y(static_cast<T>(y)) {}
  template <typename U>
  explicit Point2(const Vector2<U> &v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {}

  template <typename U> explicit operator Vector2<U>() const {
    return Vector2<U>(static_cast<U>(x), static_cast<U>(y));
  }

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

  template <typename U> SPECULA_CONSTEXPR Point2<T> &operator+=(U s) {
    x += static_cast<T>(s);
    y += static_cast<T>(s);
    return *this;
  }
  template <typename U>
  SPECULA_CONSTEXPR Point2<T> &operator+=(const Point2<U> &v) {
    x += static_cast<T>(v.x);
    y += static_cast<T>(v.y);
    return *this;
  }
  template <typename U> SPECULA_CONSTEXPR Point2<T> &operator-=(U s) {
    x -= static_cast<T>(s);
    y -= static_cast<T>(s);
    return *this;
  }
  template <typename U>
  SPECULA_CONSTEXPR Point2<T> &operator-=(const Point2<U> &v) {
    x -= static_cast<T>(v.x);
    y -= static_cast<T>(v.y);
    return *this;
  }
  template <typename U> SPECULA_CONSTEXPR Point2<T> &operator*=(U s) {
    x *= static_cast<T>(s);
    y *= static_cast<T>(s);
    return *this;
  }
  template <typename U>
  SPECULA_CONSTEXPR Point2<T> &operator*=(const Point2<U> &v) {
    x *= static_cast<T>(v.x);
    y *= static_cast<T>(v.y);
    return *this;
  }
  template <typename U> SPECULA_CONSTEXPR Point2<T> &operator/=(U s) {
    x /= static_cast<T>(s);
    y /= static_cast<T>(s);
    return *this;
  }
  template <typename U>
  SPECULA_CONSTEXPR Point2<T> &operator/=(const Point2<U> &v) {
    x /= static_cast<T>(v.x);
    y /= static_cast<T>(v.y);
    return *this;
  }

  template <typename U>
  SPECULA_CONSTEXPR Point2<T> &operator+=(const Vector2<U> &v) {
    x += static_cast<T>(v.x);
    y += static_cast<T>(v.y);
    return *this;
  }
  template <typename U>
  SPECULA_CONSTEXPR Point2<T> &operator-=(const Vector2<U> &v) {
    x -= static_cast<T>(v.x);
    y -= static_cast<T>(v.y);
    return *this;
  }

  T x, y;
};

typedef Point2<Float> Point2f;
typedef Point2<Int> Point2i;

template <typename T>
Vector2<T>::Vector2(const Point2<T> &p) : x(p.x), y(p.y) {}

template <typename T>
SPECULA_CONSTEXPR Point2<T> operator-(const Point2<T> &v) {
  return Point2<T>(-v.x, -v.y);
}

template <typename T>
SPECULA_CONSTEXPR Point2<T> operator+(const Point2<T> &v, T s) {
  return Point2<T>(v.x + s, v.y + s);
}
template <typename T>
SPECULA_CONSTEXPR Point2<T> operator+(T s, const Point2<T> &v) {
  return Point2<T>(s + v.x, s + v.y);
}
template <typename T>
SPECULA_CONSTEXPR Point2<T> operator+(const Point2<T> &v1,
                                      const Point2<T> &v2) {
  return Point2<T>(v1.x + v2.x, v1.y + v2.y);
}
template <typename T, typename U>
SPECULA_CONSTEXPR Point2<T> operator+(const Point2<T> &p, const Vector2<T> &v) {
  return Point2<T>(p.x + static_cast<T>(v.x), p.y + static_cast<T>(v.y));
}

template <typename T>
SPECULA_CONSTEXPR Point2<T> operator-(const Point2<T> &v, T s) {
  return Point2<T>(v.x - s, v.y - s);
}
template <typename T>
SPECULA_CONSTEXPR Point2<T> operator-(T s, const Point2<T> &v) {
  return Point2<T>(s - v.x, s - v.y);
}
template <typename T>
SPECULA_CONSTEXPR Vector2<T> operator-(const Point2<T> &v1,
                                       const Point2<T> &v2) {
  return Vector2<T>(v1.x - v2.x, v1.y - v2.y);
}
template <typename T, typename U>
SPECULA_CONSTEXPR Point2<T> operator-(const Point2<T> &p, const Vector2<T> &v) {
  return Point2<T>(p.x - static_cast<T>(v.x), p.y - static_cast<T>(v.y));
}

template <typename T>
SPECULA_CONSTEXPR Point2<T> operator*(const Point2<T> &v, T s) {
  return Point2<T>(v.x * s, v.y * s);
}
template <typename T>
SPECULA_CONSTEXPR Point2<T> operator*(T s, const Point2<T> &v) {
  return Point2<T>(s * v.x, s * v.y);
}
template <typename T>
SPECULA_CONSTEXPR Point2<T> operator*(const Point2<T> &v1,
                                      const Point2<T> &v2) {
  return Point2<T>(v1.x * v2.x, v1.y * v2.y);
}

template <typename T>
SPECULA_CONSTEXPR Point2<T> operator/(const Point2<T> &v, T s) {
  return Point2<T>(v.x / s, v.y / s);
}
template <typename T>
SPECULA_CONSTEXPR Point2<T> operator/(T s, const Point2<T> &v) {
  return Point2<T>(s / v.x, s / v.y);
}
template <typename T>
SPECULA_CONSTEXPR Point2<T> operator/(const Point2<T> &v1,
                                      const Point2<T> &v2) {
  return Point2<T>(v1.x / v2.x, v1.y / v2.y);
}

template <typename T>
SPECULA_CONSTEXPR bool operator==(const Point2<T> &v1, const Point2<T> &v2) {
  return v1.x == v2.x && v1.y == v2.y;
}
template <typename T>
SPECULA_CONSTEXPR bool operator!=(const Point2<T> &v1, const Point2<T> &v2) {
  return v1.x != v2.x || v1.y != v2.y;
}
} // namespace specula

#endif // SPECULA_MATH_POINT2_HPP_
