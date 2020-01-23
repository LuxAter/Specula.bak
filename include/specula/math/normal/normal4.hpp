#ifndef SPECULA_NORMAL_NORMAL4_HPP_
#define SPECULA_NORMAL_NORMAL4_HPP_

#include <iostream>
#include <iterator>
#include <stdexcept>

#include "../../compiler.hpp"
#include "../../fmt.hpp"
#include "../../types.hpp"

#include "../vector/vector4.hpp"

namespace specula {
template <typename T> class Normal4 {
public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  Normal4() SPECULA_NOEXCEPT : x(), y(), z(), w() {}
  Normal4(const T &x, const T &y, const T &z, const T &w) SPECULA_NOEXCEPT
      : x(x),
        y(y),
        z(z),
        w(w) {}
  Normal4(const Normal4 &v) SPECULA_NOEXCEPT : x(v.x), y(v.y), z(v.z), w(v.w) {}
  template <typename U>
  explicit Normal4(const Vector4<U> &v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z)),
        w(static_cast<T>(v.w)) {}
  ~Normal4() SPECULA_NOEXCEPT {}

  template <typename U> explicit operator Vector4<U>() const {
    return Vector4<U>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(z),
                      static_cast<U>(w));
  }

  Normal4 &operator=(const Normal4 &v) SPECULA_NOEXCEPT {
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
    return *this;
  }

  bool operator==(const Normal4 &v) const SPECULA_NOEXCEPT {
    return x == v.x && y == v.y && z == v.z && w == v.w;
  }
  bool operator!=(const Normal4 &v) const SPECULA_NOEXCEPT {
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
          "specula::Normal4::_M_range_check: __n (which is " +
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
          "specula::Normal4::_M_range_check: __n (which is " +
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
          "specula::Normal4::_M_range_check: __n (which is " +
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
          "specula::Normal4::_M_range_check: __n (which is " +
          std::to_string(i) + ") >= this->size() (which is " +
          std::to_string(this->size()) + ")");
    }
  }

  void clear() SPECULA_NOEXCEPT { x = y = z = w = T(); }

  void swap(Normal4 &v) SPECULA_NOEXCEPT {
    std::swap(x, v.x);
    std::swap(y, v.y);
    std::swap(z, v.z);
    std::swap(w, v.w);
  }
  SPECULA_CONSTEXPR size_type size() const SPECULA_NOEXCEPT { return 4; }

  Normal4<T> operator+(const T &s) const SPECULA_NOEXCEPT {
    return Normal4<T>(x + s, y + s, z + s, w + s);
  }
  Normal4<T> operator+(const Normal4<T> &v) const SPECULA_NOEXCEPT {
    return Normal4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
  }
  Normal4<T> &operator+=(const T &s) SPECULA_NOEXCEPT {
    x += s;
    y += s;
    z += s;
    w += s;
    return *this;
  }
  Normal4<T> &operator+=(const Normal4<T> &v) SPECULA_NOEXCEPT {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
  }
  Normal4<T> operator-(const T &s) const SPECULA_NOEXCEPT {
    return Normal4<T>(x - s, y - s, z - s, w - s);
  }
  Normal4<T> operator-(const Normal4<T> &v) const SPECULA_NOEXCEPT {
    return Normal4<T>(x - v.x, y - v.y, z - v.z, w - v.w);
  }
  Normal4<T> &operator-=(const T &s) SPECULA_NOEXCEPT {
    x -= s;
    y -= s;
    z -= s;
    w -= s;
    return *this;
  }
  Normal4<T> &operator-=(const Normal4<T> &v) SPECULA_NOEXCEPT {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
  }
  Normal4<T> operator*(const T &s) const SPECULA_NOEXCEPT {
    return Normal4<T>(x * s, y * s, z * s, w * s);
  }
  Normal4<T> operator*(const Normal4<T> &v) const SPECULA_NOEXCEPT {
    return Normal4<T>(x * v.x, y * v.y, z * v.z, w * v.w);
  }
  Normal4<T> &operator*=(const T &s) SPECULA_NOEXCEPT {
    x *= s;
    y *= s;
    z *= s;
    w *= s;
    return *this;
  }
  Normal4<T> &operator*=(const Normal4<T> &v) SPECULA_NOEXCEPT {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
    return *this;
  }
  Normal4<T> operator/(const T &s) const SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    return Normal4<T>(x * inv, y * inv, z * inv, w * inv);
  }
  Normal4<T> operator/(const Normal4<T> &v) const SPECULA_NOEXCEPT {
    return Normal4<T>(x / v.x, y / v.y, z / v.z, w / v.w);
  }
  Normal4<T> &operator/=(const T &s) SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    x *= inv;
    y *= inv;
    z *= inv;
    w *= inv;
    return *this;
  }
  Normal4<T> &operator/=(const Normal4<T> &v) SPECULA_NOEXCEPT {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    w /= v.w;
    return *this;
  }

  Normal4<T> operator-() const SPECULA_NOEXCEPT {
    return Normal4<T>(-x, -y, -z, -w);
  }

  std::string fmt() const { return fmt::format("<{},{},{},{}>", x, y, z, w); }

  T length_squared() const { return x * x + y * y + z * z + w * w; }
  T length() const { return std::sqrt(length_squared()); }

  T x, y, z, w;
};

typedef Normal4<Float> Normal4f;
typedef Normal4<Int> Normal4i;

template <typename T, typename U>
inline Normal4<T> operator*(U s, const Normal4<T> &v) {
  return v * s;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const Normal4<T> &v) {
  return out << v.fmt();
}
} // namespace specula

#endif // SPECULA_NORMAL_NORMAL4_HPP_
