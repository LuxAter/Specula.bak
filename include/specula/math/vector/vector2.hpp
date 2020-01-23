#ifndef SPECULA_VECTOR_VECTOR2_HPP_
#define SPECULA_VECTOR_VECTOR2_HPP_

#include <cmath>
#include <memory>
#include <stdexcept>

#include "../../compiler.hpp"
#include "../../fmt.hpp"
#include "../../types.hpp"

namespace specula {
template <typename T> class Vector2 {
public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef std::ptrdiff_t difference_type;
  typedef std::size_t size_type;

  Vector2() SPECULA_NOEXCEPT : x(), y() {}
  Vector2(const T &x, const T &y) SPECULA_NOEXCEPT : x(x), y(y) {}
  Vector2(const Vector2 &v) SPECULA_NOEXCEPT : x(v.x), y(v.y) {}
  ~Vector2() SPECULA_NOEXCEPT {}

  Vector2 &operator=(const Vector2 &v) SPECULA_NOEXCEPT {
    x = v.x;
    y = v.y;
    return *this;
  }

  bool operator==(const Vector2 &v) const SPECULA_NOEXCEPT {
    return x == v.x && y == v.y;
  }
  bool operator!=(const Vector2 &v) const SPECULA_NOEXCEPT {
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
          "specula::Vector2::_M_range_check: __n (which is " +
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
          "specula::Vector2::_M_range_check: __n (which is " +
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
          "specula::Vector2::_M_range_check: __n (which is " +
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
          "specula::Vector2::_M_range_check: __n (which is " +
          std::to_string(i) + ") >= this->size() (which is " +
          std::to_string(this->size()) + ")");
    }
  }

  void clear() SPECULA_NOEXCEPT { x = y = T(); }

  void swap(Vector2 &v) SPECULA_NOEXCEPT {
    std::swap(x, v.x);
    std::swap(y, v.y);
  }
  SPECULA_CONSTEXPR size_type size() const SPECULA_NOEXCEPT { return 2; }

  Vector2<T> operator+(const T &s) const SPECULA_NOEXCEPT {
    return Vector2<T>(x + s, y + s);
  }
  Vector2<T> operator+(const Vector2<T> &v) const SPECULA_NOEXCEPT {
    return Vector2<T>(x + v.x, y + v.y);
  }
  Vector2<T> &operator+=(const T &s) SPECULA_NOEXCEPT {
    x += s;
    y += s;
    return *this;
  }
  Vector2<T> &operator+=(const Vector2<T> &v) SPECULA_NOEXCEPT {
    x += v.x;
    y += v.y;
    return *this;
  }
  Vector2<T> operator-(const T &s) const SPECULA_NOEXCEPT {
    return Vector2<T>(x - s, y - s);
  }
  Vector2<T> operator-(const Vector2<T> &v) const SPECULA_NOEXCEPT {
    return Vector2<T>(x - v.x, y - v.y);
  }
  Vector2<T> &operator-=(const T &s) SPECULA_NOEXCEPT {
    x -= s;
    y -= s;
    return *this;
  }
  Vector2<T> &operator-=(const Vector2<T> &v) SPECULA_NOEXCEPT {
    x -= v.x;
    y -= v.y;
    return *this;
  }
  Vector2<T> operator*(const T &s) const SPECULA_NOEXCEPT {
    return Vector2<T>(x * s, y * s);
  }
  Vector2<T> operator*(const Vector2<T> &v) const SPECULA_NOEXCEPT {
    return Vector2<T>(x * v.x, y * v.y);
  }
  Vector2<T> &operator*=(const T &s) SPECULA_NOEXCEPT {
    x *= s;
    y *= s;
    return *this;
  }
  Vector2<T> &operator*=(const Vector2<T> &v) SPECULA_NOEXCEPT {
    x *= v.x;
    y *= v.y;
    return *this;
  }
  Vector2<T> operator/(const T &s) const SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    return Vector2<T>(x * inv, y * inv);
  }
  Vector2<T> operator/(const Vector2<T> &v) const SPECULA_NOEXCEPT {
    return Vector2<T>(x / v.x, y / v.y);
  }
  Vector2<T> &operator/=(const T &s) SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    x *= inv;
    y *= inv;
    return *this;
  }
  Vector2<T> &operator/=(const Vector2<T> &v) SPECULA_NOEXCEPT {
    x /= v.x;
    y /= v.y;
    return *this;
  }
  Vector2<T> operator-() const SPECULA_NOEXCEPT { return Vector2<T>(-x, -y); }

  std::string fmt() const { return fmt::format("<{},{}>", x, y); }

  T length_squared() const { return x * x + y * y; }
  T length() const { return std::sqrt(length_squared()); }

  T x, y;
};

typedef Vector2<Float> Vector2f;
typedef Vector2<Int> Vector2i;

template <typename T, typename U>
inline Vector2<T> operator*(U s, const Vector2<T> &v) {
  return v * s;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const Vector2<T> &v) {
  return out << v.fmt();
}
} // namespace specula

#endif // SPECULA_VECTOR_VECTOR2_HPP_
