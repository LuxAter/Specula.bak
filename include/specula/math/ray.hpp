#ifndef SPECULA_RAY_HPP_
#define SPECULA_RAY_HPP_

#include "point/point3.hpp"
#include "vector/vector3.hpp"

#include "../fmt.hpp"
#include "../types.hpp"

namespace specula {
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
  // TODO: Update to medium class
  const void *medium;
};

inline std::ostream &operator<<(std::ostream &out, const Ray &r) {
  return out << r.fmt();
}
} // namespace specula

#endif // SPECULA_RAY_HPP_
