#ifndef SPECULA_CORE_GEOMETRY_QUATERNION_HPP_
#define SPECULA_CORE_GEOMETRY_QUATERNION_HPP_

#include "../../global.hpp"

namespace specula {
template <typename T, glm::qualifier Q = glm::defaultp>
class Quaternion : public glm::qua<T, Q> {
public:
  template <typename... Args>
  Quaternion(const Args &... args) : glm::qua<T, Q>(args...) {}

  std::string fmt() const {
    return fmt::format("{}{:+}i{:+}j{:+}k", this->w, this->x, this->y, this->z);
  }
};

typedef Quaternion<Float> Quaternionf;
typedef Quaternion<Int> Quaternioni;

template <typename T, glm::qualifier Q>
std::ostream &operator<<(std::ostream &out, const Quaternion<T, Q> &q) {
  return out << q.fmt();
}
template <typename T, glm::qualifier Q>
Quaternion<T, Q> slerp(const Quaternion<T, Q> &q1, const Quaternion<T, Q> &q2,
                       Float t) {
  Float cos_theta = dot(q1, q2);
  if (cos_theta > 0.9995f) {
    return normalize((1 - t) * q1 + t * q2);
  } else {
    Float theta = std::acos(clamp(cos_theta, -1, 1));
    Float thetap = theta * t;
    Quaternion<T, Q> qperp = normalize(q2 - q1 * cos_theta);
    return q1 * std::cos(thetap) + qperp * std::sin(thetap);
  }
}

template <typename T, glm::qualifier Q>
inline T length2(const Quaternion<T, Q> &v) {
  return glm::length2<T, Q>(v);
}
template <typename T, glm::qualifier Q>
inline T dot(const Quaternion<T, Q> &v1, const Quaternion<T, Q> &v2) {
  return glm::dot<T, Q>(v1, v2);
}
template <typename T, glm::qualifier Q>
inline Quaternion<T, Q> abs(const Quaternion<T, Q> &v) {
  return glm::abs<T, Q>(v);
}
template <typename T, glm::qualifier Q>
inline Quaternion<T, Q> ceil(const Quaternion<T, Q> &v) {
  return glm::ceil<T, Q>(v);
}
template <typename T, glm::qualifier Q>
inline Quaternion<T, Q> clamp(const Quaternion<T, Q> &x,
                              const Quaternion<T, Q> &min_val,
                              const Quaternion<T, Q> &max_val) {
  return glm::clamp<T, Q>(x, min_val, max_val);
}
template <typename T, glm::qualifier Q>
inline Quaternion<T, Q> floor(const Quaternion<T, Q> &v) {
  return glm::floor<T, Q>(v);
}
template <typename T, glm::qualifier Q>
inline Quaternion<T, Q> isinf(const Quaternion<T, Q> &v) {
  return glm::isinf<T, Q>(v);
}
template <typename T, glm::qualifier Q>
inline Quaternion<T, Q> isnan(const Quaternion<T, Q> &v) {
  return glm::isnan<T, Q>(v);
}
template <typename T, glm::qualifier Q>
inline Quaternion<T, Q> max(const Quaternion<T, Q> &v1,
                            const Quaternion<T, Q> &v2) {
  return glm::max<T, Q>(v1, v2);
}
template <typename T, glm::qualifier Q>
inline Quaternion<T, Q> min(const Quaternion<T, Q> &v1,
                            const Quaternion<T, Q> &v2) {
  return glm::min<T, Q>(v1, v2);
}
template <typename T, typename U, glm::qualifier Q>
inline Quaternion<T, Q> mix(const Quaternion<T, Q> &v1,
                            const Quaternion<T, Q> &v2, const U &t) {
  return glm::mix<T, Q>(v1, v2, t);
}

} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_QUATERNION_HPP_
