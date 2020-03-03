#ifndef SPECULA_CORE_TRANSFORM_HPP_
#define SPECULA_CORE_TRANSFORM_HPP_

#include "../global.hpp"
#include "geometry.hpp"

namespace specula {
class Transform {
public:
  Transform(const Float mat[4][4]) : m(mat), m_inv(inverse(m)) {}
  Transform(const Matrix4x4<Float> &m) : m(m), m_inv(inverse(m)) {}
  Transform(const Matrix4x4<Float> &m, const Matrix4x4<Float> &m_inv)
      : m(m), m_inv(m_inv) {}

  template <typename T> inline Point3<T> operator()(const Point3<T> &p) const {
    T x = p.x, y = p.y, z = p.z;
    T xp =
        m.data[0][0] * x + m.data[0][1] * y + m.data[0][2] * z + m.data[0][3];
    T yp =
        m.data[1][0] * x + m.data[1][1] * y + m.data[1][2] * z + m.data[1][3];
    T zp =
        m.data[2][0] * x + m.data[2][1] * y + m.data[2][2] * z + m.data[2][3];
    T wp =
        m.data[3][0] * x + m.data[3][1] * y + m.data[3][2] * z + m.data[3][3];
    CHECK_NE(wp, 0);
    if (wp == 1)
      return Point3<T>(xp, yp, zp);
    else
      return Point3<T>(xp, yp, zp) / wp;
  }
  template <typename T>
  inline Point3<T> operator()(const Point3<T> &p, Vector3<T> *p_error) const {
    T x = p.x, y = p.y, z = p.z;
    T xp =
        m.data[0][0] * x + m.data[0][1] * y + m.data[0][2] * z + m.data[0][3];
    T yp =
        m.data[1][0] * x + m.data[1][1] * y + m.data[1][2] * z + m.data[1][3];
    T zp =
        m.data[2][0] * x + m.data[2][1] * y + m.data[2][2] * z + m.data[2][3];
    T wp =
        m.data[3][0] * x + m.data[3][1] * y + m.data[3][2] * z + m.data[3][3];

    T x_abs_sum = std::abs(m.data[0][0] * x) + std::abs(m.data[0][1] * y) +
                  std::abs(m.data[0][2] * z) + std::abs(m.data[0][3]);
    T y_abs_sum = std::abs(m.data[1][0] * x) + std::abs(m.data[1][1] * y) +
                  std::abs(m.data[1][2] * z) + std::abs(m.data[1][3]);
    T z_abs_sum = std::abs(m.data[2][0] * x) + std::abs(m.data[2][1] * y) +
                  std::abs(m.data[2][2] * z) + std::abs(m.data[2][3]);
    *p_error = gamma(3) * Vector3<T>(x_abs_sum, y_abs_sum, z_abs_sum);

    CHECK_NE(wp, 0);
    if (wp == 1)
      return Point3<T>(xp, yp, zp);
    else
      return Point3<T>(xp, yp, zp) / wp;
  }
  template <typename T>
  inline Vector3<T> operator()(const Vector3<T> &v) const {
    T x = v.x, y = v.y, z = v.z;
    return Vector3<T>(m.data[0][0] * x + m.data[0][1] * y + m.data[0][2] * z,
                      m.data[1][0] * x + m.data[1][1] * y + m.data[1][2] * z,
                      m.data[2][0] * x + m.data[2][1] * y + m.data[2][2] * z);
  }
  template <typename T>
  inline Normal3<T> operator()(const Normal3<T> &n) const {

    T x = n.x, y = n.y, z = n.z;
    return Normal3<T>(
        m_inv.data[0][0] * x + m_inv.data[0][1] * y + m_inv.data[0][2] * z,
        m_inv.data[1][0] * x + m_inv.data[1][1] * y + m_inv.data[1][2] * z,
        m_inv.data[2][0] * x + m_inv.data[2][1] * y + m_inv.data[2][2] * z);
  }
  inline Ray operator()(const Ray &r) const {
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
  inline Bounds3f operator()(const Bounds3f &b) const {
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

  inline Transform operator*(const Transform &t2) const {
    return Transform(m * t2.m, m_inv * t2.m_inv);
  }

  bool has_scale() const {
    Float la2 = (*this)(Vector3f(1, 0, 0)).length_squared();
    Float lb2 = (*this)(Vector3f(0, 1, 0)).length_squared();
    Float lc2 = (*this)(Vector3f(0, 0, 1)).length_squared();
    return (la2 < 0.999f || la2 > 1.001f || lb2 < 0.999f || lb2 > 1.001f ||
            lc2 < 0.999f || lc2 > 1.001f);
  }

  bool swaps_handedness() const {
    Float det =
        m.data[0][0] *
            (m.data[1][1] * m.data[2][2] - m.data[1][2] * m.data[2][1]) -
        m.data[0][1] *
            (m.data[1][0] * m.data[2][2] - m.data[1][2] * m.data[2][0]) +
        m.data[0][2] *
            (m.data[1][0] * m.data[2][1] - m.data[1][1] * m.data[2][0]);
    return det < 0;
  }

  friend Transform inverse(const Transform &t) {
    return Transform(t.m_inv, t.m);
  }
  friend Transform transpose(const Transform &t) {
    return Transform(transpose(t.m), transpose(t.m_inv));
  }

private:
  Matrix4x4<Float> m, m_inv;
};

Transform translate(const Vector3f &delta) {
  Matrix4x4<Float> m(1, 0, 0, delta.x, 0, 1, 0, delta.y, 0, 0, 1, delta.z, 0, 0,
                     0, 1);
  Matrix4x4<Float> m_inv(1, 0, 0, -delta.x, 0, 1, 0, -delta.y, 0, 0, 1,
                         -delta.z, 0, 0, 0, 1);
  return Transform(m, m_inv);
}
Transform scale(Float x, Float y, Float z) {
  Matrix4x4<Float> m(x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1);
  Matrix4x4<Float> m_inv(1 / x, 0, 0, 0, 0, 1 / y, 0, 0, 0, 0, 1 / z, 0, 0, 0,
                         0, 1);
  return Transform(m, m_inv);
}
Transform rotate_x(Float theta) {
  Float sin_theta = std::sin(radians(theta));
  Float cos_theta = std::cos(radians(theta));
  Matrix4x4<Float> m(1, 0, 0, 0, 0, cos_theta, -sin_theta, 0, 0, sin_theta,
                     cos_theta, 0, 0, 0, 0, 1);
  return Transform(m, transpose(m));
}
Transform rotate_y(Float theta) {
  Float sin_theta = std::sin(radians(theta));
  Float cos_theta = std::cos(radians(theta));
  Matrix4x4<Float> m(cos_theta, 0, sin_theta, 0, 0, 1, 0, 0, -sin_theta, 0,
                     cos_theta, 0, 0, 0, 0, 1);
  return Transform(m, transpose(m));
}
Transform rotate_z(Float theta) {
  Float sin_theta = std::sin(radians(theta));
  Float cos_theta = std::cos(radians(theta));
  Matrix4x4<Float> m(cos_theta, -sin_theta, 0, 0, 0, 1, 0, 0, sin_theta,
                     cos_theta, 0, 0, 0, 0, 0, 1);
  return Transform(m, transpose(m));
}
Transform rotate(Float theta, const Vector3f &axis) {
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

Transform look_at(const Point3f &pos, const Point3f &look, const Vector3f &up) {
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

} // namespace specula

#endif // SPECULA_CORE_TRANSFORM_HPP_
