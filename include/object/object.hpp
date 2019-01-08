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
    Object(std::function<double(const math::vec3&)> de,
           Material mat = Material());

    void Translate(const math::vec3& t);
    void Scale(const math::vec3& s);
    void Scale(const double& s);
    void RotateX(const double& radians);
    void RotateY(const double& radians);
    void RotateZ(const double& radians);

    double DE(const math::vec3& p) const;

    Material mat;

   protected:
    double scale_;
    math::mat4 trans_, trans_inv_;
    std::function<double(const math::vec3&)> de_;
  };
}  // namespace object
}  // namespace specula

#endif  // SPECULA_OBJECT_OBJECT_HPP_
