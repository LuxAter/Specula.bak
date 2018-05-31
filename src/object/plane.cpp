#include "object.hpp"
#include "object/plane.hpp"

#include <memory>

#include "basic/matrix.hpp"
#include "basic/vector.hpp"

#include "material.hpp"

specula::Plane::Plane(const estl::base::Vec3d& origin,
                      const estl::base::Vec3d& normal, Material mat)
    : Object(mat),
      constant_(estl::base::Dot(origin, normal)),
      origin_(origin),
      normal_(estl::base::Normalize(normal)) {}

bool specula::Plane::Intersect(const estl::base::Vec3d& start,
                                const estl::base::Vec3d& dir,
                                IntersectData& inter) {
  estl::base::Vec3d local = estl::base::Dot(inv_, start);
  double a = estl::base::Dot(normal_, dir);
  double b = constant_ + estl::base::Dot(normal_, local);
  if (a == 0) {
    return false;
  } else if (b / a < 0) {
    return false;
  }
  inter.near = b / a;
  inter.mat = mat_;
  inter.point = start + (dir * inter.near);
  inter.normal = normal_;
  return true;
}
