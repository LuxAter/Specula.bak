#ifndef SPECULA_TRANSFORM_TRANSFORM_HPP_
#define SPECULA_TRANSFORM_TRANSFORM_HPP_

#include "../global.hpp"

#include "../math/common.hpp"
#include "../math/geometric.hpp"
#include "../math/matrix/matrix4x4.hpp"
#include "../math/normal/normal3.hpp"
#include "../math/point/point3.hpp"
#include "../math/ray.hpp"
#include "../math/ray_differential.hpp"
#include "../math/vector/vector3.hpp"

namespace specula {
class Transform {
public:
  Transform();
  Transform(const Float mat[4][4]);
  Transform(const Matrix4x4f &m);
  Transform(const Matrix4x4f &m, const Matrix4x4f &inv);

  static Transform translate(const Vector3f &delta);
  static Transform scale(Float x, Float y, Float z);
  static Transform rotate_x(Float theta);
  static Transform rotate_y(Float theta);
  static Transform rotate_z(Float theta);
  static Transform rotate(Float theta, const Vector3f &axis);
  static Transform look_at(const Point3f &pos, const Point3f &look,
                           const Vector3f &up);
  static Transform orthographic(Float znear, Float zfar);
  static Transform perspective(Float fov, Float znear, Float zfar);

  inline bool operator==(const Transform &t) const {
    return t.m == m && t.inv == inv;
  }
  inline bool operator!=(const Transform &t) const {
    return t.m != m || t.inv != inv;
  }
  inline bool operator<(const Transform &t2) const {
    for (typename Matrix4x4f::size_type i = 0; i < 4; ++i) {
      for (typename Matrix4x4f::size_type j = 0; j < 4; ++j) {
        if (m.data[i][j] < t2.m.data[i][j])
          return true;
        else if (m.data[i][j] > t2.m.data[i][j])
          return false;
      }
    }
    return false;
  }
  inline bool is_identity() const {
    return m.data[0][0] == 1.0f && m.data[0][1] == 0.0f &&
           m.data[0][2] == 0.0f && m.data[0][3] == 0.0f &&
           m.data[1][0] == 0.0f && m.data[1][1] == 1.0f &&
           m.data[1][2] == 0.0f && m.data[1][3] == 0.0f &&
           m.data[2][0] == 0.0f && m.data[2][1] == 0.0f &&
           m.data[2][2] == 1.0f && m.data[2][3] == 0.0f &&
           m.data[3][0] == 0.0f && m.data[3][1] == 0.0f &&
           m.data[3][2] == 0.0f && m.data[3][3] == 1.0f;
  }
  inline const Matrix4x4f &get_matrix() const { return m; }
  inline const Matrix4x4f &get_inverse_matrix() const { return inv; }
  inline bool has_scale() const {
    Float la2 = (*this)(Vector3f(1, 0, 0)).length_squared();
    Float lb2 = (*this)(Vector3f(0, 1, 0)).length_squared();
    Float lc2 = (*this)(Vector3f(0, 0, 1)).length_squared();
#define NOT_ONE(x) ((x) < 0.999f || (x) > 1.001f)
    return NOT_ONE(la2) || NOT_ONE(lb2) || NOT_ONE(lc2);
#undef NOT_ONE
  }
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
        inv.data[0][0] * x + inv.data[1][0] * y + inv.data[2][0] * z,
        inv.data[0][1] * x + inv.data[1][1] * y + inv.data[2][1] * z,
        inv.data[0][2] * x + inv.data[1][2] * y + inv.data[2][2] * z);
  }
  Ray operator()(const Ray &r) const;
  RayDifferential operator()(const RayDifferential &r) const;
  Bounds3f operator()(const Bounds3f &b) const;
  Transform operator*(const Transform &t2) const;
  bool swaps_handedness() const;

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
  inline Point3<T> operator()(const Point3<T> &p, const Vector3<T> &error,
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
        (gamma(3) * T(1)) * (std::abs(m.data[0][0]) * error->x +
                             std::abs(m.data[0][1]) * error->y +
                             std::abs(m.data[0][2]) * error->z) +
        gamma(3) * (std::abs(m.data[0][0] * x) + std::abs(m.data[0][1] * y) +
                    std::abs(m.data[0][2] * z) + std::abs(m.data[0][3]));
    abs_error->y =
        (gamma(3) * T(1)) * (std::abs(m.data[1][0]) * error->x +
                             std::abs(m.data[1][1]) * error->y +
                             std::abs(m.data[1][2]) * error->z) +
        gamma(3) * (std::abs(m.data[1][0] * x) + std::abs(m.data[1][1] * y) +
                    std::abs(m.data[1][2] * z) + std::abs(m.data[1][3]));
    abs_error->z =
        (gamma(3) * T(1)) * (std::abs(m.data[2][0]) * error->x +
                             std::abs(m.data[2][1]) * error->y +
                             std::abs(m.data[2][2]) * error->z) +
        gamma(3) * (std::abs(m.data[2][0] * x) + std::abs(m.data[2][1] * y) +
                    std::abs(m.data[2][2] * z) + std::abs(m.data[2][3]));
    CHECK_NE(wp, 0);
    if (wp == 1.0f)
      return Point3<T>(xp, yp, zp);
    else
      return Point3<T>(xp, yp, zp) / wp;
  }

  friend Transform inverse(const Transform &t) { return Transform(t.inv, t.m); }
  friend Transform transpose(const Transform &t) {
    return Transform(transpose(t.m), transpose(t.inv));
  }

private:
  Matrix4x4f m, inv;
  friend class Quaternion;
  friend class AnimatedTransform;
};
} // namespace specula

#endif // SPECULA_TRANSFORM_TRANSFORM_HPP_
