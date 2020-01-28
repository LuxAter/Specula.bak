#ifndef SPECULA_VECTOR_VECTOR4_HPP_
#define SPECULA_VECTOR_VECTOR4_HPP_

#include <iostream>
#include <iterator>
#include <stdexcept>

#include "../../global.hpp"

namespace specula {
/**
 * @brief Vector with four elements
 * @ingroup Vector
 *
 * This vector class implements a vector with four elements, the elements are
 * accessed using `v.x`, `v.y`, `v.z`, `v.w`.
 *
 * @tparam T Element type for vector
 */
template <typename T> class Vector4 {
public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  Vector4() SPECULA_NOEXCEPT : x(), y(), z(), w() {}
  Vector4(const T &x, const T &y, const T &z, const T &w) SPECULA_NOEXCEPT
      : x(x),
        y(y),
        z(z),
        w(w) {}
  Vector4(const Vector4 &v) SPECULA_NOEXCEPT : x(v.x), y(v.y), z(v.z), w(v.w) {}
  ~Vector4() SPECULA_NOEXCEPT {}

  Vector4 &operator=(const Vector4 &v) SPECULA_NOEXCEPT {
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
    return *this;
  }

  bool operator==(const Vector4 &v) const SPECULA_NOEXCEPT {
    return x == v.x && y == v.y && z == v.z && w == v.w;
  }
  bool operator!=(const Vector4 &v) const SPECULA_NOEXCEPT {
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
          "specula::Vector4::_M_range_check: __n (which is " +
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
          "specula::Vector4::_M_range_check: __n (which is " +
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
          "specula::Vector4::_M_range_check: __n (which is " +
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
          "specula::Vector4::_M_range_check: __n (which is " +
          std::to_string(i) + ") >= this->size() (which is " +
          std::to_string(this->size()) + ")");
    }
  }

  void clear() SPECULA_NOEXCEPT { x = y = z = w = T(); }

  void swap(Vector4 &v) SPECULA_NOEXCEPT {
    std::swap(x, v.x);
    std::swap(y, v.y);
    std::swap(z, v.z);
    std::swap(w, v.w);
  }
  SPECULA_CONSTEXPR size_type size() const SPECULA_NOEXCEPT { return 4; }

  Vector4<T> operator+(const T &s) const SPECULA_NOEXCEPT {
    return Vector4<T>(x + s, y + s, z + s, w + s);
  }
  Vector4<T> operator+(const Vector4<T> &v) const SPECULA_NOEXCEPT {
    return Vector4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
  }
  Vector4<T> &operator+=(const T &s) SPECULA_NOEXCEPT {
    x += s;
    y += s;
    z += s;
    w += s;
    return *this;
  }
  Vector4<T> &operator+=(const Vector4<T> &v) SPECULA_NOEXCEPT {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
  }
  Vector4<T> operator-(const T &s) const SPECULA_NOEXCEPT {
    return Vector4<T>(x - s, y - s, z - s, w - s);
  }
  Vector4<T> operator-(const Vector4<T> &v) const SPECULA_NOEXCEPT {
    return Vector4<T>(x - v.x, y - v.y, z - v.z, w - v.w);
  }
  Vector4<T> &operator-=(const T &s) SPECULA_NOEXCEPT {
    x -= s;
    y -= s;
    z -= s;
    w -= s;
    return *this;
  }
  Vector4<T> &operator-=(const Vector4<T> &v) SPECULA_NOEXCEPT {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
  }
  Vector4<T> operator*(const T &s) const SPECULA_NOEXCEPT {
    return Vector4<T>(x * s, y * s, z * s, w * s);
  }
  Vector4<T> operator*(const Vector4<T> &v) const SPECULA_NOEXCEPT {
    return Vector4<T>(x * v.x, y * v.y, z * v.z, w * v.w);
  }
  Vector4<T> &operator*=(const T &s) SPECULA_NOEXCEPT {
    x *= s;
    y *= s;
    z *= s;
    w *= s;
    return *this;
  }
  Vector4<T> &operator*=(const Vector4<T> &v) SPECULA_NOEXCEPT {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
    return *this;
  }
  Vector4<T> operator/(const T &s) const SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    return Vector4<T>(x * inv, y * inv, z * inv, w * inv);
  }
  Vector4<T> operator/(const Vector4<T> &v) const SPECULA_NOEXCEPT {
    return Vector4<T>(x / v.x, y / v.y, z / v.z, w / v.w);
  }
  Vector4<T> &operator/=(const T &s) SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    x *= inv;
    y *= inv;
    z *= inv;
    w *= inv;
    return *this;
  }
  Vector4<T> &operator/=(const Vector4<T> &v) SPECULA_NOEXCEPT {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    w /= v.w;
    return *this;
  }

  Vector4<T> operator-() const SPECULA_NOEXCEPT {
    return Vector4<T>(-x, -y, -z, -w);
  }

  std::string fmt() const { return fmt::format("<{},{},{},{}>", x, y, z, w); }

  T length_squared() const { return x * x + y * y + z * z + w * w; }
  T length() const { return std::sqrt(length_squared()); }

  T x, y, z, w;
};

typedef Vector4<Float> Vector4f;
typedef Vector4<Int> Vector4i;

template <typename T, typename U>
inline Vector4<T> operator*(U s, const Vector4<T> &v) {
  return v * s;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const Vector4<T> &v) {
  return out << v.fmt();
}
} // namespace specula

#endif // SPECULA_VECTOR_VECTOR4_HPP_
