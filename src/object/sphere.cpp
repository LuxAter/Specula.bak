#include "object/sphere.hpp"
#include "object.hpp"

#include <memory>

#include "basic/matrix.hpp"
#include "basic/vector.hpp"

#include "material.hpp"

specula::Sphere::Sphere(const double& r, Material mat)
    : Object(mat), radius_(r), radiux_sq_(r * r) {}

bool specula::Sphere::Intersect(const estl::base::Vec3d& start,
                                const estl::base::Vec3d& dir,
                                IntersectData& inter) {
  estl::base::Vec3d local = Dot(inv_, start);
  double t0, t1;
  double a = Dot(dir, dir);
  double b = 2 * Dot(dir, local);
  double c = Dot(local, local) - radiux_sq_;
  if (Quad(a, b, c, t0, t1) == false) {
    return false;
  }
  if (t0 > t1) {
    std::swap(t0, t1);
  }
  if (t0 < 0) {
    if (t1 < 0) {
      return false;
    }
    inter.near = t1;
  } else {
    inter.near = t0;
  }
  inter.mat = mat_;
  inter.point = start + (dir * inter.near);
  inter.normal = estl::base::Normalize(local + (dir * inter.near));
  return true;
}

bool specula::Sphere::Quad(double a, double b, double c, double& x0, double& x1){
  double discr = (b * b) - (4 * a * c);
  if (discr < 0){
    return false;
  }else if(discr == 0){
    x0 = x1 = -0.5 * b / a;
  }else{
    double q = (b > 0) ? -0.5 * (b+sqrt(discr)) : -0.5 * (b-sqrt(discr));
    x0 = q / a;
    x1 = c / q;
  }
  return true;
}
