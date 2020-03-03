#ifndef SPECULA_CORE_INTERACTION_HPP_
#define SPECULA_CORE_INTERACTION_HPP_

#include "../global.hpp"
#include "geometry.hpp"

namespace specula {
struct Interaction {
  Interaction(const Point3f &p, const Normal3f &n, const Vector3f &p_error,
              const Vector3f &wo, Float time,
              const MediumInterface &medium_interface)
      : p(p), time(time), p_error(p_error), wo(wo), n(n),
        medium_interface(medium_interface) {}

  inline bool is_surface_interaction() const {
    return n !=Normal3f();
  }

  Point3f p;
  Float time;
  Vector3f p_error;
  Vector3f wo;
  Normal3f n;
  MediumInterface medium_interface;
};
} // namespace specula

#endif // SPECULA_CORE_INTERACTION_HPP_
