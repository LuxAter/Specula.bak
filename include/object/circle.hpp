#ifndef SPECULA_OBJECT_CIRCLE_HPP_
#define SPECULA_OBJECT_CIRCLE_HPP_

#include <memory>

#include "basic/matrix.hpp"
#include "basic/vector.hpp"

#include "../material.hpp"
#include "../object.hpp"

namespace specula {
  class Circle : public Object {
   public:
    Circle (const estl::base::Vec3d& origin, const estl::base::Vec3d& normal, const double& radius, Material mat = Material());
    bool Intersect(const estl::base::Vec3d& start,
                   const estl::base::Vec3d& dir, IntersectData& inter);
  
   protected:
    double radius_, constant_; 
    estl::base::Vec3d origin_, normal_;
  };
} // namespace specula

#endif  // SPECULA_OBJECT_SPHERE_HPP_
