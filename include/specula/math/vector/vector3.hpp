#ifndef SPECULA_VECTOR_VECTOR3_HPP_
#define SPECULA_VECTOR_VECTOR3_HPP_

#include <cmath>
#include <memory>
#include <stdexcept>

#include "../../global.hpp"

namespace specula {
template <typename T, class A = std::allocator<T>> class Vector3 {
public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef std::ptrdiff_t difference_type;
  typedef std::size_t size_type;

  Vector3() SPECULA_NOEXCEPT : x(), y(), z() {}
  Vector3(const T &x, const T &y, const T &z) SPECULA_NOEXCEPT : x(x),
                                                                 y(y),
                                                                 z(z) {}
  Vector3(const Vector3 &v) SPECULA_NOEXCEPT : x(v.x), y(v.y), z(v.z) {}
  ~Vector3() SPECULA_NOEXCEPT {}

  Vector3 &operator=(const Vector3 &v) SPECULA_NOEXCEPT {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
  }

  bool operator==(const Vector3 &v) const SPECULA_NOEXCEPT {
    return x == v.x && y == v.y && z == v.z;
  }
  bool operator!=(const Vector3 &v) const SPECULA_NOEXCEPT {
    return x != v.x || y != v.y || z != v.z;
  }

  reference operator[](size_type i) {
    switch (i) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    default:
      throw std::out_of_range(
          "specula::Vector3::_M_range_check: __n (which is " +
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
    default:
      throw std::out_of_range(
          "specula::Vector3::_M_range_check: __n (which is " +
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
    default:
      throw std::out_of_range(
          "specula::Vector3::_M_range_check: __n (which is " +
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
    default:
      throw std::out_of_range(
          "specula::Vector3::_M_range_check: __n (which is " +
          std::to_string(i) + ") >= this->size() (which is " +
          std::to_string(this->size()) + ")");
    }
  }

  void clear() SPECULA_NOEXCEPT { x = y = z = T(); }

  void swap(Vector3 &v) SPECULA_NOEXCEPT {
    std::swap(x, v.x);
    std::swap(y, v.y);
    std::swap(z, v.z);
  }
  SPECULA_CONSTEXPR size_type size() const SPECULA_NOEXCEPT { return 3; }

  Vector3<T> operator+(const T &s) const SPECULA_NOEXCEPT {
    return Vector3<T>(x + s, y + s, z + s);
  }
  Vector3<T> operator+(const Vector3<T> &v) const SPECULA_NOEXCEPT {
    return Vector3<T>(x + v.x, y + v.y, z + v.z);
  }
  Vector3<T> &operator+=(const T &s) SPECULA_NOEXCEPT {
    x += s;
    y += s;
    z += s;
    return *this;
  }
  Vector3<T> &operator+=(const Vector3<T> &v) SPECULA_NOEXCEPT {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  Vector3<T> operator-(const T &s) const SPECULA_NOEXCEPT {
    return Vector3<T>(x - s, y - s, z - s);
  }
  Vector3<T> operator-(const Vector3<T> &v) const SPECULA_NOEXCEPT {
    return Vector3<T>(x - v.x, y - v.y, z - v.z);
  }
  Vector3<T> &operator-=(const T &s) SPECULA_NOEXCEPT {
    x -= s;
    y -= s;
    z -= s;
    return *this;
  }
  Vector3<T> &operator-=(const Vector3<T> &v) SPECULA_NOEXCEPT {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }
  Vector3<T> operator*(const T &s) const SPECULA_NOEXCEPT {
    return Vector3<T>(x * s, y * s, z * s);
  }
  Vector3<T> operator*(const Vector3<T> &v) const SPECULA_NOEXCEPT {
    return Vector3<T>(x * v.x, y * v.y, z * v.z);
  }
  Vector3<T> &operator*=(const T &s) SPECULA_NOEXCEPT {
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }
  Vector3<T> &operator*=(const Vector3<T> &v) SPECULA_NOEXCEPT {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
  }
  Vector3<T> operator/(const T &s) const SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    return Vector3<T>(x * inv, y * inv, z * inv);
  }
  Vector3<T> operator/(const Vector3<T> &v) const SPECULA_NOEXCEPT {
    return Vector3<T>(x / v.x, y / v.y, z / v.z);
  }
  Vector3<T> &operator/=(const T &s) SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
  }
  Vector3<T> &operator/=(const Vector3<T> &v) SPECULA_NOEXCEPT {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
  }

  Vector3<T> operator-() const SPECULA_NOEXCEPT {
    return Vector3<T>(-x, -y, -z);
  }

  std::string fmt() const { return fmt::format("<{},{},{}>", x, y, z); }

  T length_squared() const { return x * x + y * y + z * z; }
  T length() const { return std::sqrt(length_squared()); }

  T x, y, z;
};

typedef Vector3<Float> Vector3f;
typedef Vector3<Int> Vector3i;

template <typename T, typename U>
inline Vector3<T> operator*(U s, const Vector3<T> &v) {
  return v * s;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const Vector3<T> &v) {
  return out << v.fmt();
}
} // namespace specula

#endif // SPECULA_VECTOR_VECTOR3_HPP_
