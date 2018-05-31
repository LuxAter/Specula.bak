#include "object/circle.hpp"
#include "object.hpp"

#include <memory>

#include "basic/matrix.hpp"
#include "basic/vector.hpp"

#include "material.hpp"

specula::Circle::Circle(const estl::base::Vec3d& origin, const estl::base::Vec3d& normal, const double& radius, Material mat)
    : Object(mat), radius_(radius), constant_(-estl::base::Dot(origin, normal)), origin_(origin), normal_(Normalize(normal)){}

bool specula::Circle::Intersect(const estl::base::Vec3d& start,
                                const estl::base::Vec3d& dir,
                                IntersectData& inter) {
  estl::base::Vec3d local = Dot(inv_, start);
  double a = estl::base::Dot(normal_, dir);
  double b = estl::base::Dot(normal_, local) - constant_;
  if(a == 0){
    return false;
  }else if(b / a < 0){
    return false;
  }
  inter.near = b / a;
  inter.mat = mat_;
  inter.point = start + (dir * inter.near);
  inter.normal = normal_;
  estl::base::Vec3d dist = inter.point - origin_;
  if(estl::base::Length(dist) > radius_){
    return false;
  }
  return true;
}

