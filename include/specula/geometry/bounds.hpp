#ifndef SPECULA_BOUNDS_HPP_
#define SPECULA_BOUNDS_HPP_

#include <cmath>

#include "bounds2.hpp"
#include "bounds3.hpp"
#include "point2.hpp"
#include "point3.hpp"
#include "vector2.hpp"
#include "vector3.hpp"

namespace specula {
template <typename T>
Bounds3<T> union(const Bounds3<T> &b, const Point3<T> &p) {
  return Bounds3<T>(
      Point3<T>(std::min(b.p_min.x, p.x), std::min(b.p_min.y, p.y),
                std::min(b.p_min.z, p.z)),
      Point3<T>(std::max(b.p_max.x, p.x), std::max(b.p_max.y, p.y),
                std::max(b.p_max.z, p.z)));
}
template <typename T>
Bounds3<T> union(const Bounds3<T> &b1, const Bounds3<T> &b2) {
  return Bounds3<T>(Point3<T>(std::min(b1.p_min.x, b2.p_min.x),
                              std::min(b1.p_min.y, b2.p_min.y),
                              std::min(b1.p_min.z, b2.p_min.z)),
                    Point3<T>(std::max(b1.p_max.x, b2.p_max.x),
                              std::max(b1.p_max.y, b2.p_max.y),
                              std::max(b1.p_max.z, b2.p_max.z)));
}
template <typename T>
Bounds3<T> intersect(const Bounds3<T> &b1, const Bounds3<T> &b2) {
  return Bounds3<T>(Point3<T>(std::max(b1.p_min.x, b2.p_min.x),
                              std::max(b1.p_min.y, b2.p_min.y),
                              std::max(b1.p_min.z, b2.p_min.z)),
                    Point3<T>(std::min(b1.p_max.x, b2.p_max.x),
                              std::min(b1.p_max.y, b2.p_max.y),
                              std::min(b1.p_max.z, b2.p_max.z)));
}
template <typename T>
bool overlaps(const Bounds3<T> &b1, const Bounds3<T> &b2) {
  bool x = (b1.p_max.x >= b2.p_min.x) && (b1.p_min.x <= b2.p_max.x);
  bool y = (b1.p_max.y >= b2.p_min.y) && (b1.p_min.y <= b2.p_max.y);
  bool z = (b1.p_max.z >= b2.p_min.z) && (b1.p_min.z <= b2.p_max.z);
  return (x && y && z);
}
template <typename T> bool inside(const Point3<T> &p, const Bounds3<T> &b) {
  return (p.x >= b.p_min.x && p.x <= b.p_max.x && p.y >= b.p_min.y &&
          p.y <= b.p_max.y && p.z >= b.p_min.z && p.z <= b.p_max.z);
}
template <typename T>
bool inside_exclusive(const Point3<T> &p, const Bounds3<T> &b) {
  return (p.x >= b.p_min.x && p.x < b.p_max.x && p.y >= b.p_min.y &&
          p.y < b.p_max.y && p.z >= b.p_min.z && p.z < b.p_max.z);
}
template <typename T, typename U>
inline Bounds3<T> expand(const Bounds3<T> &b, const U &delta) {
  return Bounds3<T>(b.p_min - Vector3<T>(delta, delta, delta),
                    b.p_max + Vector3<T>(delta, delta, delta));
}

} // namespace specula

#endif // SPECULA_BOUNDS_HPP_