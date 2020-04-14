#ifndef SPECULA_CORE_QUATERNION_HPP_
#define SPECULA_CORE_QUATERNION_HPP_

#include "geometry.hpp"
#include "specula/global.hpp"

namespace specula {
struct Quaternion {
  Quaternion() : v(0, 0, 0), w(1) {}
  Quaternion(const Transform &t);

  Quaternion &operator+=(const Quaternion &q) {
    v += q.v;
    w += q.w;
    return *this;
  }
  Quaternion operator+(const Quaternion &q) const {
    Quaternion ret;
    ret.v = v + q.v;
    ret.w = w + q.w;
    return ret;
  }
  Quaternion &operator-=(const Quaternion &q) {
    v -= q.v;
    w -= q.w;
    return *this;
  }
  Quaternion operator-(const Quaternion &q) const {
    Quaternion ret;
    ret.v = v - q.v;
    ret.w = w - q.w;
    return ret;
  }
  Quaternion &operator*=(Float f) {
    v *= f;
    w *= f;
    return *this;
  }
  Quaternion operator*(Float f) const {
    Quaternion ret;
    ret.v = v * f;
    ret.w = w * f;
    return ret;
  }
  friend Quaternion operator*(Float f, const Quaternion &q) {
    Quaternion ret;
    ret.v = q.v * f;
    ret.w = q.w * f;
    return ret;
  }
  Quaternion &operator/=(Float f) {
    v /= f;
    w /= f;
    return *this;
  }
  Quaternion operator/(Float f) const {
    Quaternion ret;
    ret.v = v / f;
    ret.w = w / f;
    return ret;
  }

  Quaternion operator-() const {
    Quaternion ret;
    ret.v = -v;
    ret.w = -w;
    return ret;
  }

  Transform to_transform() const;

  inline std::string fmt() const {
    return fmt::format("[{}, {}, {}, {}]", v.x, v.y, v.z, w);
  }

  Vector3f v;
  Float w;
};

inline std::ostream &operator<<(std::ostream &out, const Quaternion &v) {
  return out << v.fmt();
}

Quaternion slerp(Float t, const Quaternion &q1, const Quaternion &q2);
inline Float dot(const Quaternion &q1, const Quaternion &q2) {
  return dot(q1.v, q2.v) + q1.w * q2.w;
}
inline Quaternion normalize(const Quaternion &q) {
  return q / std::sqrt(dot(q, q));
}

} // namespace specula

#endif /* end of include guard: SPECULA_CORE_QUATERNION_HPP_ */
