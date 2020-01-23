#ifndef SPECULA_GEOMETRIC_HPP_
#define SPECULA_GEOMETRIC_HPP_

#include <cmath>

#include "bounds.hpp"
#include "common.hpp"
#include "matrix.hpp"
#include "normal.hpp"
#include "point.hpp"
#include "vector.hpp"

namespace specula {

template <typename T>
inline T absdot(const Vector2<T> &v1, const Vector2<T> &v2) {
  return abs(v1.x * v2.x + v1.y * v2.y);
}
template <typename T>
inline T absdot(const Vector3<T> &v1, const Vector3<T> &v2) {
  return abs(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
template <typename T>
inline T absdot(const Vector4<T> &v1, const Vector4<T> &v2) {
  return abs(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}
template <typename T>
inline T absdot(const Normal2<T> &v1, const Normal2<T> &v2) {
  return abs(v1.x * v2.x + v1.y * v2.y);
}
template <typename T>
inline T absdot(const Normal3<T> &v1, const Normal3<T> &v2) {
  return abs(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
template <typename T>
inline T absdot(const Normal4<T> &v1, const Normal4<T> &v2) {
  return abs(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}
template <typename T>
inline T absdot(const Vector2<T> &v1, const Normal2<T> &v2) {
  return abs(v1.x * v2.x + v1.y * v2.y);
}
template <typename T>
inline T absdot(const Vector3<T> &v1, const Normal3<T> &v2) {
  return abs(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
template <typename T>
inline T absdot(const Vector4<T> &v1, const Normal4<T> &v2) {
  return abs(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}
template <typename T>
inline T absdot(const Normal2<T> &v1, const Vector2<T> &v2) {
  return abs(v1.x * v2.x + v1.y * v2.y);
}
template <typename T>
inline T absdot(const Normal3<T> &v1, const Vector3<T> &v2) {
  return abs(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
template <typename T>
inline T absdot(const Normal4<T> &v1, const Vector4<T> &v2) {
  return abs(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}

template <typename T>
inline std::array<Vector3<T>, 3> coordinate_system(const Vector3<T> &v1) {
  Vector3<T> v2, v3;
  if (abs(v1.x) > abs(v1.y)) {
    v2 = Vector3<T>(-v1.z, 0, v1.x) / std::sqrt(v1.x * v1.x + v1.z * v1.z);
  } else {
    v2 = Vector3<T>(0, v1.z, -v1.y) / std::sqrt(v1.y * v1.y + v1.z * v1.z);
  }
  return std::array<Vector3<T>, 3>{v1, v2, cross(v1, v2)};
}
template <typename T>
inline void coordinate_system(const Vector3<T> &v1, Vector3<T> &v2,
                              Vector3<T> &v3) {
  if (abs(v1.x) > abs(v1.y)) {
    v2 = Vector3<T>(-v1.z, 0, v1.x) / std::sqrt(v1.x * v1.x + v1.z * v1.z);
  } else {
    v2 = Vector3<T>(0, v1.z, -v1.y) / std::sqrt(v1.y * v1.y + v1.z * v1.z);
  }
  v3 = cross(v1, v2);
}

template <typename T>
inline Vector3<T> cross(const Vector3<T> &v1, const Vector3<T> &v2) {
  double v1x = v1.x, v1y = v1.y, v1z = v1.z;
  double v2x = v2.x, v2y = v2.y, v2z = v2.z;
  return Vector3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z),
                    (v1x * v2y) - (v1y * v2x));
}
template <typename T>
inline Vector3<T> cross(const Vector3<T> &v1, const Normal3<T> &v2) {
  double v1x = v1.x, v1y = v1.y, v1z = v1.z;
  double v2x = v2.x, v2y = v2.y, v2z = v2.z;
  return Vector3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z),
                    (v1x * v2y) - (v1y * v2x));
}
template <typename T>
inline Vector3<T> cross(const Normal3<T> &v1, const Vector3<T> &v2) {
  double v1x = v1.x, v1y = v1.y, v1z = v1.z;
  double v2x = v2.x, v2y = v2.y, v2z = v2.z;
  return Vector3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z),
                    (v1x * v2y) - (v1y * v2x));
}

template <typename T>
inline Float distance(const Point2<T> &p1, const Point2<T> &p2) {
  return (p1 - p2).length();
}
template <typename T>
inline Float distance(const Point3<T> &p1, const Point3<T> &p2) {
  return (p1 - p2).length();
}
template <typename T>
inline Float distance(const Point4<T> &p1, const Point4<T> &p2) {
  return (p1 - p2).length();
}

template <typename T>
inline Float distance_squared(const Point2<T> &p1, const Point2<T> &p2) {
  return (p1 - p2).length_squared();
}
template <typename T>
inline Float distance_squared(const Point3<T> &p1, const Point3<T> &p2) {
  return (p1 - p2).length_squared();
}
template <typename T>
inline Float distance_squared(const Point4<T> &p1, const Point4<T> &p2) {
  return (p1 - p2).length_squared();
}

template <typename T, typename U>
inline Float distance_squared(const Point2<T> &p, const Bounds2<T> &b) {
  Float dx = std::max({Float(0), b.p_min.x - p.x, p.x - b.p_max.x});
  Float dy = std::max({Float(0), b.p_min.y - p.y, p.y - b.p_max.y});
  return dx * dx + dy * dy;
}
template <typename T, typename U>
inline Float distance_squared(const Point3<T> &p, const Bounds3<T> &b) {
  Float dx = std::max({Float(0), b.p_min.x - p.x, p.x - b.p_max.x});
  Float dy = std::max({Float(0), b.p_min.y - p.y, p.y - b.p_max.y});
  Float dz = std::max({Float(0), b.p_min.z - p.z, p.z - b.p_max.z});
  return dx * dx + dy * dy + dz * dz;
}
template <typename T, typename U>
inline Float distance_squared(const Point4<T> &p, const Bounds4<T> &b) {
  Float dx = std::max({Float(0), b.p_min.x - p.x, p.x - b.p_max.x});
  Float dy = std::max({Float(0), b.p_min.y - p.y, p.y - b.p_max.y});
  Float dz = std::max({Float(0), b.p_min.z - p.z, p.z - b.p_max.z});
  Float dw = std::max({Float(0), b.p_min.w - p.w, p.w - b.p_max.w});
  return dx * dx + dy * dy + dz * dz + dw * dw;
}

template <typename T, typename U>
inline Float distance(const Point2<T> &p, const Bounds2<T> &b) {
  return std::sqrt(distance_squared(p, b));
}
template <typename T, typename U>
inline Float distance(const Point3<T> &p, const Bounds3<T> &b) {
  return std::sqrt(distance_squared(p, b));
}
template <typename T, typename U>
inline Float distance(const Point4<T> &p, const Bounds4<T> &b) {
  return std::sqrt(distance_squared(p, b));
}

template <typename T> inline T dot(const Vector2<T> &v1, const Vector2<T> &v2) {
  return v1.x * v2.x + v1.y * v2.y;
}
template <typename T> inline T dot(const Vector3<T> &v1, const Vector3<T> &v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
template <typename T> inline T dot(const Vector4<T> &v1, const Vector4<T> &v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}
template <typename T> inline T dot(const Normal2<T> &v1, const Normal2<T> &v2) {
  return v1.x * v2.x + v1.y * v2.y;
}
template <typename T> inline T dot(const Normal3<T> &v1, const Normal3<T> &v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
template <typename T> inline T dot(const Normal4<T> &v1, const Normal4<T> &v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}
template <typename T> inline T dot(const Vector2<T> &v1, const Normal2<T> &v2) {
  return v1.x * v2.x + v1.y * v2.y;
}
template <typename T> inline T dot(const Vector3<T> &v1, const Normal3<T> &v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
template <typename T> inline T dot(const Vector4<T> &v1, const Normal4<T> &v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}
template <typename T> inline T dot(const Normal2<T> &v1, const Vector2<T> &v2) {
  return v1.x * v2.x + v1.y * v2.y;
}
template <typename T> inline T dot(const Normal3<T> &v1, const Vector3<T> &v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
template <typename T> inline T dot(const Normal4<T> &v1, const Vector4<T> &v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

template <typename T>
inline Normal2<T> faceforward(const Normal2<T> &n, const Normal2<T> &v) {
  return (dot(n, v) < 0.0f) ? -n : n;
}
template <typename T>
inline Normal3<T> faceforward(const Normal3<T> &n, const Normal3<T> &v) {
  return (dot(n, v) < 0.0f) ? -n : n;
}
template <typename T>
inline Normal4<T> faceforward(const Normal4<T> &n, const Normal4<T> &v) {
  return (dot(n, v) < 0.0f) ? -n : n;
}
template <typename T>
inline Normal2<T> faceforward(const Normal2<T> &n, const Vector2<T> &v) {
  return (dot(n, v) < 0.0f) ? -n : n;
}
template <typename T>
inline Normal3<T> faceforward(const Normal3<T> &n, const Vector2<T> &v) {
  return (dot(n, v) < 0.0f) ? -n : n;
}
template <typename T>
inline Normal4<T> faceforward(const Normal4<T> &n, const Vector4<T> &v) {
  return (dot(n, v) < 0.0f) ? -n : n;
}
template <typename T>
inline Vector2<T> faceforward(const Vector2<T> &n, const Normal2<T> &v) {
  return (dot(n, v) < 0.0f) ? -n : n;
}
template <typename T>
inline Vector3<T> faceforward(const Vector3<T> &n, const Normal3<T> &v) {
  return (dot(n, v) < 0.0f) ? -n : n;
}
template <typename T>
inline Vector4<T> faceforward(const Vector4<T> &n, const Normal4<T> &v) {
  return (dot(n, v) < 0.0f) ? -n : n;
}
template <typename T>
inline Vector2<T> faceforward(const Vector2<T> &n, const Vector2<T> &v) {
  return (dot(n, v) < 0.0f) ? -n : n;
}
template <typename T>
inline Vector3<T> faceforward(const Vector3<T> &n, const Vector2<T> &v) {
  return (dot(n, v) < 0.0f) ? -n : n;
}
template <typename T>
inline Vector4<T> faceforward(const Vector4<T> &n, const Vector4<T> &v) {
  return (dot(n, v) < 0.0f) ? -n : n;
}

template <typename T>
inline typename Vector2<T>::size_type min_dimension(const Vector2<T> &v) {
  return (v.x > v.y) ? 0 : 1;
}
template <typename T>
inline typename Vector3<T>::size_type min_dimension(const Vector3<T> &v) {
  return (v.x > v.y) ? ((v.x > v.z) ? 0 : 2) : ((v.y > v.z) ? 1 : 2);
}
template <typename T>
inline typename Vector4<T>::size_type min_dimension(const Vector4<T> &v) {
  return (v.x > v.y)
             ? ((v.x > v.z) ? ((v.x > v.w) ? 0 : 3) : ((v.z > v.w) ? 2 : 3))
             : ((v.y > v.z) ? ((v.y > v.w) ? 1 : 3) : ((v.z > v.w) ? 2 : 3));
}
template <typename T>
inline typename Point2<T>::size_type min_dimension(const Point2<T> &v) {
  return (v.x > v.y) ? 0 : 1;
}
template <typename T>
inline typename Point3<T>::size_type min_dimension(const Point3<T> &v) {
  return (v.x > v.y) ? ((v.x > v.z) ? 0 : 2) : ((v.y > v.z) ? 1 : 2);
}
template <typename T>
inline typename Point4<T>::size_type min_dimension(const Point4<T> &v) {
  return (v.x > v.y)
             ? ((v.x > v.z) ? ((v.x > v.w) ? 0 : 3) : ((v.z > v.w) ? 2 : 3))
             : ((v.y > v.z) ? ((v.y > v.w) ? 1 : 3) : ((v.z > v.w) ? 2 : 3));
}
template <typename T>
inline typename Normal2<T>::size_type min_dimension(const Normal2<T> &v) {
  return (v.x > v.y) ? 0 : 1;
}
template <typename T>
inline typename Normal3<T>::size_type min_dimension(const Normal3<T> &v) {
  return (v.x > v.y) ? ((v.x > v.z) ? 0 : 2) : ((v.y > v.z) ? 1 : 2);
}
template <typename T>
inline typename Normal4<T>::size_type min_dimension(const Normal4<T> &v) {
  return (v.x > v.y)
             ? ((v.x > v.z) ? ((v.x > v.w) ? 0 : 3) : ((v.z > v.w) ? 2 : 3))
             : ((v.y > v.z) ? ((v.y > v.w) ? 1 : 3) : ((v.z > v.w) ? 2 : 3));
}

template <typename T> inline Vector2<T> normalize(const Vector2<T> &v) {
  return v / v.length();
}
template <typename T> inline Vector3<T> normalize(const Vector3<T> &v) {
  return v / v.length();
}
template <typename T> inline Vector4<T> normalize(const Vector4<T> &v) {
  return v / v.length();
}
template <typename T> inline Normal2<T> normalize(const Normal2<T> &v) {
  return v / v.length();
}
template <typename T> inline Normal3<T> normalize(const Normal3<T> &v) {
  return v / v.length();
}
template <typename T> inline Normal4<T> normalize(const Normal4<T> &v) {
  return v / v.length();
}
} // namespace specula

#endif // SPECULA_GEOMETRIC_HPP_
