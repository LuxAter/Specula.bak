#include "specula/transform/transform.hpp"

#include "specula/global.hpp"

#include "specula/math/common.hpp"
#include "specula/math/geometric.hpp"
#include "specula/math/matrix/matrix4x4.hpp"
#include "specula/math/normal/normal3.hpp"
#include "specula/math/point/point3.hpp"
#include "specula/math/ray.hpp"
#include "specula/math/ray_differential.hpp"
#include "specula/math/vector/vector3.hpp"

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
  Matrix4x4f m(1, 0, 0, 0, 0, cos_theta, -sin_theta, 0, 0, sin_theta, cos_theta,
               0, 0, 0, 0, 1);
  return Transform(m, transpose(m));
}
specula::Transform specula::Transform::rotate_y(Float theta) {
  Float sin_theta = std::sin(radians(theta));
  Float cos_theta = std::cos(radians(theta));
  Matrix4x4f m(cos_theta, 0, sin_theta, 0, 0, 1, 0, 0, -sin_theta, 0, cos_theta,
               0, 0, 0, 0, 1);
  return Transform(m, transpose(m));
}
specula::Transform specula::Transform::rotate_z(Float theta) {
  Float sin_theta = std::sin(radians(theta));
  Float cos_theta = std::cos(radians(theta));
  Matrix4x4f m(cos_theta, -sin_theta, 0, 0, sin_theta, cos_theta, 0, 0, 0, 0, 1,
               0, 0, 0, 0, 1);
  return Transform(m, transpose(m));
}
specula::Transform specula::Transform::rotate(Float theta,
                                              const Vector3f &axis) {
  Vector3f a = normalize(axis);
  Float sin_theta = std::sin(radians(theta));
  Float cos_theta = std::cos(radians(theta));
  Matrix4x4f m;
  m.data[0][0] = a.x * a.x + (1 - a.x * a.x) * cos_theta;
  m.data[0][1] = a.x * a.y * (1 - cos_theta) - a.z * sin_theta;
  m.data[0][2] = a.x * a.z * (1 - cos_theta) + a.y * sin_theta;
  m.data[0][3] = 0;

  m.data[1][0] = a.x * a.y * (1 - cos_theta) + a.z * sin_theta;
  m.data[1][1] = a.y * a.y + (1 - a.y * a.y) * cos_theta;
  m.data[1][2] = a.y * a.z * (1 - cos_theta) - a.x * sin_theta;
  m.data[1][3] = 0;

  m.data[2][0] = a.x * a.z * (1 - cos_theta) - a.y * sin_theta;
  m.data[2][1] = a.y * a.z * (1 - cos_theta) + a.x * sin_theta;
  m.data[2][2] = a.z * a.z + (1 - a.z * a.z) * cos_theta;
  m.data[2][3] = 0;
  return Transform(m, transpose(m));
}
specula::Transform specula::Transform::look_at(const Point3f &pos,
                                               const Point3f &look,
                                               const Vector3f &up) {
  Matrix4x4f camera_to_world;
  camera_to_world.data[0][3] = pos.x;
  camera_to_world.data[1][3] = pos.y;
  camera_to_world.data[2][3] = pos.z;
  camera_to_world.data[3][3] = 1;

  Vector3f dir = normalize(look - pos);
  if (cross(normalize(up), dir).length() == 0) {
    LERROR(
        "\"up\" vector ({}) and viewing direction ({}) passed to look_at are "
        "pointing in the same direction. Using the identity transformation.",
        up, dir);
    return Transform();
  }
  Vector3f right = normalize(cross(normalize(up), dir));
  Vector3f new_up = cross(dir, right);
  camera_to_world.data[0][0] = right.x;
  camera_to_world.data[1][0] = right.y;
  camera_to_world.data[2][0] = right.z;
  camera_to_world.data[3][0] = 0.0f;
  camera_to_world.data[0][1] = new_up.x;
  camera_to_world.data[1][1] = new_up.y;
  camera_to_world.data[2][1] = new_up.z;
  camera_to_world.data[3][1] = 0.0f;
  camera_to_world.data[0][2] = dir.x;
  camera_to_world.data[1][2] = dir.y;
  camera_to_world.data[2][2] = dir.z;
  camera_to_world.data[3][2] = 0.0f;
  return Transform(inverse(camera_to_world), camera_to_world);
}
specula::Transform specula::Transform::orthographic(Float znear, Float zfar) {
  return Transform::scale(1, 1, 1 / (zfar - znear)) *
         Transform::translate(Vector3f(0, 0, -znear));
}
specula::Transform specula::Transform::perspective(Float fov, Float znear,
                                                   Float zfar) {
  Matrix4x4f persp(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, zfar / (zfar - znear),
                   -zfar * znear / (zfar - znear), 0, 0, 1, 0);
  Float inv_tan_ang = 1 / std::tan(radians(fov) / 2);
  return Transform::scale(inv_tan_ang, inv_tan_ang, 1) * Transform(persp);
}

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

bool specula::Transform::swaps_handedness() const { return determinant(m) < 0; }
