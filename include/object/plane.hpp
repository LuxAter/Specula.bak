#ifndef SPECULA_OBJECT_PLANE_HPP_
#define SPECULA_OBJECT_PLANE_HPP_

#include "../math/math.hpp"
#include "material.hpp"
#include "object.hpp"

namespace specula {
namespace object {
  class Plane : public Object {
   public:
    Plane(const math::Vec3d& origin, const math::Vec3d& normal,
          Material mat = Material());

    virtual double DE(const math::Vec3d& p);

    math::Vec3d origin_, normal_;
  };

  std::unique_ptr<Object> GeneratePlane(const math::Vec3d& origin,
                                        const math::Vec3d& normal,
                                        Material mat = Material());
}  // namespace object
}  // namespace specula

#endif  // SPECULA_OBJECT_PLANE_HPP_
