#ifndef SPECULA_BOUNDS_HPP_
#define SPECULA_BOUNDS_HPP_

#include "../../global.hpp"

#include "bounds2.hpp"
#include "bounds3.hpp"
#include "bounds4.hpp"

/**
 * @defgroup Bounds
 * @ingroup Math
 * @brief Standard `Bounds` classes and operations
 *
 * Many parts of the system operate on axis-aligned regions of space. The
 * `Bounds2`, `Bounds3`, and `Bounds4` template classes are used to represent
 * the extent of these sorts of regions. All are parametrized by a type `T`
 * that is used to represent the coordinates of its extents.
 *
 * There are a few possible representations for these sorts of bounding boxes,
 * this project uses axis-aligned bounding boxes, where the box edges are
 * mutually perpendicular and aligned with the coordinate system axes.
 *
 */

namespace specula {
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
Bounds4<T> Union(const Bounds4<T> &b, const Point4<T> &p) {
  Bounds4<T> ret;
  ret.p_min = min(b.p_min, p);
  ret.p_max = max(b.p_max, p);
  return ret;
}
template <typename T>
Bounds4<T> Union(const Bounds4<T> &b1, const Bounds4<T> &b2) {
  Bounds4<T> ret;
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
Bounds4<T> intersect(const Bounds4<T> &b1, const Bounds4<T> &b2) {
  Bounds3<T> ret;
  ret.p_min = max(b1.p_min, b2.p_min);
  ret.p_max = min(b1.p_max, b2.p_max);
  return ret;
}

template <typename T>
bool overlaps(const Bounds2<T> &b1, const Bounds2<T> &b2) {
  bool x = (b1.p_max.x >= b2.p_min.x) && (b1.p_min.x <= b2.p_max.x);
  bool y = (b1.p_max.y >= b2.p_min.y) && (b1.p_min.y <= b2.p_max.y);
  return x && y;
}
template <typename T>
bool overlaps(const Bounds3<T> &b1, const Bounds3<T> &b2) {
  bool x = (b1.p_max.x >= b2.p_min.x) && (b1.p_min.x <= b2.p_max.x);
  bool y = (b1.p_max.y >= b2.p_min.y) && (b1.p_min.y <= b2.p_max.y);
  bool z = (b1.p_max.z >= b2.p_min.z) && (b1.p_min.z <= b2.p_max.z);
  return x && y && z;
}

template <typename T> bool inside(const Point2<T> &p, const Bounds2<T> &b) {
  return p.x >= b.p_min.x && p.x <= b.p_max.x && p.y >= b.p_min.y &&
         p.y <= b.p_max.y;
}
template <typename T> bool inside(const Point3<T> &p, const Bounds3<T> &b) {
  return p.x >= b.p_min.x && p.x <= b.p_max.x && p.y >= b.p_min.y &&
         p.y <= b.p_max.y && p.z >= b.p_min.z && &p.z <= b.p_max.z;
}
template <typename T> bool inside(const Point4<T> &p, const Bounds4<T> &b) {
  return p.x >= b.p_min.x && p.x <= b.p_max.x && p.y >= b.p_min.y &&
         p.y <= b.p_max.y && p.z >= b.p_min.z && p.z <= b.p_max.z &&
         p.w >= b.p_min.w && p.w <= b.p_max.w;
}

template <typename T>
bool inside_exclusive(const Point2<T> &p, const Bounds2<T> &b) {
  return p.x >= b.p_min.x && p.x < b.p_max.x && p.y >= b.p_min.y &&
         p.y < b.p_max.y;
}
template <typename T>
bool inside_exclusive(const Point3<T> &p, const Bounds3<T> &b) {
  return p.x >= b.p_min.x && p.x < b.p_max.x && p.y >= b.p_min.y &&
         p.y < b.p_max.y && p.z >= b.p_min.z && &p.z < b.p_max.z;
}
template <typename T>
bool inside_exclusive(const Point4<T> &p, const Bounds4<T> &b) {
  return p.x >= b.p_min.x && p.x < b.p_max.x && p.y >= b.p_min.y &&
         p.y < b.p_max.y && p.z >= b.p_min.z && p.z < b.p_max.z &&
         p.w >= b.p_min.w && p.w < b.p_max.w;
}

template <typename T, typename U>
inline Bounds2<T> expand(const Bounds2<T> &b, U delta) {
  return Bounds2<T>(b.p_min - Vector2<T>(delta, delta),
                    b.p_max + Vector2<T>(delta, delta));
}
template <typename T, typename U>
inline Bounds3<T> expand(const Bounds3<T> &b, U delta) {
  return Bounds3<T>(b.p_min - Vector3<T>(delta, delta, delta),
                    b.p_max + Vector3<T>(delta, delta, delta));
}
template <typename T, typename U>
inline Bounds4<T> expand(const Bounds4<T> &b, U delta) {
  return Bounds4<T>(b.p_min - Vector4<T>(delta, delta, delta, delta),
                    b.p_max + Vector4<T>(delta, delta, delta, delta));
}
} // namespace specula

#endif // SPECULA_BOUNDS_HPP_