#ifndef SPECULA_OBJECT_SPHERE_HPP_
#define SPECULA_OBJECT_SPHERE_HPP_

#include <memory>

#include "basic/matrix.hpp"
#include "basic/vector.hpp"

#include "../material.hpp"
#include "../object.hpp"

namespace specula {
  class Sphere : public Object {
   public:
    Sphere(const double& r, Material mat = Material());
    bool Intersect(const estl::base::Vec3d& start,
                   const estl::base::Vec3d& dir, IntersectData& inter);

   protected:
    bool Quad(double a, double b, double c, double& x0, double &x1);
  
    double radius_, radiux_sq_;
  };

  std::unique_ptr<Object> CreateObjectSphere(const double& r, Material mat = Material());
} // namespace specula

#endif  // SPECULA_OBJECT_SPHERE_HPP_
