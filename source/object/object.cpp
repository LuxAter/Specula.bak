#include "object/object.hpp"

#include <functional>
#include <limits>

#include "math/math.hpp"
#include "object/distance_estimator.hpp"
#include "object/material.hpp"

specula::object::Object::Object()
    : mat(Material()),
      scale_(1),
      trans_(1),
      trans_inv_(1),
      de_([](const math::vec3<double>& p) {
        return std::numeric_limits<double>::infinity();
      }) {}

specula::object::Object::Object(std::function<double(const math::vec3<double>&)> de,
                                Material mat)
    : mat(mat), scale_(1), trans_(1), trans_inv_(1), de_(de) {}

void specula::object::Object::Translate(const math::vec3<double>& t) {
  math::translate(trans_, trans_inv_, t);
}
void specula::object::Object::Scale(const math::vec3<double>& s) {
  // de_ = Streach(de, s);
}
void specula::object::Object::Scale(const double& s) { scale_ *= s; }
void specula::object::Object::RotateX(const double& radians) {
  math::rotateX(trans_, trans_inv_, radians);
}
void specula::object::Object::RotateY(const double& radians) {
  math::rotateY(trans_, trans_inv_, radians);
}
void specula::object::Object::RotateZ(const double& radians) {
  math::rotateZ(trans_, trans_inv_, radians);
}

double specula::object::Object::DE(const math::vec3<double>& p) const {
  return de_(trans_inv_ * (1.0 / scale_) * p) * scale_;
}
