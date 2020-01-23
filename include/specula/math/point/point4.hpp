#ifndef SPECULA_POINT_POINT4_HPP_
#define SPECULA_POINT_POINT4_HPP_

#include <iostream>
#include <iterator>
#include <stdexcept>

#include "../../compiler.hpp"
#include "../../fmt.hpp"
#include "../../types.hpp"

#include "../vector/vector4.hpp"

namespace specula {
template <typename T> class Point4 {
public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  Point4() SPECULA_NOEXCEPT : x(), y(), z(), w() {}
  Point4(const T &v) SPECULA_NOEXCEPT : x(v), y(v), z(v), w(v) {}
  Point4(const T &x, const T &y, const T &z, const T &w) SPECULA_NOEXCEPT
      : x(x),
        y(y),
        z(z),
        w(w) {}
  Point4(const Point4 &v) SPECULA_NOEXCEPT : x(v.x), y(v.y), z(v.z), w(v.w) {}
  template <typename U>
  explicit Point4(const Vector4<U> &v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z)),
        w(static_cast<T>(v.w)) {}
  ~Point4() SPECULA_NOEXCEPT {}

  template <typename U> explicit operator Vector4<U>() const {
    return Vector4<U>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(z),
                      static_cast<U>(w));
  }

  Point4 &operator=(const Point4 &v) SPECULA_NOEXCEPT {
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
    return *this;
  }

  bool operator==(const Point4 &v) const SPECULA_NOEXCEPT {
    return x == v.x && y == v.y && z == v.z && w == v.w;
  }
  bool operator!=(const Point4 &v) const SPECULA_NOEXCEPT {
    return x != v.x || y != v.y || z != v.z || w != v.w;
  }

  reference operator[](size_type i) {
    switch (i) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    case 3:
      return w;
    default:
      throw std::out_of_range(
          "specula::Point4::_M_range_check: __n (which is " +
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
    case 2:
      return z;
    case 3:
      return w;
    default:
      throw std::out_of_range(
          "specula::Point4::_M_range_check: __n (which is " +
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
    case 2:
      return z;
    case 3:
      return w;
    default:
      throw std::out_of_range(
          "specula::Point4::_M_range_check: __n (which is " +
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
    case 2:
      return z;
    case 3:
      return w;
    default:
      throw std::out_of_range(
          "specula::Point4::_M_range_check: __n (which is " +
          std::to_string(i) + ") >= this->size() (which is " +
          std::to_string(this->size()) + ")");
    }
  }

  void clear() SPECULA_NOEXCEPT { x = y = z = w = T(); }

  void swap(Point4 &v) SPECULA_NOEXCEPT {
    std::swap(x, v.x);
    std::swap(y, v.y);
    std::swap(z, v.z);
    std::swap(w, v.w);
  }
  SPECULA_CONSTEXPR size_type size() const SPECULA_NOEXCEPT { return 4; }

  Point4<T> operator+(const T &s) const SPECULA_NOEXCEPT {
    return Point4<T>(x + s, y + s, z + s, w + s);
  }
  Point4<T> operator+(const Point4<T> &v) const SPECULA_NOEXCEPT {
    return Point4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
  }
  Point4<T> operator+(const Vector4<T> &v) const SPECULA_NOEXCEPT {
    return Point4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
  }
  Point4<T> &operator+=(const T &s) SPECULA_NOEXCEPT {
    x += s;
    y += s;
    z += s;
    w += s;
    return *this;
  }
  Point4<T> &operator+=(const Point4<T> &v) SPECULA_NOEXCEPT {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
  }
  Point4<T> &operator+=(const Vector4<T> &v) SPECULA_NOEXCEPT {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
  }
  Point4<T> operator-(const T &s) const SPECULA_NOEXCEPT {
    return Point4<T>(x - s, y - s, z - s, w - s);
  }
  Vector4<T> operator-(const Point4<T> &v) const SPECULA_NOEXCEPT {
    return Vector4<T>(x - v.x, y - v.y, z - v.z, w - v.w);
  }
  Point4<T> operator-(const Vector4<T> &v) const SPECULA_NOEXCEPT {
    return Point4<T>(x - v.x, y - v.y, z - v.z, w - v.w);
  }
  Point4<T> &operator-=(const T &s) SPECULA_NOEXCEPT {
    x -= s;
    y -= s;
    z -= s;
    w -= s;
    return *this;
  }
  Point4<T> operator*(const T &s) const SPECULA_NOEXCEPT {
    return Point4<T>(x * s, y * s, z * s, w * s);
  }
  Point4<T> operator*(const Point4<T> &v) const SPECULA_NOEXCEPT {
    return Point4<T>(x * v.x, y * v.y, z * v.z, w * v.w);
  }
  Point4<T> &operator*=(const T &s) SPECULA_NOEXCEPT {
    x *= s;
    y *= s;
    z *= s;
    w *= s;
    return *this;
  }
  Point4<T> &operator*=(const Point4<T> &v) SPECULA_NOEXCEPT {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
    return *this;
  }
  Point4<T> operator/(const T &s) const SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    return Point4<T>(x * inv, y * inv, z * inv, w * inv);
  }
  Point4<T> operator/(const Point4<T> &v) const SPECULA_NOEXCEPT {
    return Point4<T>(x / v.x, y / v.y, z / v.z, w / v.w);
  }
  Point4<T> &operator/=(const T &s) SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    x *= inv;
    y *= inv;
    z *= inv;
    w *= inv;
    return *this;
  }
  Point4<T> &operator/=(const Point4<T> &v) SPECULA_NOEXCEPT {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    w /= v.w;
    return *this;
  }

  Point4<T> operator-() const SPECULA_NOEXCEPT {
    return Point4<T>(-x, -y, -z, -w);
  }

  std::string fmt() const { return fmt::format("<{},{},{},{}>", x, y, z, w); }

  T x, y, z, w;
};

typedef Point4<Float> Point4f;
typedef Point4<Int> Point4i;

template <typename T>
std::ostream &operator<<(std::ostream &out, const Point4<T> &v) {
  return out << v.fmt();
}
} // namespace specula

#endif // SPECULA_POINT_POINT4_HPP_
