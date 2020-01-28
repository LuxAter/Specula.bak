#ifndef SPECULA_QUAFloatERNION_HPP_
#define SPECULA_QUAFloatERNION_HPP_

#include <iostream>
#include <iterator>
#include <stdexcept>

#include "../global.hpp"

namespace specula {

class Quaternion {
public:
  typedef Float value_type;
  typedef Float &reference;
  typedef const Float &const_reference;
  typedef Float *pointer;
  typedef const Float *const_pointer;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  Quaternion() SPECULA_NOEXCEPT : x(0), y(0), z(0), w(1) {}
  Quaternion(const Transform &t);
  Quaternion(const Float &x, const Float &y, const Float &z,
             const Float &w) SPECULA_NOEXCEPT : x(x),
                                                y(y),
                                                z(z),
                                                w(w) {}
  Quaternion(const Quaternion &v) SPECULA_NOEXCEPT : x(v.x),
                                                     y(v.y),
                                                     z(v.z),
                                                     w(v.w) {}
  ~Quaternion() SPECULA_NOEXCEPT {}

  Transform to_transform() const;

  Quaternion &operator=(const Quaternion &v) SPECULA_NOEXCEPT {
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
    return *this;
  }

  bool operator==(const Quaternion &v) const SPECULA_NOEXCEPT {
    return x == v.x && y == v.y && z == v.z && w == v.w;
  }
  bool operator!=(const Quaternion &v) const SPECULA_NOEXCEPT {
    return x != v.x || y != v.y || z != v.z || w != v.w;
  }

  void swap(Quaternion &v) SPECULA_NOEXCEPT {
    std::swap(x, v.x);
    std::swap(y, v.y);
    std::swap(z, v.z);
    std::swap(w, v.w);
  }
  SPECULA_CONSTEXPR size_type size() const SPECULA_NOEXCEPT { return 4; }

  Quaternion operator+(const Float &s) const SPECULA_NOEXCEPT {
    return Quaternion(x + s, y + s, z + s, w + s);
  }
  Quaternion operator+(const Quaternion &v) const SPECULA_NOEXCEPT {
    return Quaternion(x + v.x, y + v.y, z + v.z, w + v.w);
  }
  Quaternion &operator+=(const Float &s) SPECULA_NOEXCEPT {
    x += s;
    y += s;
    z += s;
    w += s;
    return *this;
  }
  Quaternion &operator+=(const Quaternion &v) SPECULA_NOEXCEPT {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
  }
  Quaternion operator-(const Float &s) const SPECULA_NOEXCEPT {
    return Quaternion(x - s, y - s, z - s, w - s);
  }
  Quaternion operator-(const Quaternion &v) const SPECULA_NOEXCEPT {
    return Quaternion(x - v.x, y - v.y, z - v.z, w - v.w);
  }
  Quaternion &operator-=(const Float &s) SPECULA_NOEXCEPT {
    x -= s;
    y -= s;
    z -= s;
    w -= s;
    return *this;
  }
  Quaternion &operator-=(const Quaternion &v) SPECULA_NOEXCEPT {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
  }
  Quaternion operator*(const Float &s) const SPECULA_NOEXCEPT {
    return Quaternion(x * s, y * s, z * s, w * s);
  }
  Quaternion &operator*=(const Float &s) SPECULA_NOEXCEPT {
    x *= s;
    y *= s;
    z *= s;
    w *= s;
    return *this;
  }
  Quaternion operator/(const Float &s) const SPECULA_NOEXCEPT {
    Float inv = Float(1) / s;
    return Quaternion(x * inv, y * inv, z * inv, w * inv);
  }
  Quaternion &operator/=(const Float &s) SPECULA_NOEXCEPT {
    Float inv = Float(1) / s;
    x *= inv;
    y *= inv;
    z *= inv;
    w *= inv;
    return *this;
  }

  Quaternion operator-() const SPECULA_NOEXCEPT {
    return Quaternion(-x, -y, -z, -w);
  }

  std::string fmt() const { return fmt::format("<{},{},{},{}>", x, y, z, w); }

  Float length_squared() const { return x * x + y * y + z * z + w * w; }
  Float length() const { return std::sqrt(length_squared()); }

  Float x, y, z, w;
};

Quaternion slerp(const Quaternion &q1, const Quaternion &q2, Float t);
inline Float dot(const Quaternion &q1, const Quaternion &q2) {
  return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
}
inline Quaternion normalize(const Quaternion &q) { return q / q.length(); }

inline Quaternion operator*(Float s, const Quaternion &v) { return v * s; }

inline std::ostream &operator<<(std::ostream &out, const Quaternion &v) {
  return out << v.fmt();
}
} // namespace specula

#endif // SPECULA_MAFloatH_QUAFloatERNION_HPP_
