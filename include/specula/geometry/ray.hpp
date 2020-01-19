#ifndef SPECULA_GEOMETRY_RAY_HPP_
#define SPECULA_GEOMETRY_RAY_HPP_

#include <limits>

#include "../compiler.hpp"
#include "../preprocessor.hpp"

#include "point3.hpp"
#include "vector3.hpp"

namespace specula {

class Ray {
public:
  Ray()
      : o(), d(), t_max(std::numeric_limits<Float>::infinity()), time(0.0f),
        medium(nullptr) {}
  Ray(const Point3f &o, const Vector3f &d,
      Float t_max = std::numeric_limits<Float>::infinity(), Float time = 0.00f,
      const void *medium = nullptr)
      : o(o), d(d), t_max(t_max), time(time), medium(medium) {}

  inline Point3f operator()(const Float t) const { return o + d * t; }

  Point3f o;
  Vector3f d;
  mutable Float t_max;
  Float time;

  // TODO Change to const Medium* once Medium has been implemented
  const void *medium;
};
} // namespace specula

#endif // SPECULA_GEOMETRY_RAY_HPP_