#ifndef SPECULA_OBJECT_SPHERE_HPP_
#define SPECULA_OBJECT_SPHERE_HPP_

#include "material.hpp"
#include "object.hpp"
#include "../math/math.hpp"

namespace specula {
  namespace object {
    class Sphere : public Object {
      public:
      Sphere(const double& radius, Material mat = Material());

      virtual double DE(const math::Vec3d& p);

      double radius_, radius_square_;

    };
  } // namespace object
} // namespace specula

#endif  // SPECULA_OBJECT_SPHERE_HPP_
