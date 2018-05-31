#ifndef SPECULA_OBJECT_PLANE_HPP_
#define SPECULA_OBJECT_PLANE_HPP_

#include <memory>

#include "basic/matrix.hpp"
#include "basic/vector.hpp"

#include "../material.hpp"
#include "../object.hpp"

namespace specula {
  class Plane : public Object {
    public:
      Plane(const estl::base::Vec3d& origin,
          const estl::base::Vec3d& normal, Material mat = Material());
    bool Intersect(const estl::base::Vec3d& start,
                   const estl::base::Vec3d& dir, IntersectData& inter);
    protected:
    double constant_;
    estl::base::Vec3d origin_, normal_;
  };
} // namespace specula

#endif  // SPECULA_OBJECT_PLANE_HPP_
