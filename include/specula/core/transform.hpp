#ifndef SPECULA_CORE_TRANSFORM_HPP_
#define SPECULA_CORE_TRANSFORM_HPP_

#include "../global.hpp"
#include "geometry.hpp"
#include "interaction.hpp"

namespace specula {
class Transform {
public:
  Transform(const Float mat[4][4]);
  Transform(const Matrix4x4<Float> &m);
  Transform(const Matrix4x4<Float> &m, const Matrix4x4<Float> &m_inv);

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
  inline Point3<T> operator()(const Point3<T> &p, const Vector3<T> &p_error,
                              Vector3<T> *p_trans_error) const {
    T x = p.x, y = p.y, z = p.z;
    T xp =
        m.data[0][0] * x + m.data[0][1] * y + m.data[0][2] * z + m.data[0][3];
    T yp =
        m.data[1][0] * x + m.data[1][1] * y + m.data[1][2] * z + m.data[1][3];
    T zp =
        m.data[2][0] * x + m.data[2][1] * y + m.data[2][2] * z + m.data[2][3];
    T wp =
        m.data[3][0] * x + m.data[3][1] * y + m.data[3][2] * z + m.data[3][3];

    p_trans_error->x =
        (gamma(3) + T(1)) * (std::abs(m.data[0][0]) * p_error.x +
                             std::abs(m.data[0][1]) * p_error.y +
                             std::abs(m.data[0][2]) * p_error.z) +
        gamma(3) * (std::abs(m.data[0][0] * x) + std::abs(m.data[0][1] * y) +
                    std::abs(m.data[0][2] * z) + std::abs(m.data[0][3]));
    p_trans_error->y =
        (gamma(3) + T(1)) * (std::abs(m.data[1][0]) * p_error.x +
                             std::abs(m.data[1][1]) * p_error.y +
                             std::abs(m.data[1][2]) * p_error.z) +
        gamma(3) * (std::abs(m.data[1][0] * x) + std::abs(m.data[1][1] * y) +
                    std::abs(m.data[1][2] * z) + std::abs(m.data[1][3]));
    p_trans_error->z =
        (gamma(3) + T(1)) * (std::abs(m.data[2][0]) * p_error.x +
                             std::abs(m.data[2][1]) * p_error.y +
                             std::abs(m.data[2][2]) * p_error.z) +
        gamma(3) * (std::abs(m.data[2][0] * x) + std::abs(m.data[2][1] * y) +
                    std::abs(m.data[2][2] * z) + std::abs(m.data[2][3]));
    CHECK_NE(wp, 0);
    if (wp == 1.0f) {
      return Point3<T>(xp, yp, zp);
    } else {
      return Point3<T>(xp, yp, zp) / wp;
    }
  }
  template <typename T>
  inline Vector3<T> operator()(const Vector3<T> &v) const {
    T x = v.x, y = v.y, z = v.z;
    return Vector3<T>(m.data[0][0] * x + m.data[0][1] * y + m.data[0][2] * z,
                      m.data[1][0] * x + m.data[1][1] * y + m.data[1][2] * z,
                      m.data[2][0] * x + m.data[2][1] * y + m.data[2][2] * z);
  }
  template <typename T>
  inline Vector3<T> operator()(const Vector3<T> &v,
                               Vector3<T> *v_trans_error) const {
    T x = v.x, y = v.y, z = v.z;
    v_trans_error->x =
        gamma(3) * (std::abs(m.data[0][0] * x) + std::abs(m.data[0][1] * y) +
                    std::abs(m.data[0][2] * z));
    v_trans_error->y =
        gamma(3) * (std::abs(m.data[1][0] * x) + std::abs(m.data[1][1] * y) +
                    std::abs(m.data[1][2] * z));
    v_trans_error->z =
        gamma(3) * (std::abs(m.data[2][0] * x) + std::abs(m.data[2][1] * y) +
                    std::abs(m.data[2][2] * z));
    return Vector3<T>(m.data[0][0] * x + m.data[0][1] * y + m.data[0][2] * z,
                      m.data[1][0] * x + m.data[1][1] * y + m.data[1][2] * z,
                      m.data[2][0] * x + m.data[2][1] * y + m.data[2][2] * z);
  }
  template <typename T>
  inline Vector3<T> operator()(const Vector3<T> &v, const Vector3<T> &v_error,
                               Vector3<T> *v_trans_error) const {
    T x = v.x, y = v.y, z = v.z;
    v_trans_error->x =
        (gamma(3) + T(1)) * (std::abs(m.data[0][0]) * v_error.x +
                             std::abs(m.data[0][1]) * v_error.y +
                             std::abs(m.data[0][2]) * v_error.z) +
        gamma(3) * (std::abs(m.data[0][0] * x) + std::abs(m.data[0][1] * y) +
                    std::abs(m.data[0][2] * z) + std::abs(m.data[0][3]));
    v_trans_error->y =
        (gamma(3) + T(1)) * (std::abs(m.data[1][0]) * v_error.x +
                             std::abs(m.data[1][1]) * v_error.y +
                             std::abs(m.data[1][2]) * v_error.z) +
        gamma(3) * (std::abs(m.data[1][0] * x) + std::abs(m.data[1][1] * y) +
                    std::abs(m.data[1][2] * z) + std::abs(m.data[1][3]));
    v_trans_error->z =
        (gamma(3) + T(1)) * (std::abs(m.data[2][0]) * v_error.x +
                             std::abs(m.data[2][1]) * v_error.y +
                             std::abs(m.data[2][2]) * v_error.z) +
        gamma(3) * (std::abs(m.data[2][0] * x) + std::abs(m.data[2][1] * y) +
                    std::abs(m.data[2][2] * z) + std::abs(m.data[2][3]));
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
  Ray operator()(const Ray &r) const;
  RayDifferential operator()(const RayDifferential &r) const;
  Bounds3f operator()(const Bounds3f &b) const;
  SurfaceInteraction operator()(const SurfaceInteraction &si) const;
  Ray operator()(const Ray &r, Vector3f *o_error, Vector3f *d_error) const;
  Ray operator()(const Ray &r, const Vector3f &o_error_in,
                 const Vector3f &d_error_in, Vector3f *o_error_out,
                 Vector3f *d_error_out) const;

  Transform operator*(const Transform &t2) const;

  bool operator==(const Transform &t) const;
  bool operator!=(const Transform &t) const;
  bool operator<(const Transform &t2) const;

  bool is_identity() const;
  bool has_scale() const;
  bool swaps_handedness() const;

  inline const Matrix4x4<Float> &get_matrix() const { return m; }
  inline const Matrix4x4<Float> &get_inverse_matrix() const { return m_inv; }

  friend Transform inverse(const Transform &t);
  friend Transform transpose(const Transform &t);

private:
  Matrix4x4<Float> m, m_inv;
};

Transform translate(const Vector3f &delta);
Transform scale(Float x, Float y, Float z);
Transform rotate_x(Float theta);
Transform rotate_y(Float theta);
Transform rotate_z(Float theta);
Transform rotate(Float theta, const Vector3f &axis);

Transform look_at(const Point3f &pos, const Point3f &look, const Vector3f &up);

Transform orthographic(Float z_near, Float z_far);
Transform perspective(Float fov, Float n, Float f);
} // namespace specula

#endif // SPECULA_CORE_TRANSFORM_HPP_
