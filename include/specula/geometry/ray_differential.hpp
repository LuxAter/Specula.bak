#ifndef SPECULA_RAY_DIFFERENTIAL_HPP_
#define SPECULA_RAY_DIFFERENTIAL_HPP_

#include "../compiler.hpp"
#include "../preprocessor.hpp"

#include "point3.hpp"
#include "ray.hpp"
#include "vector3.hpp"

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
  RayDifferential(const Ray &ray)
      : Ray(ray), has_differentials(false), rx_origin(), ry_origin(),
        rx_direction(), ry_direction() {}

  void scale_differentials(const Float &s) {
    rx_origin = o + (rx_origin - o) * s;
    ry_origin = o + (ry_origin - o) * s;
    rx_direction = d + (rx_direction - d) * s;
    ry_direction = d + (ry_direction - d) * s;
  }

  bool has_differentials;
  Point3f rx_origin, ry_origin;
  Vector3f rx_direction, ry_direction;
};
} // namespace specula

#endif // SPECULA_RAY_DIFFERENTIAL_HPP_