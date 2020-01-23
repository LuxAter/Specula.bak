#ifndef SPECULA_NORMAL_NORMAL2_HPP_
#define SPECULA_NORMAL_NORMAL2_HPP_

#include <cmath>
#include <memory>
#include <stdexcept>

#include "../../compiler.hpp"
#include "../../fmt.hpp"
#include "../../types.hpp"

#include "../vector/vector2.hpp"

namespace specula {
template <typename T> class Normal2 {
public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef std::ptrdiff_t difference_type;
  typedef std::size_t size_type;

  Normal2() SPECULA_NOEXCEPT : x(), y() {}
  Normal2(const T &x, const T &y) SPECULA_NOEXCEPT : x(x), y(y) {}
  Normal2(const Normal2 &v) SPECULA_NOEXCEPT : x(v.x), y(v.y) {}
  template <typename U>
  explicit Normal2(const Vector2<U> &v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {}
  ~Normal2() SPECULA_NOEXCEPT {}

  template <typename U> explicit operator Vector2<U>() const {
    return Vector2<U>(static_cast<U>(x), static_cast<U>(y));
  }

  Normal2 &operator=(const Normal2 &v) SPECULA_NOEXCEPT {
    x = v.x;
    y = v.y;
    return *this;
  }

  bool operator==(const Normal2 &v) const SPECULA_NOEXCEPT {
    return x == v.x && y == v.y;
  }
  bool operator!=(const Normal2 &v) const SPECULA_NOEXCEPT {
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
          "specula::Normal2::_M_range_check: __n (which is " +
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
          "specula::Normal2::_M_range_check: __n (which is " +
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
          "specula::Normal2::_M_range_check: __n (which is " +
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
          "specula::Normal2::_M_range_check: __n (which is " +
          std::to_string(i) + ") >= this->size() (which is " +
          std::to_string(this->size()) + ")");
    }
  }

  void clear() SPECULA_NOEXCEPT { x = y = T(); }

  void swap(Normal2 &v) SPECULA_NOEXCEPT {
    std::swap(x, v.x);
    std::swap(y, v.y);
  }
  SPECULA_CONSTEXPR size_type size() const SPECULA_NOEXCEPT { return 2; }

  Normal2<T> operator+(const T &s) const SPECULA_NOEXCEPT {
    return Normal2<T>(x + s, y + s);
  }
  Normal2<T> operator+(const Normal2<T> &v) const SPECULA_NOEXCEPT {
    return Normal2<T>(x + v.x, y + v.y);
  }
  Normal2<T> &operator+=(const T &s) SPECULA_NOEXCEPT {
    x += s;
    y += s;
    return *this;
  }
  Normal2<T> &operator+=(const Normal2<T> &v) SPECULA_NOEXCEPT {
    x += v.x;
    y += v.y;
    return *this;
  }
  Normal2<T> operator-(const T &s) const SPECULA_NOEXCEPT {
    return Normal2<T>(x - s, y - s);
  }
  Normal2<T> operator-(const Normal2<T> &v) const SPECULA_NOEXCEPT {
    return Normal2<T>(x - v.x, y - v.y);
  }
  Normal2<T> &operator-=(const T &s) SPECULA_NOEXCEPT {
    x -= s;
    y -= s;
    return *this;
  }
  Normal2<T> &operator-=(const Normal2<T> &v) SPECULA_NOEXCEPT {
    x -= v.x;
    y -= v.y;
    return *this;
  }
  Normal2<T> operator*(const T &s) const SPECULA_NOEXCEPT {
    return Normal2<T>(x * s, y * s);
  }
  Normal2<T> operator*(const Normal2<T> &v) const SPECULA_NOEXCEPT {
    return Normal2<T>(x * v.x, y * v.y);
  }
  Normal2<T> &operator*=(const T &s) SPECULA_NOEXCEPT {
    x *= s;
    y *= s;
    return *this;
  }
  Normal2<T> &operator*=(const Normal2<T> &v) SPECULA_NOEXCEPT {
    x *= v.x;
    y *= v.y;
    return *this;
  }
  Normal2<T> operator/(const T &s) const SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    return Normal2<T>(x * inv, y * inv);
  }
  Normal2<T> operator/(const Normal2<T> &v) const SPECULA_NOEXCEPT {
    return Normal2<T>(x / v.x, y / v.y);
  }
  Normal2<T> &operator/=(const T &s) SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    x *= inv;
    y *= inv;
    return *this;
  }
  Normal2<T> &operator/=(const Normal2<T> &v) SPECULA_NOEXCEPT {
    x /= v.x;
    y /= v.y;
    return *this;
  }
  Normal2<T> operator-() const SPECULA_NOEXCEPT { return Normal2<T>(-x, -y); }

  std::string fmt() const { return fmt::format("<{},{}>", x, y); }

  T length_squared() const { return x * x + y * y; }
  T length() const { return std::sqrt(length_squared()); }

  T x, y;
};

typedef Normal2<Float> Normal2f;
typedef Normal2<Int> Normal2i;

template <typename T>
std::ostream &operator<<(std::ostream &out, const Normal2<T> &v) {
  return out << v.fmt();
}
} // namespace specula

#endif // SPECULA_NORMAL_NORMAL2_HPP_
