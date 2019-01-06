#include "object/object.hpp"

#include <functional>
#include <limits>

#include "math/math.hpp"
#include "object/distance_estimator.hpp"
#include "object/material.hpp"

specula::object::Object::Object()
    : mat(Material()), trans_(1), trans_inv_(1), de_([](const math::Vec3d& p) {
        return std::numeric_limits<double>::infinity();
      }) {}

specula::object::Object::Object(std::function<double(const math::Vec3d&)> de,
                                Material mat)
    : mat(mat), trans_(1), trans_inv_(1), de_(de) {}

void specula::object::Object::Translate(const math::Vec3d& t) {
  auto res = math::translate(trans_, trans_inv_, t);
  trans_ = res.first;
  trans_inv_ = res.second;
}
void specula::object::Object::Scale(const math::Vec3d& s) {
  auto res = math::scale(trans_, trans_inv_, s);
  trans_ = res.first;
  trans_inv_ = res.second;
}
void specula::object::Object::Scale(const double& s) {
  auto res = math::scale(trans_, trans_inv_, {s, s, s});
  trans_ = res.first;
  trans_inv_ = res.second;
}
void specula::object::Object::RotateX(const double& radians) {
  auto res = math::rotateX(trans_, trans_inv_, radians);
  trans_ = res.first;
  trans_inv_ = res.second;
}
void specula::object::Object::RotateY(const double& radians) {
  auto res = math::rotateY(trans_, trans_inv_, radians);
  trans_ = res.first;
  trans_inv_ = res.second;
}
void specula::object::Object::RotateZ(const double& radians) {
  auto res = math::rotateZ(trans_, trans_inv_, radians);
  trans_ = res.first;
  trans_inv_ = res.second;
}

double specula::object::Object::DE(const math::Vec3d& p) const {
  // std::cout << p << "->" << trans_inv_ * p << "->";
  double d = de_(trans_inv_ * p) *
         std::max(std::max(trans_(0, 0), trans_(1, 1)), trans_(2, 2));
  // std::cout << d << "\n";
  return d;
}
