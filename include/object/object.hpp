#ifndef SPECULA_OBJECT_OBJECT_HPP_
#define SPECULA_OBJECT_OBJECT_HPP_

#include <functional>

#include "../math/math.hpp"
#include "material.hpp"
#include "distance_estimator.hpp"

namespace specula {
namespace object {
  class Object {
   public:
    Object();

    double DE(const math::Vec3d& p) const;

    Material mat;

   protected:
    math::Mat4d trans_, trans_inv_;
    std::function<double(const math::Vec3d&)> de_;
  };
}  // namespace object
}  // namespace specula

#endif  // SPECULA_OBJECT_OBJECT_HPP_
