#ifndef SPECULA_TRANSFORM_HPP_
#define SPECULA_TRANSFORM_HPP_

#include "math/common.hpp"
#include "math/geometric.hpp"
#include "math/matrix/matrix4x4.hpp"
#include "math/normal/normal3.hpp"
#include "math/point/point3.hpp"
#include "math/ray.hpp"
#include "math/ray_differential.hpp"
#include "math/vector/vector3.hpp"
#include "types.hpp"

namespace specula {
class Transform {
public:
  Transform();
  Transform(const Float mat[4][4]);
  Transform(const Matrix4x4f &m);
  Transform(const Matrix4x4f &m, const Matrix4x4f &inv);

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
    SPECULA_ASSERT(wp != 0);
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
  inline Ray operator()(const Ray &r) const {
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
  inline RayDifferential operator()(const RayDifferential &r) const {
    Ray tr = (*this)(Ray(r));
    RayDifferential ret(tr.o, tr.d, tr.t_max, tr.time, tr.medium);
    ret.has_differentials = r.has_differentials;
    ret.rx_origin = (*this)(r.rx_origin);
    ret.ry_origin = (*this)(r.ry_origin);
    ret.rx_direction = (*this)(r.rx_direction);
    ret.ry_direction = (*this)(r.ry_direction);
    return ret;
  }
  template <typename T>
  inline Point3<T> operator()(const Point3<T> &p, Vector3<T> *p_error) const {}

private:
  Matrix4x4f m, inv;
};

Transform inverse(const Transform &t);
Transform transpose(const Transform &t);
} // namespace specula

#endif // SPECULA_TRANSFORM_HPP_
