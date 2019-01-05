#include "object/plane.hpp"
#include "object/object.hpp"

#include "math/math.hpp"

specula::object::Plane::Plane(const math::Vec3d& origin,
                              const math::Vec3d& normal, Material mat)
    : Object(mat), origin_(origin), normal_(normal) {}

double specula::object::Plane::DE(const math::Vec3d& p) {
  return math::dot(normal_, (p - origin_)) / math::length(normal_);
}

std::unique_ptr<specula::object::Object> specula::object::GeneratePlane(
    const math::Vec3d& origin, const math::Vec3d& normal, Material mat) {
  return std::unique_ptr<Object>(new Plane(origin, normal, mat));
}
