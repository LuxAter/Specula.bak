#ifndef SPECULA_OBJECT_OBJECT_HPP_
#define SPECULA_OBJECT_OBJECT_HPP_

#include <functional>
#include <limits>

#include "../math/math.hpp"
#include "distance_estimator.hpp"
#include "material.hpp"

namespace specula {
namespace object {
  class Object {
   public:
    Object();
    Object(std::function<double(const math::Vec3d&)> de,
           Material mat = Material());


    void Translate(const math::Vec3d& t);
    void Scale(const math::Vec3d& s);
    void Scale(const double& s);
    void RotateX(const double& radians);
    void RotateY(const double& radians);
    void RotateZ(const double& radians);

    double DE(const math::Vec3d& p) const;

    Material mat;

   protected:
    math::Mat4d trans_, trans_inv_;
    std::function<double(const math::Vec3d&)> de_;
  };
}  // namespace object
}  // namespace specula

#endif  // SPECULA_OBJECT_OBJECT_HPP_
