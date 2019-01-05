#include "object/sphere.hpp"
#include "object/object.hpp"

#include "math/math.hpp"

specula::object::Sphere::Sphere(const double& radius, Material mat)
    : Object(mat), radius_(radius), radius_square_(radius * radius) {}

double specula::object::Sphere::DE(const math::Vec3d& p) {
  return math::length(math::Vec3d(mat_inv_ * p)) - radius_;
}
