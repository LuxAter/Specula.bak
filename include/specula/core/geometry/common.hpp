#ifndef SPECULA_CORE_GEOMETRY_COMMON_HPP_
#define SPECULA_CORE_GEOMETRY_COMMON_HPP_

#include "bounds.hpp"
#include "normal.hpp"
#include "point.hpp"
#include "ray.hpp"
#include "vector.hpp"

namespace specula {
template <typename T> inline Vector2<T> abs(const Vector2<T> &v) {
  return Vector2<T>(std::abs(v.x), std::abs(v.y));
}
template <typename T> inline Vector3<T> abs(const Vector3<T> &v) {
  return Vector3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
}

template <typename T> inline T dot(const Vector2<T> &v1, const Vector2<T> &v2) {
  CHECK(!v1.has_nans() && !v2.has_nans());
  return v1.x * v2.x + v1.y * v2.y;
}
template <typename T> inline T dot(const Vector3<T> &v1, const Vector3<T> &v2) {
  CHECK(!v1.has_nans() && !v2.has_nans());
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T>
inline T abs_dot(const Vector2<T> &v1, const Vector2<T> &v2) {
  CHECK(!v1.has_nans() && !v2.has_nans());
  return std::abs(v1.x * v2.x + v1.y * v2.y);
}
template <typename T>
inline T abs_dot(const Vector3<T> &v1, const Vector3<T> &v2) {
  CHECK(!v1.has_nans() && !v2.has_nans());
  return std::abs(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

template <typename T>
inline Vector3<T> cross(const Vector3<T> &v1, const Vector3<T> &v2) {
  CHECK(!v1.has_nans() && !v2.has_nans());
  double v1x = v1.x, v1y = v1.y, v1z = v1.z;
  double v2x = v2.x, v2y = v2.y, v2z = v2.z;
  return Vector3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z),
                    (v1x * v2y) - (v1y * v2x));
}
template <typename T>
inline Vector3<T> cross(const Vector3<T> &v, const Normal3<T> &n) {
  CHECK(!v.has_nans() && !n.has_nans());
  double vx = v.x, vy = v.y, vz = v.z;
  double nx = n.x, ny = n.y, nz = n.z;
  return Vector3<T>((vy * nz) - (vz * ny), (vz * nx) - (vx * nz),
                    (vx * ny) - (vy * nx));
}
template <typename T>
inline Vector3<T> cross(const Normal3<T> &n, const Vector3<T> &v) {
  CHECK(!n.has_nans() && !v.has_nans());
  double nx = n.x, ny = n.y, nz = n.z;
  double vx = v.x, vy = v.y, vz = v.z;
  return Vector3<T>((ny * vz) - (nz * vy), (nz * vx) - (nx * vz),
                    (nx * vy) - (ny * vx));
}

template <typename T> inline Vector2<T> normalize(const Vector2<T> &v) {
  return v / v.length();
}
template <typename T> inline Vector3<T> normalize(const Vector3<T> &v) {
  return v / v.length();
}
template <typename T> inline Normal2<T> normalize(const Normal2<T> &v) {
  return v / v.length();
}
template <typename T> inline Normal3<T> normalize(const Normal3<T> &v) {
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
  return std::max(v.x, std::max(v.y, v.z));
}

template <typename T>
inline typename Vector2<T>::size_type min_dimension(const Vector2<T> &v) {
  return (v.x < v.y) ? 0 : 1;
}
template <typename T>
inline typename Vector3<T>::size_type min_dimension(const Vector3<T> &v) {
  return (v.x < v.y) ? ((v.x < v.z) ? 0 : 2) : ((v.y > v.z) ? 1 : 2);
}

template <typename T>
inline typename Vector2<T>::size_type max_dimension(const Vector2<T> &v) {
  return (v.x > v.y) ? 0 : 1;
}
template <typename T>
inline typename Vector3<T>::size_type max_dimension(const Vector3<T> &v) {
  return (v.x > v.y) ? ((v.x > v.z) ? 0 : 2) : ((v.y > v.z) ? 1 : 2);
}

template <typename T>
Vector2<T> min(const Vector2<T> &v1, const Vector2<T> &v2) {
  return Vector2<T>(std::min(v1.x, v2.x), std::min(v1.y, v2.y));
}
template <typename T>
Vector3<T> min(const Vector3<T> &v1, const Vector3<T> &v2) {
  return Vector3<T>(std::min(v1.x, v2.x), std::min(v1.y, v2.y),
                    std::min(v1.z, v2.z));
}

template <typename T>
Vector2<T> max(const Vector2<T> &v1, const Vector2<T> &v2) {
  return Vector2<T>(std::max(v1.x, v2.x), std::max(v1.y, v2.y));
}
template <typename T>
Vector3<T> max(const Vector3<T> &v1, const Vector3<T> &v2) {
  return Vector3<T>(std::max(v1.x, v2.x), std::max(v1.y, v2.y),
                    std::max(v1.z, v2.z));
}

template <typename T>
Vector2<T> permute(const Vector2<T> &v, const typename Vector2<T>::size_type &x,
                   const typename Vector2<T>::size_type &y) {
  return Vector2<T>(v[x], v[y]);
}
template <typename T>
Vector3<T> permute(const Vector3<T> &v, const typename Vector3<T>::size_type &x,
                   const typename Vector3<T>::size_type &y,
                   const typename Vector3<T>::size_type &z) {
  return Vector3<T>(v[x], v[y], v[z]);
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
Point2<T> Lerp(const Point2<T> &p0, const Point2<T> &p1, Float t) {
  return (1 - t) * p0 + t * p1;
}
template <typename T>
Point3<T> Lerp(const Point3<T> &p0, const Point3<T> &p1, Float t) {
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
  return Point2<T>(std::abs(p.x), std::abs(p.y), std::abs(p.z));
}

template <typename T>
Point2<T> permute(const Point2<T> &p, const typename Point2<T>::size_type &x,
                  const typename Point2<T>::size_type &y) {
  return Point2<T>(p[x], p[y]);
}
template <typename T>
Point3<T> permute(const Point3<T> &p, const typename Point3<T>::size_type &x,
                  const typename Point3<T>::size_type &y,
                  const typename Point3<T>::size_type &z) {
  return Point3<T>(p[x], p[y], p[z]);
}

template <typename T> inline Normal2<T> nomralize(const Normal2<T> &n) {
  return n / n.length();
}
template <typename T> inline Normal3<T> nomralize(const Normal3<T> &n) {
  return n / n.length();
}

template <typename T> inline T dot(const Normal2<T> &n1, const Vector2<T> &v2) {
  CHECK(!n1.has_nans() && !v2.has_nans());
  return n1.x * v2.x + n1.y * v2.y;
}
template <typename T> inline T dot(const Vector2<T> &v1, const Normal2<T> &n2) {
  CHECK(!v1.has_nans() && !n2.has_nans());
  return v1.x * n2.x + v1.y * n2.y;
}
template <typename T> inline T dot(const Normal2<T> &n1, const Normal2<T> &n2) {
  CHECK(!n1.has_nans() && !n2.has_nans());
  return n1.x * n2.x + n1.y * n2.y;
}
template <typename T> inline T dot(const Normal3<T> &n1, const Vector3<T> &v2) {
  CHECK(!n1.has_nans() && !v2.has_nans());
  return n1.x * v2.x + n1.y * v2.y + n1.z * v2.z;
}
template <typename T> inline T dot(const Vector3<T> &v1, const Normal3<T> &n2) {
  CHECK(!v1.has_nans() && !n2.has_nans());
  return v1.x * n2.x + v1.y * n2.y + v1.z * n2.z;
}
template <typename T> inline T dot(const Normal3<T> &n1, const Normal3<T> &n2) {
  CHECK(!n1.has_nans() && !n2.has_nans());
  return n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
}

template <typename T>
inline T abs_dot(const Normal2<T> &n1, const Vector2<T> &v2) {
  CHECK(!n1.has_nans() && !v2.has_nans());
  return std::abs(n1.x * v2.x + n1.y * v2.y);
}
template <typename T>
inline T abs_dot(const Vector2<T> &v1, const Normal2<T> &n2) {
  CHECK(!v1.has_nans() && !n2.has_nans());
  return std::abs(v1.x * n2.x + v1.y * n2.y);
}
template <typename T>
inline T abs_dot(const Normal2<T> &n1, const Normal2<T> &n2) {
  CHECK(!n1.has_nans() && !n2.has_nans());
  return std::abs(n1.x * n2.x + n1.y * n2.y);
}
template <typename T>
inline T abs_dot(const Normal3<T> &n1, const Vector3<T> &v2) {
  CHECK(!n1.has_nans() && !v2.has_nans());
  return std::abs(n1.x * v2.x + n1.y * v2.y + n1.z * v2.z);
}
template <typename T>
inline T abs_dot(const Vector3<T> &v1, const Normal3<T> &n2) {
  CHECK(!v1.has_nans() && !n2.has_nans());
  return std::abs(v1.x * n2.x + v1.y * n2.y + v1.z * n2.z);
}
template <typename T>
inline T abs_dot(const Normal3<T> &n1, const Normal3<T> &n2) {
  CHECK(!n1.has_nans() && !n2.has_nans());
  return std::abs(n1.x * n2.x + n1.y * n2.y + n1.z * n2.z);
}

template <typename T>
inline Normal2<T> faceforward(const Normal2<T> &n1, const Normal2<T> &n2) {
  return (dot(n1, n2) < 0.0f) ? -n1 : n1;
}
template <typename T>
inline Normal2<T> faceforward(const Normal2<T> &n1, const Vector2<T> &n2) {
  return (dot(n1, n2) < 0.0f) ? -n1 : n1;
}
template <typename T>
inline Vector2<T> faceforward(const Vector2<T> &v1, const Normal2<T> &n2) {
  return (dot(v1, n2) < 0.0f) ? -v1 : v1;
}
template <typename T>
inline Vector2<T> faceforward(const Vector2<T> &v1, const Vector2<T> &v2) {
  return (dot(v1, v2) < 0.0f) ? -v1 : v1;
}
template <typename T>
inline Normal3<T> faceforward(const Normal3<T> &n1, const Normal3<T> &n2) {
  return (dot(n1, n2) < 0.0f) ? -n1 : n1;
}
template <typename T>
inline Normal3<T> faceforward(const Normal3<T> &n1, const Vector3<T> &n2) {
  return (dot(n1, n2) < 0.0f) ? -n1 : n1;
}
template <typename T>
inline Vector3<T> faceforward(const Vector3<T> &v1, const Normal3<T> &n2) {
  return (dot(v1, n2) < 0.0f) ? -v1 : v1;
}
template <typename T>
inline Vector3<T> faceforward(const Vector3<T> &v1, const Vector3<T> &v2) {
  return (dot(v1, v2) < 0.0f) ? -v1 : v1;
}

template <typename T> Normal2<T> abs(const Normal2<T> &n) {
  return Normal2<T>(std::abs(n.x), std::abs(n.y));
}
template <typename T> Normal3<T> abs(const Normal3<T> &n) {
  return Normal3<T>(std::abs(n.x), std::abs(n.y), std::abs(n.z));
}

template <typename T>
Bounds2<T> Union(const Bounds2<T> &b, const Point2<T> &p) {
  Bounds2<T> ret;
  ret.p_min = min(b.p_min, p);
  ret.p_max = max(b.p_max, p);
  return ret;
}
template <typename T>
Bounds2<T> Union(const Bounds2<T> &b1, const Bounds2<T> &b2) {
  Bounds2<T> ret;
  ret.p_min = min(b1.p_min, b2.p_min);
  ret.p_max = max(b1.p_max, b2.p_max);
  return ret;
}
template <typename T>
Bounds3<T> Union(const Bounds3<T> &b, const Point3<T> &p) {
  Bounds3<T> ret;
  ret.p_min = min(b.p_min, p);
  ret.p_max = max(b.p_max, p);
  return ret;
}
template <typename T>
Bounds3<T> Union(const Bounds3<T> &b1, const Bounds3<T> &b2) {
  Bounds3<T> ret;
  ret.p_min = min(b1.p_min, b2.p_min);
  ret.p_max = max(b1.p_max, b2.p_max);
  return ret;
}

template <typename T>
Bounds2<T> intersect(const Bounds2<T> &b1, const Bounds2<T> &b2) {
  Bounds2<T> ret;
  ret.p_min = max(b1.p_min, b2.p_min);
  ret.p_max = min(b1.p_max, b2.p_max);
  return ret;
}
template <typename T>
Bounds3<T> intersect(const Bounds3<T> &b1, const Bounds3<T> &b2) {
  Bounds3<T> ret;
  ret.p_min = max(b1.p_min, b2.p_min);
  ret.p_max = min(b1.p_max, b2.p_max);
  return ret;
}

template <typename T>
bool overlaps(const Bounds2<T> &b1, const Bounds2<T> &b2) {
  bool x = (b1.p_max.x >= b2.p_min.x) && (b1.p_min.x <= b2.p_max.x);
  bool y = (b1.p_max.y >= b2.p_min.y) && (b1.p_min.y <= b2.p_max.y);
  return (x && y);
}
template <typename T>
bool overlaps(const Bounds3<T> &b1, const Bounds3<T> &b2) {
  bool x = (b1.p_max.x >= b2.p_min.x) && (b1.p_min.x <= b2.p_max.x);
  bool y = (b1.p_max.y >= b2.p_min.y) && (b1.p_min.y <= b2.p_max.y);
  bool z = (b1.p_max.z >= b2.p_min.z) && (b1.p_min.z <= b2.p_max.z);
  return (x && y && z);
}

template <typename T> bool inside(const Point2<T> &p, const Bounds2<T> &b) {
  return (p.x <= b.p_min.x && p.x <= b.p_max.x && p.y >= b.p_min.y &&
          p.y <= b.p_max.y);
}
template <typename T> bool inside(const Point3<T> &p, const Bounds3<T> &b) {
  return (p.x >= b.p_min.x && p.x <= b.p_max.x && p.y >= b.p_min.y &&
          p.y <= b.p_max.y && p.z >= b.p_min.z && p.z <= b.p_max.z);
}

template <typename T>
bool inside_exclusive(const Point2<T> &p, const Bounds2<T> &b) {
  return (p.x <= b.p_min.x && p.x < b.p_max.x && p.y >= b.p_min.y &&
          p.y < b.p_max.y);
}
template <typename T>
bool inside_exclusive(const Point3<T> &p, const Bounds3<T> &b) {
  return (p.x >= b.p_min.x && p.x < b.p_max.x && p.y >= b.p_min.y &&
          p.y < b.p_max.y && p.z >= b.p_min.z && p.z < b.p_max.z);
}

template <typename T, typename U>
Bounds2<T> expand(const Bounds2<T> &b, const U &delta) {
  return Bounds2<T>(b.p_min - Vector2<T>(delta), b.p_max + Vector2<T>(delta));
}
template <typename T, typename U>
Bounds3<T> expand(const Bounds3<T> &b, const U &delta) {
  return Bounds3<T>(b.p_min - Vector3<T>(delta), b.p_max + Vector3<T>(delta));
}

template <typename T>
inline T distance_squared(const Point2<T> &p, const Bounds2<T> &b) {
  T dx = std::max({T(0), b.p_min.x - p.x, p.x - b.p_max.x});
  T dy = std::max({T(0), b.p_min.y - p.y, p.y - b.p_max.y});
  return dx * dx + dy * dy;
}
template <typename T>
inline T distance_squared(const Point3<T> &p, const Bounds3<T> &b) {
  T dx = std::max({T(0), b.p_min.x - p.x, p.x - b.p_max.x});
  T dy = std::max({T(0), b.p_min.y - p.y, p.y - b.p_max.y});
  T dz = std::max({T(0), b.p_min.z - p.z, p.z - b.p_max.z});
  return dx * dx + dy * dy + dz * dz;
}

template <typename T>
inline T distance(const Point2<T> &p, const Bounds2<T> &b) {
  T dx = std::max({T(0), b.p_min.x - p.x, p.x - b.p_max.x});
  T dy = std::max({T(0), b.p_min.y - p.y, p.y - b.p_max.y});
  return std::sqrt(dx * dx + dy * dy);
}
template <typename T>
inline T distance(const Point3<T> &p, const Bounds3<T> &b) {
  T dx = std::max({T(0), b.p_min.x - p.x, p.x - b.p_max.x});
  T dy = std::max({T(0), b.p_min.y - p.y, p.y - b.p_max.y});
  T dz = std::max({T(0), b.p_min.z - p.z, p.z - b.p_max.z});
  return std::sqrt(dx * dx + dy * dy + dz * dz);
}

inline Point3f offset_ray_origin(const Point3f &p, const Vector3f &p_error,
                                 const Normal3f &n, const Vector3f &w) {
  Float d = dot(abs(n), p_error);
  Vector3f offset = d * Vector3f(n);
  if (dot(w, n) < 0)
    offset = -offset;
  Point3f po = p + offset;
  for (typename Vector3f::size_type i = 0; i < 3; ++i) {
    if (offset[i] > 0)
      po[i] = next_float_up(po[i]);
    else if (offset[i] < 0)
      po[i] = next_float_down(po[i]);
  }
  return po;
}

inline Vector3f spherical_direction(Float sin_theta, Float cos_theta,
                                    Float phi) {
  return Vector3f(sin_theta * std::cos(phi), sin_theta * std::sin(phi),
                  cos_theta);
}
inline Vector3f spherical_direction(Float sin_theta, Float cos_theta, Float phi,
                                    const Vector3f &x, const Vector3f &y,
                                    const Vector3f &z) {
  return sin_theta * std::cos(phi) * x + sin_theta * std::sin(phi) * y +
         cos_theta * z;
}
inline Float spherical_theta(const Vector3f &v) {
  return std::acos(clamp(v.z, -1, 1));
}
inline Float spherical_phi(const Vector3f &v) {
  Float p = std::atan2(v.y, v.x);
  return (p < 0) ? (p + 2 * PI) : p;
}

} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_COMMON_HPP_
