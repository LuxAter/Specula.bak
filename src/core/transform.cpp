#include "specula/core/transform.hpp"

specula::Transform::Transform(const Float mat[4][4])
    : m(mat), m_inv(inverse(m)) {}
specula::Transform::Transform(const Matrix4x4<Float> &m)
    : m(m), m_inv(inverse(m)) {}
specula::Transform::Transform(const Matrix4x4<Float> &m,
                              const Matrix4x4<Float> &m_inv)
    : m(m), m_inv(m_inv) {}

specula::Ray specula::Transform::operator()(const Ray &r) const {
  Vector3f o_error;
  Point3f o = (*this)(r.o, &o_error);
  Vector3f d = (*this)(r.d);
  Float length_squared = d.length_squared();
  float t_max = r.t_max;
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
  const Transform &M = *this;
  Bounds3f ret(M(Point3f(b.p_min.x, b.p_min.y, b.p_min.z)));
  ret = Union(ret, M(Point3f(b.p_max.x, b.p_min.y, b.p_min.z)));
  ret = Union(ret, M(Point3f(b.p_min.x, b.p_max.y, b.p_min.z)));
  ret = Union(ret, M(Point3f(b.p_min.x, b.p_min.y, b.p_max.z)));
  ret = Union(ret, M(Point3f(b.p_min.x, b.p_max.y, b.p_max.z)));
  ret = Union(ret, M(Point3f(b.p_max.x, b.p_max.y, b.p_min.z)));
  ret = Union(ret, M(Point3f(b.p_max.x, b.p_min.y, b.p_max.z)));
  ret = Union(ret, M(Point3f(b.p_max.x, b.p_max.y, b.p_max.z)));
  return ret;
}

specula::SurfaceInteraction
specula::Transform::operator()(const SurfaceInteraction &si) const {
  SurfaceInteraction ret;

  ret.p = (*this)(si.p, si.p_error, &ret.p_error);

  const Transform &t = *this;
  ret.n = normalize(t(si.n));
  ret.wo = normalize(t(si.wo));
  ret.time = si.time;
  ret.medium_interface = si.medium_interface;
  ret.uv = si.uv;
  ret.shape = si.shape;
  ret.dpdu = t(si.dpdu);
  ret.dpdv = t(si.dpdv);
  ret.dndu = t(si.dndu);
  ret.dndv = t(si.dndv);
  ret.shading.n = normalize(t(si.shading.n));
  ret.shading.dpdu = t(si.shading.dpdu);
  ret.shading.dpdv = t(si.shading.dpdv);
  ret.shading.dndu = t(si.shading.dndu);
  ret.shading.dndv = t(si.shading.dndv);
  ret.dudx = si.dudx;
  ret.dvdx = si.dvdx;
  ret.dudy = si.dusy;
  ret.dvdy = si.dvdy;
  ret.dpdx = t(si.dpdx);
  ret.dpdy = t(si.dpdy);
  ret.bsdf = si.bsdf;
  ret.bssrdf = si.bssrdf;
  ret.primitive = si.primitive;
  ret.shading.n = faceforward(ret.shading.n, ret.n);
  ret.face_index = si.face_index;
  return ret;
}
specula::Ray specula::Transform::operator()(const Ray &r, Vector3f *o_error,
                                            Vector3f *d_error) const {
  Point3f o = (*this)(r.o, o_error);
  Vector3f d = (*this)(r.d, d_error);
  Float t_max = r.t_max;
  Float length_squared = d.length_squared();
  if (length_squared > 0) {
    Float dt = dot(abs(d), *o_error) / length_squared;
    o += d * dt;
  }
  return Ray(o, d, t_max, r.time, r.medium);
}
specula::Ray specula::Transform::operator()(const Ray &r,
                                            const Vector3f &o_error_in,
                                            const Vector3f &d_error_in,
                                            Vector3f *o_error_out,
                                            Vector3f *d_error_out) const {
  Point3f o = (*this)(r.o, o_error_in, o_error_out);
  Vector3f d = (*this)(r.d, d_error_in, d_error_out);
  Float t_max = r.t_max;
  Float length_squared = d.length_squared();
  if (length_squared > 0) {
    Float dt = dot(abs(d), *o_error_out) / length_squared;
    o += d * dt;
  }
  return Ray(o, d, t_max, r.time, r.medium);
}

specula::Transform specula::Transform::operator*(const Transform &t2) const {
  return Transform(m * t2.m, m_inv * t2.m_inv);
}

bool specula::Transform::operator==(const Transform &t) const {
  return t.m == m && t.m_inv == m_inv;
}
bool specula::Transform::operator!=(const Transform &t) const {
  return t.m != m || t.m_inv != m_inv;
}
bool specula::Transform::operator<(const Transform &t2) const {
  for (typename Matrix4x4<Float>::size_type i = 0; i < 4; ++i) {
    for (typename Matrix4x4<Float>::size_type j = 0; j < 4; ++j) {
      if (m.data[i][j] < t2.m.data[i][j])
        return true;
      if (m.data[i][j] > t2.m.data[i][j])
        return false;
    }
  }
  return false;
}

bool specula::Transform::is_identity() const {
  return m.data[0][0] == 1.0f && m.data[0][1] == 0.0f && m.data[0][2] == 0.0f &&
         m.data[0][3] == 0.0f && m.data[1][0] == 0.0f && m.data[1][1] == 1.0f &&
         m.data[1][2] == 0.0f && m.data[1][3] == 0.0f && m.data[2][0] == 0.0f &&
         m.data[2][1] == 0.0f && m.data[2][2] == 1.0f && m.data[2][3] == 0.0f &&
         m.data[3][0] == 0.0f && m.data[3][1] == 0.0f && m.data[3][2] == 0.0f &&
         m.data[3][3] == 1.0f;
}
bool specula::Transform::has_scale() const {
  Float la2 = (*this)(Vector3f(1, 0, 0)).length_squared();
  Float lb2 = (*this)(Vector3f(0, 1, 0)).length_squared();
  Float lc2 = (*this)(Vector3f(0, 0, 1)).length_squared();
  return (la2 < 0.999f || la2 > 1.001f || lb2 < 0.999f || lb2 > 1.001f ||
          lc2 < 0.999f || lc2 > 1.001f);
}
bool specula::Transform::swaps_handedness() const {
  Float det = m.data[0][0] *
                  (m.data[1][1] * m.data[2][2] - m.data[1][2] * m.data[2][1]) -
              m.data[0][1] *
                  (m.data[1][0] * m.data[2][2] - m.data[1][2] * m.data[2][0]) +
              m.data[0][2] *
                  (m.data[1][0] * m.data[2][1] - m.data[1][1] * m.data[2][0]);
  return det < 0;
}

specula::Transform specula::inverse(const Transform &t) {
  return Transform(t.m_inv, t.m);
}
specula::Transform specula::transpose(const Transform &t) {
  return Transform(transpose(t.m), transpose(t.m_inv));
}

specula::Transform specula::translate(const Vector3f &delta) {
  Matrix4x4<Float> m(1, 0, 0, delta.x, 0, 1, 0, delta.y, 0, 0, 1, delta.z, 0, 0,
                     0, 1);
  Matrix4x4<Float> m_inv(1, 0, 0, -delta.x, 0, 1, 0, -delta.y, 0, 0, 1,
                         -delta.z, 0, 0, 0, 1);
  return Transform(m, m_inv);
}
specula::Transform specula::scale(Float x, Float y, Float z) {
  Matrix4x4<Float> m(x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1);
  Matrix4x4<Float> m_inv(1 / x, 0, 0, 0, 0, 1 / y, 0, 0, 0, 0, 1 / z, 0, 0, 0,
                         0, 1);
  return Transform(m, m_inv);
}
specula::Transform specula::rotate_x(Float theta) {
  Float sin_theta = std::sin(radians(theta));
  Float cos_theta = std::cos(radians(theta));
  Matrix4x4<Float> m(1, 0, 0, 0, 0, cos_theta, -sin_theta, 0, 0, sin_theta,
                     cos_theta, 0, 0, 0, 0, 1);
  return Transform(m, transpose(m));
}
specula::Transform specula::rotate_y(Float theta) {
  Float sin_theta = std::sin(radians(theta));
  Float cos_theta = std::cos(radians(theta));
  Matrix4x4<Float> m(cos_theta, 0, sin_theta, 0, 0, 1, 0, 0, -sin_theta, 0,
                     cos_theta, 0, 0, 0, 0, 1);
  return Transform(m, transpose(m));
}
specula::Transform specula::rotate_z(Float theta) {
  Float sin_theta = std::sin(radians(theta));
  Float cos_theta = std::cos(radians(theta));
  Matrix4x4<Float> m(cos_theta, -sin_theta, 0, 0, 0, 1, 0, 0, sin_theta,
                     cos_theta, 0, 0, 0, 0, 0, 1);
  return Transform(m, transpose(m));
}
specula::Transform specula::rotate(Float theta, const Vector3f &axis) {
  Vector3f a = normalize(axis);
  Float sin_theta = std::sin(radians(theta));
  Float cos_theta = std::cos(radians(theta));
  Matrix4x4<Float> m;
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

specula::Transform specula::look_at(const Point3f &pos, const Point3f &look,
                                    const Vector3f &up) {
  Matrix4x4<Float> camera_to_world;
  camera_to_world.data[0][4] = pos.x;
  camera_to_world.data[1][4] = pos.y;
  camera_to_world.data[2][4] = pos.z;
  camera_to_world.data[3][4] = 1;

  Vector3f dir = normalize(look - pos);
  Vector3f left = normalize(cross(normalize(up), dir));
  Vector3f new_up = cross(dir, left);

  camera_to_world.data[0][0] = left.x;
  camera_to_world.data[1][0] = left.y;
  camera_to_world.data[2][0] = left.z;
  camera_to_world.data[3][0] = 0;
  camera_to_world.data[0][1] = new_up.x;
  camera_to_world.data[1][1] = new_up.y;
  camera_to_world.data[2][1] = new_up.z;
  camera_to_world.data[3][1] = 0;
  camera_to_world.data[0][2] = dir.x;
  camera_to_world.data[1][2] = dir.y;
  camera_to_world.data[2][2] = dir.z;
  camera_to_world.data[3][2] = 0;

  return Transform(inverse(camera_to_world), camera_to_world);
}

specula::Transform specula::orthographic(Float z_near, Float z_far) {
  return scale(1, 1, 1 / (z_far - z_near)) *
         translate(Vector3f(0.0, 0.0, -z_near));
}
specula::Transform specula::perspective(Float fov, Float n, Float f) {
  Matrix4x4<Float> persp(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, f / (f - n),
                         -f * n / (f - n), 0, 0, 1, 0);
  Flaot inv_tan_ang = 1 / std::tan(radians(fov) / 2);
  return scale(inv_tan_ang, inv_tan_ang, 1) * Transform(persp);
}
