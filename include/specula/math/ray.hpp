#ifndef SPECULA_RAY_HPP_
#define SPECULA_RAY_HPP_

#include "../global.hpp"

#include "point/point3.hpp"
#include "vector/vector3.hpp"

/**
 * @addtogroup Ray
 * @ingroup Math
 * @brief Ray classes and operations
 *
 * This module implements a `Ray` class that is commonly used throught
 * rendering. The ray consists of both an origin which is a `Point3<T>`, and a
 * direction which is stored as a `Vector3<T>`.
 *
 * A *ray* is a semi-infinite line specified by its origin and direction. We
 * represent a Ray with a `Point3f` for the origin and a `Vector3f` for the
 * direction. We only need rays with floating-point origins and directions, so
 * `Ray` isn't a template class parametrized by an arbitrary type, as points,
 * vectors anre normals were.
 *
 */

namespace specula {
/**
 * @ingroup Ray
 * @brief Core ray class
 *
 * This class implements the primary ray class, and is used for all ray tracing
 * and ray marching metods. The `Ray` also includes a member variable that
 * limits the ray to a segment along its infinite extent. Each ray also records
 * the medium containing its origin.
 *
 */
class Ray {
public:
  Ray()
      : o(), d(), t_max(std::numeric_limits<Float>::infinity()), time(0.0f),
        medium(nullptr) {}
  Ray(const Point3f &o, const Vector3f &d,
      Float t_max = std::numeric_limits<Float>::infinity(), Float time = 0.0f,
      const void *medium = nullptr)
      : o(o), d(d), t_max(t_max), time(time), medium(medium) {}
  inline Point3f operator()(Float t) const { return o + d * t; }

  inline std::string fmt() const {
    return fmt::format("[o={}, d={}, t_max={}, time={}]", o, d, t_max, time);
  }

  Point3f o;
  Vector3f d;
  mutable Float t_max;
  Float time;
  /**
   * @todo Update this pointer to be the Medium class.
   */
  const void *medium;
};

inline std::ostream &operator<<(std::ostream &out, const Ray &r) {
  return out << r.fmt();
}
} // namespace specula

#endif // SPECULA_RAY_HPP_
