#ifndef SPECULA_OBJECT_SPHERE_HPP_
#define SPECULA_OBJECT_SPHERE_HPP_

#include <memory>

#include "../math/math.hpp"
#include "material.hpp"
#include "object.hpp"

namespace specula {
namespace object {
  class Sphere : public Object {
   public:
    Sphere(const math::Vec3d& origin, const double& radius, Material mat = Material());

    virtual double DE(const math::Vec3d& p);

    math::Vec3d origin_;
    double radius_, radius_square_;
  };

  std::unique_ptr<Object> GenerateSphere(const math::Vec3d& origin, const double& radius,
                                         Material mat = Material());

}  // namespace object
}  // namespace specula

#endif  // SPECULA_OBJECT_SPHERE_HPP_
