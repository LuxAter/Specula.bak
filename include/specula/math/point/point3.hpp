#ifndef SPECULA_POINT_POINT3_HPP_
#define SPECULA_POINT_POINT3_HPP_

#include <cmath>
#include <memory>
#include <stdexcept>

#include "../../global.hpp"

#include "../vector/vector3.hpp"

namespace specula {
/**
 * @brief Point with three elements
 * @ingroup Point 
 *
 * This point class implements a point with three elements, the elements are
 * accessed using `v.x`, `v.y`, and `v.z`.
 *
 * @tparam T Element type for point 
 */
template <typename T> class Point3 {
public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef std::ptrdiff_t difference_type;
  typedef std::size_t size_type;

  Point3() SPECULA_NOEXCEPT : x(), y(), z() {}
  Point3(const T &v) SPECULA_NOEXCEPT : x(v), y(v), z(v) {}
  Point3(const T &x, const T &y, const T &z) SPECULA_NOEXCEPT : x(x),
                                                                y(y),
                                                                z(z) {}
  Point3(const Point3 &v) SPECULA_NOEXCEPT : x(v.x), y(v.y), z(v.z) {}
  template <typename U>
  explicit Point3(const Vector3<U> &v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z)) {
  }
  ~Point3() SPECULA_NOEXCEPT {}

  template <typename U> explicit operator Vector3<U>() const {
    return Vector3<U>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(z));
  }

  Point3 &operator=(const Point3 &v) SPECULA_NOEXCEPT {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
  }

  bool operator==(const Point3 &v) const SPECULA_NOEXCEPT {
    return x == v.x && y == v.y && z == v.z;
  }
  bool operator!=(const Point3 &v) const SPECULA_NOEXCEPT {
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
          "specula::Point3::_M_range_check: __n (which is " +
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
          "specula::Point3::_M_range_check: __n (which is " +
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
          "specula::Point3::_M_range_check: __n (which is " +
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
          "specula::Point3::_M_range_check: __n (which is " +
          std::to_string(i) + ") >= this->size() (which is " +
          std::to_string(this->size()) + ")");
    }
  }

  void clear() SPECULA_NOEXCEPT { x = y = z = T(); }

  void swap(Point3 &v) SPECULA_NOEXCEPT {
    std::swap(x, v.x);
    std::swap(y, v.y);
    std::swap(z, v.z);
  }
  SPECULA_CONSTEXPR size_type size() const SPECULA_NOEXCEPT { return 3; }

  Point3<T> operator+(const T &s) const SPECULA_NOEXCEPT {
    return Point3<T>(x + s, y + s, z + s);
  }
  Point3<T> operator+(const Point3<T> &v) const SPECULA_NOEXCEPT {
    return Point3<T>(x + v.x, y + v.y, z + v.z);
  }
  Point3<T> operator+(const Vector3<T> &v) const SPECULA_NOEXCEPT {
    return Point3<T>(x + v.x, y + v.y, z + v.z);
  }
  Point3<T> &operator+=(const T &s) SPECULA_NOEXCEPT {
    x += s;
    y += s;
    z += s;
    return *this;
  }
  Point3<T> &operator+=(const Point3<T> &v) SPECULA_NOEXCEPT {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  Point3<T> &operator+=(const Vector3<T> &v) SPECULA_NOEXCEPT {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  Point3<T> operator-(const T &s) const SPECULA_NOEXCEPT {
    return Point3<T>(x - s, y - s, z - s);
  }
  Vector3<T> operator-(const Point3<T> &v) const SPECULA_NOEXCEPT {
    return Vector3<T>(x - v.x, y - v.y, z - v.z);
  }
  Point3<T> operator-(const Vector3<T> &v) const SPECULA_NOEXCEPT {
    return Point3<T>(x - v.x, y - v.y, z - v.z);
  }
  Point3<T> &operator-=(const T &s) SPECULA_NOEXCEPT {
    x -= s;
    y -= s;
    z -= s;
    return *this;
  }
  Point3<T> operator*(const T &s) const SPECULA_NOEXCEPT {
    return Point3<T>(x * s, y * s, z * s);
  }
  Point3<T> operator*(const Point3<T> &v) const SPECULA_NOEXCEPT {
    return Point3<T>(x * v.x, y * v.y, z * v.z);
  }
  Point3<T> &operator*=(const T &s) SPECULA_NOEXCEPT {
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }
  Point3<T> &operator*=(const Point3<T> &v) SPECULA_NOEXCEPT {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
  }
  Point3<T> operator/(const T &s) const SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    return Point3<T>(x * inv, y * inv, z * inv);
  }
  Point3<T> operator/(const Point3<T> &v) const SPECULA_NOEXCEPT {
    return Point3<T>(x / v.x, y / v.y, z / v.z);
  }
  Point3<T> &operator/=(const T &s) SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
  }
  Point3<T> &operator/=(const Point3<T> &v) SPECULA_NOEXCEPT {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
  }

  Point3<T> operator-() const SPECULA_NOEXCEPT { return Point3<T>(-x, -y, -z); }

  std::string fmt() const { return fmt::format("<{},{},{}>", x, y, z); }

  T x, y, z;
};

typedef Point3<Float> Point3f;
typedef Point3<Int> Point3i;

template <typename T>
std::ostream &operator<<(std::ostream &out, const Point3<T> &v) {
  return out << v.fmt();
}
} // namespace specula

#endif // SPECULA_POINT_POINT3_HPP_
