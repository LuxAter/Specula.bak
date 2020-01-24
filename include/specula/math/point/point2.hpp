#ifndef SPECULA_POINT_POINT2_HPP_
#define SPECULA_POINT_POINT2_HPP_

#include <cmath>
#include <memory>
#include <stdexcept>

#include "../../global.hpp"

#include "../vector/vector2.hpp"

namespace specula {
template <typename T> class Point2 {
public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef std::ptrdiff_t difference_type;
  typedef std::size_t size_type;

  Point2() SPECULA_NOEXCEPT : x(), y() {}
  Point2(const T &v) SPECULA_NOEXCEPT : x(v), y(v) {}
  Point2(const T &x, const T &y) SPECULA_NOEXCEPT : x(x), y(y) {}
  Point2(const Point2 &v) SPECULA_NOEXCEPT : x(v.x), y(v.y) {}
  template <typename U>
  explicit Point2(const Vector2<U> &v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {}
  ~Point2() SPECULA_NOEXCEPT {}

  template <typename U> explicit operator Vector2<U>() const {
    return Vector2<U>(static_cast<U>(x), static_cast<U>(y));
  }

  Point2 &operator=(const Point2 &v) SPECULA_NOEXCEPT {
    x = v.x;
    y = v.y;
    return *this;
  }

  bool operator==(const Point2 &v) const SPECULA_NOEXCEPT {
    return x == v.x && y == v.y;
  }
  bool operator!=(const Point2 &v) const SPECULA_NOEXCEPT {
    return x != v.x || y != v.y;
  }

  reference operator[](size_type i) {
    switch (i) {
    case 0:
      return x;
    case 1:
      return y;
    default:
      throw std::out_of_range(
          "specula::Point2::_M_range_check: __n (which is " +
          std::to_string(i) + ") >= this->size() (which is " +
          std::to_string(this->size()) + ")");
    }
  }
  const_reference operator[](size_type i) const {
    switch (i) {
    case 0:
      return x;
    case 1:
      return y;
    default:
      throw std::out_of_range(
          "specula::Point2::_M_range_check: __n (which is " +
          std::to_string(i) + ") >= this->size() (which is " +
          std::to_string(this->size()) + ")");
    }
  }
  reference at(size_type i) {
    switch (i) {
    case 0:
      return x;
    case 1:
      return y;
    default:
      throw std::out_of_range(
          "specula::Point2::_M_range_check: __n (which is " +
          std::to_string(i) + ") >= this->size() (which is " +
          std::to_string(this->size()) + ")");
    }
  }
  const_reference at(size_type i) const {
    switch (i) {
    case 0:
      return x;
    case 1:
      return y;
    default:
      throw std::out_of_range(
          "specula::Point2::_M_range_check: __n (which is " +
          std::to_string(i) + ") >= this->size() (which is " +
          std::to_string(this->size()) + ")");
    }
  }

  void clear() SPECULA_NOEXCEPT { x = y = T(); }

  void swap(Point2 &v) SPECULA_NOEXCEPT {
    std::swap(x, v.x);
    std::swap(y, v.y);
  }
  SPECULA_CONSTEXPR size_type size() const SPECULA_NOEXCEPT { return 2; }

  Point2<T> operator+(const T &s) const SPECULA_NOEXCEPT {
    return Point2<T>(x + s, y + s);
  }
  Point2<T> operator+(const Point2<T> &v) const SPECULA_NOEXCEPT {
    return Point2<T>(x + v.x, y + v.y);
  }
  Point2<T> operator+(const Vector2<T> &v) const SPECULA_NOEXCEPT {
    return Point2<T>(x + v.x, y + v.y);
  }
  Point2<T> &operator+=(const T &s) SPECULA_NOEXCEPT {
    x += s;
    y += s;
    return *this;
  }
  Point2<T> &operator+=(const Point2<T> &v) SPECULA_NOEXCEPT {
    x += v.x;
    y += v.y;
    return *this;
  }
  Point2<T> &operator+=(const Vector2<T> &v) SPECULA_NOEXCEPT {
    x += v.x;
    y += v.y;
    return *this;
  }
  Point2<T> operator-(const T &s) const SPECULA_NOEXCEPT {
    return Point2<T>(x - s, y - s);
  }
  Vector2<T> operator-(const Point2<T> &v) const SPECULA_NOEXCEPT {
    return Vector2<T>(x - v.x, y - v.y);
  }
  Point2<T> operator-(const Vector2<T> &v) const SPECULA_NOEXCEPT {
    return Point2<T>(x - v.x, y - v.y);
  }
  Point2<T> &operator-=(const T &s) SPECULA_NOEXCEPT {
    x -= s;
    y -= s;
    return *this;
  }
  Point2<T> &operator-=(const Vector2<T> &v) SPECULA_NOEXCEPT {
    x -= v.x;
    y -= v.y;
    return *this;
  }
  Point2<T> operator*(const T &s) const SPECULA_NOEXCEPT {
    return Point2<T>(x * s, y * s);
  }
  Point2<T> operator*(const Point2<T> &v) const SPECULA_NOEXCEPT {
    return Point2<T>(x * v.x, y * v.y);
  }
  Point2<T> &operator*=(const T &s) SPECULA_NOEXCEPT {
    x *= s;
    y *= s;
    return *this;
  }
  Point2<T> &operator*=(const Point2<T> &v) SPECULA_NOEXCEPT {
    x *= v.x;
    y *= v.y;
    return *this;
  }
  Point2<T> operator/(const T &s) const SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    return Point2<T>(x * inv, y * inv);
  }
  Point2<T> operator/(const Point2<T> &v) const SPECULA_NOEXCEPT {
    return Point2<T>(x / v.x, y / v.y);
  }
  Point2<T> &operator/=(const T &s) SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    x *= inv;
    y *= inv;
    return *this;
  }
  Point2<T> &operator/=(const Point2<T> &v) SPECULA_NOEXCEPT {
    x /= v.x;
    y /= v.y;
    return *this;
  }
  Point2<T> operator-() const SPECULA_NOEXCEPT { return Point2<T>(-x, -y); }

  std::string fmt() const { return fmt::format("<{},{}>", x, y); }

  T x, y;
};

typedef Point2<Float> Point2f;
typedef Point2<Int> Point2i;

template <typename T>
std::ostream &operator<<(std::ostream &out, const Point2<T> &v) {
  return out << v.fmt();
}
} // namespace specula

#endif // SPECULA_POINT_POINT2_HPP_
