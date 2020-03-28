#ifndef SPECULA_CORE_TRANSFORM_TRANSFORM_HPP_
#define SPECULA_CORE_TRANSFORM_TRANSFORM_HPP_

#include "core/geometry/matrix.hpp"
#include "core/geometry/ray.hpp"
#include "global/declarations.hpp"
#include "specula/core/geometry.hpp"
#include "specula/global.hpp"

namespace specula {
class Transform {
public:
  Transform() {}
  Transform(const Float mat[4][4]) {
    m = Matrix4f(mat[0][0], mat[0][1], mat[0][2], mat[0][3], mat[1][0],
                 mat[1][1], mat[1][2], mat[1][3], mat[2][0], mat[2][1],
                 mat[2][2], mat[2][3], mat[3][0], mat[3][1], mat[3][2],
                 mat[3][3]);
    m_inv = inverse(m);
  }
  Transform(const Matrix4f &m) : m(m), m_inv(inverse(m)) {}
  Transform(const Matrix4f &m, const Matrix4f &m_inv) : m(m), m_inv(m_inv) {}

  bool operator==(const Transform &t) const {
    return t.m == m && t.m_inv == m_inv;
  }
  bool operator!=(const Transform &t) const {
    return t.m != m || t.m_inv != m_inv;
  }
  bool operator<(const Transform &t) const {
    for (typename Matrix4f::size_type i = 0; i < 4; ++i) {
      for (typename Matrix4f::size_type j = 0; j < 4; ++j) {
        if (m.data[i][j] < t.m.data[i][j])
          return true;
        else if (m.data[i][j] > t.m.data[i][j])
          return false;
      }
    }
    return false;
  }
  bool is_identity() const {
    return (
        m.data[0][0] == 1.0f && m.data[0][1] == 0.0f && m.data[0][2] == 0.0f &&
        m.data[0][3] == 0.0f && m.data[1][0] == 0.0f && m.data[1][1] == 1.0f &&
        m.data[1][2] == 0.0f && m.data[1][3] == 0.0f && m.data[2][0] == 0.0f &&
        m.data[2][1] == 0.0f && m.data[2][2] == 1.0f && m.data[2][3] == 0.0f &&
        m.data[3][0] == 0.0f && m.data[3][1] == 0.0f && m.data[3][2] == 0.0f &&
        m.data[3][3] == 1.0f);
  }
  const Matrix4f &get_matrix() const { return m; }
  const Matrix4f &get_inverse_matrix() const { return m_inv; }
  bool has_scale() const {
    Float la2 = op(Vector3f(1, 0, 0)).length_squared();
    Float lb2 = op(Vector3f(0, 1, 0)).length_squared();
    Float lc2 = op(Vector3f(0, 0, 1)).length_squared();
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

  template <typename T> inline Point3<T> op(const Point3<T> &p) const {
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
  inline Point3<T> op(const Point3<T> &p, Vector3<T> *p_error) const {
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
  inline Point3<T> op(const Point3<T> &p, const Vector3<T> &p_error,
                      Vector3<T> *abs_error) const {
    T x = p.x, y = p.y, z = p.z;
    T xp =
        m.data[0][0] * x + m.data[0][1] * y + m.data[0][2] * z + m.data[0][3];
    T yp =
        m.data[1][0] * x + m.data[1][1] * y + m.data[1][2] * z + m.data[1][3];
    T zp =
        m.data[2][0] * x + m.data[2][1] * y + m.data[2][2] * z + m.data[2][3];
    T wp =
        m.data[3][0] * x + m.data[3][1] * y + m.data[3][2] * z + m.data[3][3];
    abs_error->x =
        (gamma(3) + T(1)) * (std::abs(m.data[0][0]) * p_error.x +
                             std::abs(m.data[0][1]) * p_error.y +
                             std::abs(m.data[0][2]) * p_error.z) +
        gamma(3) * (std::abs(m.data[0][0] * x) + std::abs(m.data[0][1] * y) +
                    std::abs(m.data[0][2] * z) + std::abs(m.data[0][3]));
    abs_error->y =
        (gamma(3) + T(1)) * (std::abs(m.data[1][0]) * p_error.x +
                             std::abs(m.data[1][1]) * p_error.y +
                             std::abs(m.data[1][2]) * p_error.z) +
        gamma(3) * (std::abs(m.data[1][0] * x) + std::abs(m.data[1][1] * y) +
                    std::abs(m.data[1][2] * z) + std::abs(m.data[1][3]));
    abs_error->y =
        (gamma(3) + T(1)) * (std::abs(m.data[2][0]) * p_error.x +
                             std::abs(m.data[2][1]) * p_error.y +
                             std::abs(m.data[2][2]) * p_error.z) +
        gamma(3) * (std::abs(m.data[2][0] * x) + std::abs(m.data[2][1] * y) +
                    std::abs(m.data[2][2] * z) + std::abs(m.data[2][3]));
    CHECK_NE(wp, 0);
    if (wp == 1)
      return Point3<T>(xp, yp, zp);
    else
      return Point3<T>(xp, yp, zp) / wp;
  }
  template <typename T> inline Vector3<T> op(const Vector3<T> &v) const {
    T x = v.x, y = v.y, z = v.z;
    return Vector3<T>(m.data[0][0] * x + m.data[0][1] * y + m.data[0][2] * z,
                      m.data[1][0] * x + m.data[1][1] * y + m.data[1][2] * z,
                      m.data[2][0] * x + m.data[2][1] * y + m.data[2][2] * z);
  }
  template <typename T>
  inline Vector3<T> op(const Vector3<T> &v, Vector3<T> *v_error) const {
    T x = v.x, y = v.y, z = v.z;
    v_error->x = gamma(3) *
                 (std::abs(m.data[0][0] * v.x) + std::abs(m.data[0][1] * v.y) +
                  std::abs(m.data[0][2] * v.z));
    v_error->y = gamma(3) *
                 (std::abs(m.data[1][0] * v.x) + std::abs(m.data[1][1] * v.y) +
                  std::abs(m.data[1][2] * v.z));
    v_error->z = gamma(3) *
                 (std::abs(m.data[2][0] * v.x) + std::abs(m.data[2][1] * v.y) +
                  std::abs(m.data[2][2] * v.z));
    return Vector3<T>(m.data[0][0] * x + m.data[0][1] * y + m.data[0][2] * z,
                      m.data[1][0] * x + m.data[1][1] * y + m.data[1][2] * z,
                      m.data[2][0] * x + m.data[2][1] * y + m.data[2][2] * z);
  }
  template <typename T>
  inline Vector3<T> op(const Vector3<T> &v, const Vector3<T> &v_error,
                       Vector3<T> *abs_error) const {
    T x = v.x, y = v.y, z = v.z;
    abs_error->x =
        (gamma(3) + T(1)) * (std::abs(m.data[0][0]) * v_error.x +
                             std::abs(m.data[0][1]) * v_error.y +
                             std::abs(m.data[0][2]) * v_error.z) +
        gamma(3) * (std::abs(m.data[0][0] * x) + std::abs(m.data[0][1] * y) +
                    std::abs(m.data[0][2] * z));
    abs_error->y =
        (gamma(3) + T(1)) * (std::abs(m.data[1][0]) * v_error.x +
                             std::abs(m.data[1][1]) * v_error.y +
                             std::abs(m.data[1][2]) * v_error.z) +
        gamma(3) * (std::abs(m.data[1][0] * x) + std::abs(m.data[1][1] * y) +
                    std::abs(m.data[1][2] * z));
    abs_error->y =
        (gamma(3) + T(1)) * (std::abs(m.data[2][0]) * v_error.x +
                             std::abs(m.data[2][1]) * v_error.y +
                             std::abs(m.data[2][2]) * v_error.z) +
        gamma(3) * (std::abs(m.data[2][0] * x) + std::abs(m.data[2][1] * y) +
                    std::abs(m.data[2][2] * z));
    return Vector3<T>(m.data[0][0] * x + m.data[0][1] * y + m.data[0][2] * z,
                      m.data[1][0] * x + m.data[1][1] * y + m.data[1][2] * z,
                      m.data[2][0] * x + m.data[2][1] * y + m.data[2][2] * z);
  }
  template <typename T> inline Normal3<T> op(const Normal3<T> &n) const {
    T x = n.x, y = n.y, z = n.z;
    return Normal3<T>(
        m_inv.data[0][0] * x + m_inv.data[0][1] * y + m_inv.data[0][2] * z,
        m_inv.data[1][0] * x + m_inv.data[1][1] * y + m_inv.data[1][2] * z,
        m_inv.data[2][0] * x + m_inv.data[2][1] * y + m_inv.data[2][2] * z);
  }

  inline Ray op(const Ray &r) const {
    Vector3f o_error;
    Point3f o = op(r.o, &o_error);
    Vector3f d = op(r.d);
    Float length_squared = d.length_squared();
    Float t_max = r.t_max;
    if (length_squared > 0) {
      Float dt = dot(abs(d), o_error) / length_squared;
      o += d * dt;
      t_max -= dt;
    }
    return Ray(o, d, t_max, r.time, r.medium);
  }
  inline Ray op(const Ray &r, Vector3f *o_error, Vector3f *d_error) const {
    Point3f o = op(r.o, o_error);
    Vector3f d = op(r.d, d_error);
    Float length_squared = d.length_squared();
    Float t_max = r.t_max;
    if (length_squared > 0) {
      Float dt = dot(abs(d), *o_error) / length_squared;
      o += d * dt;
    }
    return Ray(o, d, t_max, r.time, r.medium);
  }
  inline Ray op(const Ray &r, const Vector3f &o_error_in,
                const Vector3f &d_error_in, Vector3f *o_error_out,
                Vector3f *d_error_out) const {
    Point3f o = op(r.o, o_error_in, d_error_out);
    Vector3f d = op(r.d, d_error_in, d_error_out);
    Float length_squared = d.length_squared();
    Float t_max = r.t_max;
    if (length_squared > 0) {
      Float dt = dot(abs(d), *o_error_out) / length_squared;
      o += d * dt;
    }
    return Ray(o, d, t_max, r.time, r.medium);
  }
  inline RayDifferential op(const RayDifferential &r) const {
    Ray tr = op(Ray(r));
    RayDifferential ret(tr.o, tr.d, tr.t_max, tr.time, tr.medium);
    ret.has_differentials = r.has_differentials;
    ret.rx_origin = op(r.rx_origin);
    ret.ry_origin = op(r.ry_origin);
    ret.rx_direction = op(r.ry_direction);
    ret.ry_direction = op(r.ry_direction);
    return ret;
  }

  Bounds3f op(const Bounds3f &b) const;
  // TODO
  // SurfaceInteraction op(const SurfaceInteraction &si) const;

  template <typename T, typename... Args>
  inline auto operator()(const T &&v, const Args &&... args) const
      -> decltype(op(std::forward(v), std::forward(args)...)) {
    return op(std::forward(v), std::forward(args)...);
  }

  inline Transform operator*(const Transform &t) const {
    return Transform(m * t.m, t.m_inv * m_inv);
  }

  inline std::string fmt() const {
    return fmt::format("(t: {} inv: {})", m, m_inv);
  }

  friend Transform inverse(const Transform &t) {
    return Transform(t.m_inv, t.m);
  }
  friend Transform transpose(const Transform &t) {
    return Transform(transpose(t.m), transpose(t.m_inv));
  }

private:
  Matrix4f m, m_inv;
  friend class AnimatedTransform;
  friend struct Quaternion;
};

bool solve_linear_system(const Float a[2][2], const Float b[2], Float *x0,
                         Float *x1);

Transform translate(const Vector3f &delta);
Transform scale(Float x, Float y, Float z);
Transform rotate_x(Float theta);
Transform rotate_y(Float theta);
Transform rotate_z(Float theta);
Transform rotate(Float theta, const Vector3f &axis);
Transform look_at(const Point3f &pos, const Point3f &look, const Vector3f &up);
Transform orthographic(Float z_near, Float z_far);
Transform perspective(Float fov, Float z_near, Float z_far);

inline std::ostream &operator<<(std::ostream &out, const Transform &t) {
  return out << t.fmt();
}
} // namespace specula

#endif /* end of include guard: SPECULA_CORE_TRANSFORM_TRANSFORM_HPP_ */
