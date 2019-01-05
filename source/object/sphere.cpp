#include "object/sphere.hpp"
#include "object/object.hpp"

#include <memory>

#include "math/math.hpp"

specula::object::Sphere::Sphere(const math::Vec3d& origin, const double& radius, Material mat)
    : Object(mat), origin_(origin), radius_(radius), radius_square_(radius * radius) {}

double specula::object::Sphere::DE(const math::Vec3d& p) {
  return math::length(origin_ - p) - radius_;
}

std::unique_ptr<specula::object::Object> specula::object::GenerateSphere(
    const math::Vec3d& origin, const double& radius, Material mat) {
  return std::unique_ptr<Object>(new Sphere(origin, radius, mat));
}
