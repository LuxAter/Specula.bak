/**
 * @file point.hpp
 * @author Arden Rasmussen (ardenrasmussen@lclark.edu)
 * @brief Defines point class, and point operations
 * @version 0.1
 * @date 2020-01-08
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef SPECULA_POINT_HPP_
#define SPECULA_POINT_HPP_

#include "../specula.hpp"

#include "vector.hpp"

namespace specula {
template <typename T> class Point2 {
public:
  Point2() : x(0), y(0) {}
  Point2(T x, T y) : x(x), y(y) { SPECULA_ASSERT(!has_nan()); }
  explicit Point2(const Point3<T> &p);

  template <typename U>
  explicit Point2(const Point2<U> &p)
      : x(static_cast<T>(p.x)), y(static_cast<T>(p.y)) {
    SPECULA_ASSERT(!has_nan());
  }
  template <typename U>
  explicit Point2(const Vector2<U> &v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {
    SPECULA_ASSERT(!has_nan());
  }

  inline bool has_nan() const { return std::isnan(x) || std::isnan(y); }

  template <typename U> explicit operator Vector2<U>() const {
    return Vector2<U>(static_cast<U>(x), static_cast<U>(y));
  }

  Point2<T> operator+(const Point2<T> &p) const {
    return Point2<T>(x + p.x, y + p.y);
  }
  Point2<T> operator+(const Vector2<T> &v) const {
    return Point2<T>(x + v.x, y + v.y);
  }
  Point2<T> &operator+=(const Point2<T> &p) {
    x += p.x;
    y += p.y;
    return *this;
  }
  Point2<T> &operator+=(const Vector2<T> &v) {
    x += v.x;
    y += v.y;
    return *this;
  }
  Vector2<T> operator-(const Point2<T> &p) const {
    return Vector2<T>(x - p.x, y - p.y);
  }
  Point2<T> operator-(const Vector2<T> &v) const {
    return Point2<T>(x - v.x, y - v.y);
  }
  Point2<T> &operator-=(const Vector2<T> &v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }
  template <typename U> Point2<T> operator*(U s) const {
    return Point2<T>(s * x, s * y);
  }
  template <typename U> Point2<T> &operator*=(U s) {
    x *= s;
    y *= s;
    return *this;
  }
  template <typename U> Point2<T> operator/(U f) const {
    SPECULA_ASSERT(f != 0);
    Float inv = Float(1) / f;
    return Point2<T>(inv * x, inv * y);
  }
  template <typename U> Point2<T> &operator/=(U f) {
    SPECULA_ASSERT(f != 0);
    Float inv = Float(1) / f;
    x *= inv;
    y *= inv;
    return *this;
  }
  Point2<T> operator-() const { return Point2<T>(-x, -y); }

  bool operator==(const Point2<T> &p) const { return x == p.x && y == p.y; }
  bool operator!=(const Point2<T> &p) const { return x != p.x || y != p.y; }

  T x, y;
};
template <typename T> class Point3 {
public:
  Point3() : x(0), y(0), z(0) {}
  Point3(T x, T y, T z) : x(x), y(y), z(z) { SPECULA_ASSERT(!has_nan()); }
  template <typename U>
  explicit Point3(const Point3<U> &p)
      : x(static_cast<T>(p.x)), y(static_cast<T>(p.y)), z(static_cast<T>(p.z)) {
    SPECULA_ASSERT(!has_nan());
  }
  template <typename U>
  explicit Point3(const Vector3<U> &v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z)) {
    SPECULA_ASSERT(!has_nan());
  }

  inline bool has_nan() const {
    return std::isnan(x) || std::isnan(y) || std::isnan(z);
  }

  template <typename U> explicit operator Vector3<U>() const {
    return Vector3<U>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(z));
  }
  template <typename U> explicit operator Point2<U>() const {
    return Point2<U>(static_cast<U>(x), static_cast<U>(y));
  }

  Point3<T> operator+(const Point3<T> &p) const {
    return Point3<T>(x + p.x, y + p.y, z + p.z);
  }
  Point3<T> operator+(const Vector3<T> &v) const {
    return Point3<T>(x + v.x, y + v.y, z + v.z);
  }
  Point3<T> &operator+=(const Point3<T> &p) {
    x += p.x;
    y += p.y;
    z += p.z;
    return *this;
  }
  Point3<T> &operator+=(const Vector3<T> &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  Vector3<T> operator-(const Point3<T> &p) const {
    return Vector3<T>(x - p.x, y - p.y, z - p.z);
  }
  Point3<T> operator-(const Vector3<T> &v) const {
    return Point3<T>(x - v.x, y - v.y, z - v.z);
  }
  Point3<T> &operator-=(const Vector3<T> &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }
  template <typename U> Point3<T> operator*(U s) const {
    return Point3<T>(s * x, s * y, s * z);
  }
  template <typename U> Point3<T> &operator*=(U s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }
  template <typename U> Point3<T> operator/(U f) const {
    SPECULA_ASSERT(f != 0);
    Float inv = Float(1) / f;
    return Point3<T>(inv * x, inv * y, inv * z);
  }
  template <typename U> Point3<T> &operator/=(U f) {
    SPECULA_ASSERT(f != 0);
    Float inv = Float(1) / f;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
  }
  Point3<T> operator-() const { return Point3<T>(-x, -y, -z); }

  bool operator==(const Point3<T> &p) const {
    return x == p.x && y == p.y && z == p.z;
  }
  bool operator!=(const Point3<T> &p) const {
    return x != p.x || y != p.y || z != p.z;
  }

  T x, y, z;
};

typedef Point2<Float> Point2f;
typedef Point2<Int> Point2i;
typedef Point3<Float> Point3f;
typedef Point3<Int> Point3i;

template <typename T>
inline T distance(const Point2<T> &p1, const Point2<T> &p2) {
  return (p1 - p2).length();
}
template <typename T>
inline T distance(const Point3<T> &p1, const Point3<T> &p2) {
  return (p1 - p2).length();
}

template <typename T>
inline T distance_squared(const Point2<T> &p1, const Point2<T> &p2) {
  return (p1 - p2).length_squared();
}
template <typename T>
inline T distance_squared(const Point3<T> &p1, const Point3<T> &p2) {
  return (p1 - p2).length_squared();
}

template <typename T>
Point2<T> lerp(const Point2<T> &p0, const Point2<T> &p1, Float t) {
  return (1 - t) * p0 + t * p1;
}
template <typename T>
Point3<T> lerp(const Point3<T> &p0, const Point3<T> &p1, Float t) {
  return (1 - t) * p0 + t * p1;
}

template <typename T> Point2<T> min(const Point2<T> &p1, const Point2<T> &p2) {
  return Point2<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y));
}
template <typename T> Point3<T> min(const Point3<T> &p1, const Point3<T> &p2) {
  return Point3<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y),
                   std::min(p1.z, p2.z));
}

template <typename T> Point2<T> max(const Point2<T> &p1, const Point2<T> &p2) {
  return Point2<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y));
}
template <typename T> Point3<T> max(const Point3<T> &p1, const Point3<T> &p2) {
  return Point3<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y),
                   std::max(p1.z, p2.z));
}

template <typename T> Point2<T> floor(const Point2<T> &p) {
  return Point2<T>(std::floor(p.x), std::floor(p.y));
}
template <typename T> Point3<T> floor(const Point3<T> &p) {
  return Point3<T>(std::floor(p.x), std::floor(p.y), std::floor(p.z));
}
template <typename T> Point2<T> ceil(const Point2<T> &p) {
  return Point2<T>(std::ceil(p.x), std::ceil(p.y));
}
template <typename T> Point3<T> ceil(const Point3<T> &p) {
  return Point3<T>(std::ceil(p.x), std::ceil(p.y), std::ceil(p.z));
}
template <typename T> Point2<T> abs(const Point2<T> &p) {
  return Point2<T>(std::abs(p.x), std::abs(p.y));
}
template <typename T> Point3<T> abs(const Point3<T> &p) {
  return Point3<T>(std::abs(p.x), std::abs(p.y), std::abs(p.z));
}

template <typename T>
Point2<T> permute(const Point2<T> &p, std::size_t x, std::size_t y) {
  return Point2<T>(p[x], p[y]);
}
template <typename T>
Point3<T> permute(const Point3<T> &p, std::size_t x, std::size_t y,
                  std::size_t z) {
  return Point3<T>(p[x], p[y], p[z]);
}

template <typename T>
inline std::ostream &operator<<(std::ostream &os, const Point2<T> &p) {
  return os << "[ " << p.x << ", " << p.y << " ]";
}
template <typename T>
inline std::ostream &operator<<(std::ostream &os, const Point3<T> &p) {
  return os << "[ " << p.x << ", " << p.y << ", " << p.z << " ]";
}

} // namespace specula

#endif // SPECULA_POINT_HPP_