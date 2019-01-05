#include "object/object.hpp"

#include <limits>
#include <memory>

#include "math/math.hpp"

specula::object::Object::Object()
    : material_(Material()), mat_(1), mat_inv_(1) {}
specula::object::Object::Object(Material mat)
    : material_(mat), mat_(1), mat_inv_(1) {}
specula::object::Object::~Object() {}

void specula::object::Object::Translate(const math::Vec3d& pos) {
  math::Mat4d trans(1);
  trans(0, 3) = pos.x;
  trans(1, 3) = pos.y;
  trans(2, 3) = pos.z;
  mat_ = trans * mat_;
  trans(0, 3) = -pos.x;
  trans(1, 3) = -pos.x;
  trans(2, 3) = -pos.x;
  mat_inv_ = mat_inv_ * trans;
}

double specula::object::Object::DE(const math::Vec3d& p) {
  return std::numeric_limits<double>::infinity();
}

std::unique_ptr<specula::object::Object> specula::object::GenerateObject(
    Material mat) {
  return std::unique_ptr<Object>(new Object(mat));
}
