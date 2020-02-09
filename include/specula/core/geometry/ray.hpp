#ifndef SPECULA_CORE_GEOMETRY_RAY_HPP_
#define SPECULA_CORE_GEOMETRY_RAY_HPP_

#include "specula/global.hpp"

#include "point.hpp"
#include "vector.hpp"

namespace specula {
class Ray {
public:
  Ray() : t_max(INFTY), time(0.0f), medium(nullptr) {}
  Ray(const Point3f &o, const Vector3f &d, Float t_max = INFTY,
      Float time = 0.0f, const Medium *medium = nullptr)
      : o(o), d(d), t_max(t_max), time(time), medium(medium) {}

  Point3f operator()(Float t) const { return o + d * t; }
  inline bool has_nans() const SPECULA_NOEXCEPT {
    return o.has_nans() || d.has_nans() || std::isnan(t_max);
  }

  inline std::string fmt() const {
    return fmt::format("[o={}, d={}, t_max={}, time={}]", o, d, t_max, time);
  }

  Point3f o;
  Vector3f d;
  mutable Float t_max;
  Float time;
  const Medium *medium;
};

class RayDifferential : public Ray {
public:
  RayDifferential() : has_differentials(false) {}
  RayDifferential(const Point3f &o, const Vector3f &d, Float t_max = INFTY,
                  Float time = 0.0f, const Medium *medium = nullptr)
      : Ray(o, d, t_max, time, medium), has_differentials(false) {}
  RayDifferential(const Ray &ray) : Ray(ray), has_differentials(false) {}
  inline bool has_nans() const SPECULA_NOEXCEPT {
    return Ray::has_nans() ||
           (has_differentials &&
            (rx_origin.has_nans() || ry_origin.has_nans() ||
             rx_direction.has_nans() || ry_direction.has_nans()));
  }
  void scale_differentials(Float s) {
    rx_origin = o + (rx_origin - o) * s;
    ry_origin = o + (ry_origin - o) * s;
    rx_direction = d + (rx_direction - d) * s;
    ry_direction = d + (ry_direction - d) * s;
  }

  inline std::string fmt() const {
    return fmt::format("[{}, has_differentials={}, xo={}, xd={}, yo={}, yd={}]",
                       Ray::fmt(), has_differentials, rx_origin, rx_direction,
                       ry_origin, ry_direction);
  }

  bool has_differentials;
  Point3f rx_origin, ry_origin;
  Vector3f rx_direction, ry_direction;
};
} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_RAY_HPP_