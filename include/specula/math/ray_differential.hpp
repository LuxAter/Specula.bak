#ifndef SPECULA_RAY_DIFFERENTIAL_HPP_
#define SPECULA_RAY_DIFFERENTIAL_HPP_

#include "ray.hpp"

#include "point/point3.hpp"
#include "vector/vector3.hpp"

#include "../fmt.hpp"
#include "../types.hpp"

namespace specula {
class RayDifferential : public Ray {
public:
  RayDifferential()
      : Ray(), has_differentials(false), rx_origin(), ry_origin(),
        rx_direction(), ry_direction() {}
  RayDifferential(const Point3f &o, const Vector3f &d,
                  Float t_max = std::numeric_limits<Float>::infinity(),
                  Float time = 0.0f, const void *medium = nullptr)
      : Ray(o, d, t_max, time, medium), has_differentials(false), rx_origin(),
        ry_origin(), rx_direction(), ry_direction() {}
  inline void scale_differentials(Float s) {
    rx_origin = o + (rx_origin - o) * s;
    ry_origin = o + (ry_origin - o) * s;
    rx_direction = d + (rx_direction - d) * s;
    ry_direction = d + (ry_direction - d) * s;
  }

  inline std::string fmt() const {
    return fmt::format("[{}, has_differentials={}, xo={}, dx={}, yo={},yd={}]",
                       static_cast<const Ray &>(*this).fmt(),
                       has_differentials ? "true" : "false", rx_origin,
                       rx_direction, ry_origin, ry_direction);
  }

  bool has_differentials;
  Point3f rx_origin, ry_origin;
  Vector3f rx_direction, ry_direction;
};
inline std::ostream &operator<<(std::ostream &out, const RayDifferential &r) {
  return out << r.fmt();
}
} // namespace specula

#endif // SPECULA_RAY_DIFFERENTIAL_HPP_
