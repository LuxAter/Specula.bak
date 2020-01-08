/**
 * @file vector.hpp
 * @author Arden Rasmussen (ardenrasmussen@lclark.edu)
 * @brief Defines vector class and vector operations
 * @version 0.1
 * @date 2020-01-08
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef SPECULA_VECTOR_HPP_
#define SPECULA_VECTOR_HPP_

#include "../specula.hpp"

namespace specula {
template <typename T> class Vector2 {
public:
  Vector2() : x(0), y(0) {}
  Vector2(T x, T y) : x(x), y(y) { SPECULA_ASSERT(!has_nan()); }
  explicit Vector2(const Point2<T> &p);
  explicit Vector2(const Point3<T> &p);

  inline bool has_nan() const { return std::isnan(x) || std::isnan(y); }
  inline Float length_squared() const { return x * x + y * y; }
  inline Float length() const { return std::sqrt(x * x + y * y); }

  T operator[](std::size_t i) const {
    SPECULA_ASSERT(i >= 0 && i <= 1);
    if (i == 0)
      return x;
    return y;
  }
  T &operator[](std::size_t i) {
    SPECULA_ASSERT(i >= 0 && i <= 1);
    if (i == 0)
      return x;
    return y;
  }

  Vector2<T> operator+(const Vector2<T> &v) const {
    return Vector2<T>(x + v.x, y + v.y);
  }
  Vector2<T> &operator+=(const Vector2<T> &v) {
    x += v.x;
    y += v.y;
    return *this;
  }
  Vector2<T> operator-(const Vector2<T> &v) const {
    return Vector2<T>(x - v.x, y - v.y);
  }
  Vector2<T> &operator-=(const Vector2<T> &v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }
  template <typename U> Vector2<T> operator*(U s) const {
    return Vector2<T>(s * x, s * y);
  }
  template <typename U> Vector2<T> *operator*=(U s) {
    x *= s;
    y *= s;
    return *this;
  }
  template <typename U> Vector2<T> operator/(U f) const {
    SPECULA_ASSERT(f != 0);
    Float inv = Float(1) / f;
    return Vector2<T>(x * inv, y * inv);
  }
  template <typename U> Vector2<T> *operator/=(U f) {
    SPECULA_ASSERT(f != 0);
    Float inv = Float(1) / f;
    x *= inv;
    y *= inv;
    return *this;
  }
  Vector2<T> operator-() const { return Vector2<T>(-x, -y); }

  bool operator==(const Vector2<T> &v) const { return x = v.x && y == v.y; }
  bool operator!=(const Vector2<T> &v) const { return x != v.x || y != v.y; }

  T x, y;
};
template <typename T> class Vector3 {
public:
  Vector3() : x(0), y(0), z(0) {}
  Vector3(T x, T y, T z) : x(x), y(y), z(z) { SPECULA_ASSERT(!has_nan()); }
  explicit Vector3(const Point3<T> &p);
  explicit Vector3(const Normal3<T> &n);

  inline bool has_nan() const {
    return std::isnan(x) || std::isnan(y) || std::isnan(z);
  }

  inline Float length_squared() const { return x * x + y * y + z * z; }
  inline Float length() const { return std::sqrt(x * x + y * y + z * z); }

  T operator[](std::size_t i) const {
    SPECULA_ASSERT(i >= 0 && i <= 2);
    if (i == 0)
      return x;
    if (i == 1)
      return y;
    return z;
  }
  T &operator[](std::size_t i) {
    SPECULA_ASSERT(i >= 0 && i <= 2);
    if (i == 0)
      return x;
    if (i == 1)
      return y;
    return z;
  }

  Vector3<T> operator+(const Vector3<T> &v) const {
    return Vector3<T>(x + v.x, y + v.y, z + v.z);
  }
  Vector3<T> &operator+=(const Vector3<T> &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  Vector3<T> operator-(const Vector3<T> &v) const {
    return Vector3<T>(x - v.x, y - v.y, z - v.z);
  }
  Vector3<T> &operator-=(const Vector3<T> &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }
  template <typename U> Vector3<T> operator*(U s) const {
    return Vector3<T>(s * x, s * y, s * z);
  }
  template <typename U> Vector3<T> *operator*=(U s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }
  template <typename U> Vector3<T> operator/(U f) const {
    SPECULA_ASSERT(f != 0);
    Float inv = Float(1) / f;
    return Vector3<T>(x * inv, y * inv, z * inv);
  }
  template <typename U> Vector3<T> *operator/=(U f) {
    SPECULA_ASSERT(f != 0);
    Float inv = Float(1) / f;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
  }
  Vector3<T> operator-() const { return Vector3<T>(-x, -y, -z); }

  bool operator==(const Vector3<T> &v) const {
    return x == v.x && y == v.y && z == v.z;
  }
  bool operator!=(const Vector3<T> &v) const {
    return x != v.x || y != v.y || z != v.z;
  }

  T x, y, z;
};

typedef Vector2<Float> Vector2f;
typedef Vector2<Int> Vector2i;
typedef Vector3<Float> Vector3f;
typedef Vector3<Int> Vector3i;

template <typename T, typename U>
inline Vector2<T> operator*(U s, const Vector2<T> &v) {
  return v * s;
}
template <typename T, typename U>
inline Vector3<T> operator*(U s, const Vector3<T> &v) {
  return v * s;
}

template <typename T> inline Vector2<T> abs(const Vector2<T> &v) {
  return Vector2<T>(std::abs(v.x), std::abs(v.y));
}
template <typename T> inline Vector3<T> abs(const Vector3<T> &v) {
  return Vector3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
}

template <typename T> inline T dot(const Vector2<T> &v1, const Vector2<T> &v2) {
  return v1.x * v2.x + v1.y * v2.y;
}
template <typename T> inline T dot(const Vector3<T> &v1, const Vector3<T> &v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T>
inline T abs_dot(const Vector2<T> &v1, const Vector2<T> &v2) {
  return std::abs(v1.x * v2.x + v1.y * v2.y);
}
template <typename T>
inline T abs_dot(const Vector3<T> &v1, const Vector3<T> &v2) {
  return std::abs(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

template <typename T>
inline Vector3<T> cross(const Vector3<T> &v1, const Vector3<T> &v2) {
  double v1x = v1.x, v1y = v1.y, v1z = v1.z;
  double v2x = v2.x, v2y = v2.y, v2z = v2.z;
  return Vector3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z),
                    (v1x * v2y) - (v1y * v2x));
}

template <typename T> inline Vector2<T> normalize(const Vector2<T> &v) {
  return v / v.length();
}
template <typename T> inline Vector3<T> normalize(const Vector3<T> &v) {
  return v / v.length();
}

template <typename T> inline T min_component(const Vector2<T> &v) {
  return std::min(v.x, v.y);
}
template <typename T> inline T min_component(const Vector3<T> &v) {
  return std::min(v.x, std::min(v.y, v.z));
}

template <typename T> inline T max_component(const Vector2<T> &v) {
  return std::max(v.x, v.y);
}
template <typename T> inline T max_component(const Vector3<T> &v) {
  return std::max(v.x, std::min(v.y, v.z));
}

template <typename T> inline std::size_t min_dimension(const Vector2<T> &v) {
  return (v.x < v.y) ? 1 : 0;
}
template <typename T> inline std::size_t min_dimension(const Vector3<T> &v) {
  return (v.x < v.y) ? ((v.x < v.z) ? 0 : 2) : ((v.y < v.z) ? 1 : 2);
}

template <typename T> inline std::size_t max_dimension(const Vector2<T> &v) {
  return (v.x > v.y) ? 1 : 0;
}
template <typename T> inline std::size_t max_dimension(const Vector3<T> &v) {
  return (v.x > v.y) ? ((v.x > v.z) ? 0 : 2) : ((v.y > v.z) ? 1 : 2);
}

template <typename T>
inline Vector2<T> min(const Vector2<T> &v1, const Vector2<T> &v2) {
  return Vector3<T>(std::min(v1.x, v2.x), std::min(v1.y, v2.y));
}
template <typename T>
inline Vector3<T> min(const Vector3<T> &v1, const Vector3<T> &v2) {
  return Vector3<T>(std::min(v1.x, v2.x), std::min(v1.y, v2.y),
                    std::min(v1.z, v2.z));
}

template <typename T>
inline Vector2<T> max(const Vector2<T> &v1, const Vector2<T> &v2) {
  return Vector3<T>(std::max(v1.x, v2.x), std::max(v1.y, v2.y));
}
template <typename T>
inline Vector3<T> max(const Vector3<T> &v1, const Vector3<T> &v2) {
  return Vector3<T>(std::max(v1.x, v2.x), std::max(v1.y, v2.y),
                    std::max(v1.z, v2.z));
}

template <typename T>
inline Vector2<T> permute(const Vector2<T> &v, std::size_t x, std::size_t y) {
  return Vector2<T>(v[x], v[y]);
}
template <typename T>
inline Vector3<T> permute(const Vector3<T> &v, std::size_t x, std::size_t y,
                          std::size_t z) {
  return Vector3<T>(v[x], v[y], v[z]);
}

template <typename T>
inline std::array<Vector3<T>, 3> coordinate_system(const Vector3<T> &v1) {
  Vector3<T> v2, v3;
  if (std::abs(v1.x) > std::abs(v1.y))
    v2 = Vector3<T>(-v1.z, 0, v1.x) / std::sqrt(v1.x * v1.x + v1.z * v1.z);
  else
    v2 = Vector3<T>(0, v1.z, -v1.y) / std::sqrt(v1.y * v1.y + v1.z * v1.z);
  v3 = cross(v1, v2);
  return std::array<Vector3<T>, 3>({v1, v2, v3});
}
template <typename T>
inline void coordinate_system(const Vector3<T> &v1, Vector3<T> &v2,
                              Vector3<T> &v3) {
  if (std::abs(v1.x) > std::abs(v1.y))
    v2 = Vector3<T>(-v1.z, 0, v1.x) / std::sqrt(v1.x * v1.x + v1.z * v1.z);
  else
    v2 = Vector3<T>(0, v1.z, -v1.y) / std::sqrt(v1.y * v1.y + v1.z * v1.z);
  v3 = cross(v1, v2);
}
template <typename T>
inline void coordinate_system(const Vector3<T> &v1, Vector3<T> *v2,
                              Vector3<T> *v3) {
  if (std::abs(v1.x) > std::abs(v1.y))
    *v2 = Vector3<T>(-v1.z, 0, v1.x) / std::sqrt(v1.x * v1.x + v1.z * v1.z);
  else
    *v2 = Vector3<T>(0, v1.z, -v1.y) / std::sqrt(v1.y * v1.y + v1.z * v1.z);
  *v3 = cross(v1, *v2);
}

template <typename T>
inline std::ostream &operator<<(std::ostream &os, const Vector2<T> &v) {
  return os << "[ " << v.x << ", " << v.y << " ]";
}
template <typename T>
inline std::ostream &operator<<(std::ostream &os, const Vector3<T> &v) {
  return os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
}

} // namespace specula

#endif // SPECULA_VECTOR_HPP_