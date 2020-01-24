#include "specula/transform.hpp"

#include "specula/math/common.hpp"
#include "specula/math/geometric.hpp"
#include "specula/math/matrix/matrix4x4.hpp"
#include "specula/math/normal/normal3.hpp"
#include "specula/math/point/point3.hpp"
#include "specula/math/ray.hpp"
#include "specula/math/ray_differential.hpp"
#include "specula/math/vector/vector3.hpp"
#include "specula/preprocessor.hpp"
#include "specula/types.hpp"

specula::Transform::Transform() : m(), inv() {}
specula::Transform::Transform(const Float mat[4][4])
    : m(mat[0][0], mat[0][1], mat[0][2], mat[0][3], mat[1][0], mat[1][1],
        mat[1][2], mat[1][3], mat[2][0], mat[2][1], mat[2][2], mat[2][3],
        mat[3][0], mat[3][1], mat[3][2], mat[3][3]),
      inv(inverse(m)) {}
specula::Transform::Transform(const Matrix4x4f &m) : m(m), inv(inverse(m)) {}
specula::Transform::Transform(const Matrix4x4f &m, const Matrix4x4f &inv)
    : m(m), inv(inv) {}

specula::Transform specula::Transform::translate(const Vector3f &delta) {
  return Transform(Matrix4x4f(1, 0, 0, delta.x, 0, 1, 0, delta.y, 0, 0, 1,
                              delta.z, 0, 0, 0, 1),
                   Matrix4x4f(1, 0, 0, -delta.x, 0, 1, 0, -delta.y, 0, 0, 1,
                              -delta.z, 0, 0, 0, 1));
}
specula::Transform specula::Transform::scale(Float x, Float y, Float z) {
  return Transform(
      Matrix4x4f(x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1),
      Matrix4x4f(1 / x, 0, 0, 0, 0, 1 / y, 0, 0, 0, 0, 1 / z, 0, 0, 0, 0, 1));
}
specula::Transform specula::Transform::rotate_x(Float theta) {
  Float sin_theta = std::sin(radians(theta));
  Float cos_theta = std::cos(radians(theta));
}
specula::Transform specula::Transform::rotate_y(Float theta) {}
specula::Transform specula::Transform::rotate_z(Float theta) {}
specula::Transform specula::Transform::rotate(Float theta,
                                              const Vector3f &axis) {}
specula::Transform specula::Transform::look_at(const Point3f &pos,
                                               const Point3f &look,
                                               const Vector3f &up) {}
specula::Transform specula::Transform::orthographic(Float znear, Float zfar) {}
specula::Transform specula::Transform::perspective(Float fov, Float znear,
                                                   Float zfar) {}

specula::Ray specula::Transform::operator()(const Ray &r) const {
  Vector3f o_error;
  Point3f o = (*this)(r.o, &o_error);
  Vector3f d = (*this)(r.d);
  Float length_squared = d.length_squared();
  Float t_max = r.t_max;
  if (length_squared > 0) {
    Float dt = dot(abs(d), o_error) / length_squared;
    o += d * dt;
    t_max -= dt;
  }
  return Ray(o, d, t_max, r.time, r.medium);
}
specula::RayDifferential
specula::Transform::operator()(const RayDifferential &r) const {
  Ray tr = (*this)(Ray(r));
  RayDifferential ret(tr.o, tr.d, tr.t_max, tr.time, tr.medium);
  ret.has_differentials = r.has_differentials;
  ret.rx_origin = (*this)(r.rx_origin);
  ret.ry_origin = (*this)(r.ry_origin);
  ret.rx_direction = (*this)(r.rx_direction);
  ret.ry_direction = (*this)(r.ry_direction);
  return ret;
}
specula::Bounds3f specula::Transform::operator()(const Bounds3f &b) const {
  Bounds3f ret((*this)(Point3f(b.p_min.x, b.p_min.y, b.p_min.z)));
  ret = Union(ret, (*this)(Point3f(b.p_max.x, b.p_min.y, b.p_min.z)));
  ret = Union(ret, (*this)(Point3f(b.p_min.x, b.p_max.y, b.p_min.z)));
  ret = Union(ret, (*this)(Point3f(b.p_min.x, b.p_min.y, b.p_max.z)));
  ret = Union(ret, (*this)(Point3f(b.p_min.x, b.p_max.y, b.p_max.z)));
  ret = Union(ret, (*this)(Point3f(b.p_max.x, b.p_max.y, b.p_min.z)));
  ret = Union(ret, (*this)(Point3f(b.p_max.x, b.p_min.y, b.p_max.z)));
  ret = Union(ret, (*this)(Point3f(b.p_max.x, b.p_max.y, b.p_max.z)));
  return ret;
}
specula::Transform specula::Transform::operator*(const Transform &t2) const {
  return Transform(m * t2.m, t2.inv * inv);
}
