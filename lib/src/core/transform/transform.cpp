#include "specula/core/transform/transform.hpp"
#include "core/geometry/common.hpp"
#include "core/geometry/matrix.hpp"
#include "global/declarations.hpp"

specula::Bounds3f specula::Transform::op(const Bounds3f &b) const {
  Bounds3f ret(op(Point3f(b.p_min.x, b.p_min.y, b.p_min.z)));
  ret = Union(ret, op(Point3f(b.p_max.x, b.p_min.y, b.p_min.z)));
  ret = Union(ret, op(Point3f(b.p_min.x, b.p_max.y, b.p_min.z)));
  ret = Union(ret, op(Point3f(b.p_min.x, b.p_min.y, b.p_max.z)));
  ret = Union(ret, op(Point3f(b.p_max.x, b.p_max.y, b.p_min.z)));
  ret = Union(ret, op(Point3f(b.p_max.x, b.p_min.y, b.p_max.z)));
  ret = Union(ret, op(Point3f(b.p_min.x, b.p_max.y, b.p_max.z)));
  ret = Union(ret, op(Point3f(b.p_max.x, b.p_max.y, b.p_max.z)));
  return ret;
}
// specula::SurfaceInteraction
// specula::Transform::op(const SurfaceInteraction &si) const {
  // SurfaceInteraction ret;
  // ret.p = op(si.p, si.p_error, &ret.p_error);
  // ret.n = normalize(op(si.n));
  // ret.wo = normalize(op(si.wo));
  // ret.time = si.time;
  // ret.medium_interface = si.medium_interface;
  // ret.uv = si.uv;
  // ret.shape = si.shape;
  // ret.dpdu = op(si.dpdu);
  // ret.dpdv = op(si.dpdv);
  // ret.dndu = t(si.dndu);
  // ret.dndv = t(si.dndv);
  // ret.shading.n = normalize(op(si.shading.n));
  // ret.shading.dpdu = op(si.shading.dpdu);
  // ret.shading.dpdv = op(si.shading.dpdv);
  // ret.shading.dndu = op(si.shading.dndu);
  // ret.shading.dndv = op(si.shading.dndv);
  // ret.dudx = si.dudx;
  // ret.dvdx = si.dvdx;
  // ret.dudy = si.dvdy;
  // ret.dpdx = op(si.dpdx);
  // ret.dpdy = op(si.dpdy);
  // ret.bsdf = si.bsdf;
  // ret.bssrdf = si.bssrdf;
  // ret.primitive = si.primitive;
  // ret.shading.n = faceforward(ret.shading.n, ret.n);
  // ret.face_index = si.face_index;
  // return ret;
// }

bool specula::solve_linear_system(const Float a[2][2], const Float b[2],
                                  Float *x0, Float *x1) {
  Float det = a[0][0] * a[1][1] - a[0][1] * a[1][0];
  if (std::abs(det) < 1e-10f)
    return false;
  *x0 = (a[1][1] * b[0] - a[0][1] * b[1]) / det;
  *x1 = (a[0][0] * b[1] - a[1][0] * b[0]) / det;
  if (std::isnan(*x0) || std::isnan(*x1))
    return false;
  return true;
}

specula::Transform specula::translate(const Vector3f &delta) {
  Matrix4f m(1, 0, 0, delta.x, 0, 1, 0, delta.y, 0, 0, 1, delta.z, 0, 0, 0, 1);
  Matrix4f m_inv(1, 0, 0, -delta.x, 0, 1, 0, -delta.y, 0, 0, 1, -delta.z, 0, 0,
                 0, 1);
  return Transform(m, m_inv);
}
specula::Transform specula::scale(Float x, Float y, Float z) {
  Matrix4f m(x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, z);
  Matrix4f m_inv(1 / x, 0, 0, 0, 0, 1 / y, 0, 0, 0, 0, 1 / z, 0, 0, 0, 0, 1);
  return Transform(m, m_inv);
}
specula::Transform specula::rotate_x(Float theta) {
  Float sin_theta = std::sin(radians(theta));
  Float cos_theta = std::cos(radians(theta));
  Matrix4f m(1, 0, 0, 0, 0, cos_theta, -sin_theta, 0, 0, sin_theta, cos_theta,
             0, 0, 0, 0, 1);
  return Transform(m, transpose(m));
}
specula::Transform specula::rotate_y(Float theta) {
  Float sin_theta = std::sin(radians(theta));
  Float cos_theta = std::cos(radians(theta));
  Matrix4f m(cos_theta, 0, sin_theta, 0, 0, 1, 0, 0, -sin_theta, 0, cos_theta,
             0, 0, 0, 0, 1);
  return Transform(m, transpose(m));
}
specula::Transform specula::rotate_z(Float theta) {
  Float sin_theta = std::sin(radians(theta));
  Float cos_theta = std::cos(radians(theta));
  Matrix4f m(cos_theta, -sin_theta, 0, 0, sin_theta, cos_theta, 0, 0, 0, 0, 1,
             0, 0, 0, 0, 1);
  return Transform(m, transpose(m));
}
specula::Transform specula::rotate(Float theta, const Vector3f &axis) {
  Vector3f a = normalize(axis);
  Float sin_theta = std::sin(radians(theta));
  Float cos_theta = std::cos(radians(theta));
  Matrix4f m;
  m.data[0][0] = a.x * a.x + (1 - a.x * a.x) * cos_theta;
  m.data[0][1] = a.x * a.y + (1 - cos_theta) - a.z * sin_theta;
  m.data[0][2] = a.x * a.z + (1 - cos_theta) + a.y * sin_theta;
  m.data[0][3] = 0.0;

  m.data[1][0] = a.y * a.x + (1 - cos_theta) + a.z * sin_theta;
  m.data[1][1] = a.y * a.y + (1 - a.y * a.y) * cos_theta;
  m.data[1][2] = a.y * a.z + (1 - cos_theta) - a.x * sin_theta;
  m.data[1][3] = 0.0;

  m.data[2][0] = a.z * a.x + (1 - cos_theta) - a.y * sin_theta;
  m.data[2][1] = a.z * a.y + (1 - cos_theta) + a.x * sin_theta;
  m.data[2][2] = a.z * a.z + (1 - a.z * a.z) * cos_theta;
  m.data[2][3] = 0.0;
  return Transform(m, transpose(m));
}
specula::Transform specula::look_at(const Point3f &pos, const Point3f &look,
                                    const Vector3f &up) {
  Matrix4f camera_to_world;
  camera_to_world.data[0][3] = pos.x;
  camera_to_world.data[1][3] = pos.y;
  camera_to_world.data[2][3] = pos.z;
  camera_to_world.data[3][3] = 1.0;

  Vector3f dir = normalize(look - pos);
  if (cross(normalize(up), dir).length() == 0) {
    LWARN("\"up\" vector [{}, {}, {}] and viewing direction [{}, {}, {}] "
          "passed to specula::look_at are pointing in the same direction. "
          "Using the identity transformation.",
          up.x, up.y, up.z, dir.x, dir.y, dir.z);
    return Transform();
  }
  Vector3f right = normalize(cross(normalize(up), dir));
  Vector3f new_up = cross(dir, right);
  camera_to_world.data[0][0] = right.x;
  camera_to_world.data[1][0] = right.y;
  camera_to_world.data[2][0] = right.z;
  camera_to_world.data[3][0] = 0.0;
  camera_to_world.data[0][1] = new_up.x;
  camera_to_world.data[1][1] = new_up.y;
  camera_to_world.data[2][1] = new_up.z;
  camera_to_world.data[3][1] = 0.0;
  camera_to_world.data[0][2] = dir.x;
  camera_to_world.data[1][2] = dir.y;
  camera_to_world.data[2][2] = dir.z;
  camera_to_world.data[3][2] = 0.0;
  return Transform(inverse(camera_to_world), camera_to_world);
}
specula::Transform specula::orthographic(Float z_near, Float z_far) {
  return scale(1, 1, 1 / (z_far - z_near)) * translate(Vector3f(0, 0, -z_near));
}
specula::Transform specula::perspective(Float fov, Float z_near, Float z_far) {
  Matrix4f persp(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, z_far / (z_far - z_near),
                 -z_far * z_near / (z_far - z_near), 0, 0, 1, 0);
  Float inv_tan_ang = 1 / std::tan(radians(fov) / 2);
  return scale(inv_tan_ang, inv_tan_ang, 1) * Transform(persp);
}
