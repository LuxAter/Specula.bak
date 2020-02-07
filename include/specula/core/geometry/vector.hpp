#ifndef SPECULA_CORE_GEOMETRY_VECTOR_HPP_
#define SPECULA_CORE_GEOMETRY_VECTOR_HPP_

#include "../../global.hpp"

namespace specula {
template <std::size_t N, typename T, glm::qualifier Q = glm::defaultp>
class Vector : public glm::vec<N, T, Q> {
public:
  Vector() : glm::vec<N, T, Q>() {}
  Vector(const glm::vec<N, T, Q> &v) : glm::vec<N, T, Q>(v) {}
  template <typename... Args>
  Vector(const Args &... args) : glm::vec<N, T, Q>(args...) {}
  template <std::size_t M = N>
  typename std::enable_if<M == N && M == 2, std::string>::type fmt() const {
    return fmt::format("<{},{}>", this->x, this->y);
  }
  template <std::size_t M = N>
  typename std::enable_if<M == N && M == 3, std::string>::type fmt() const {
    return fmt::format("<{},{},{}>", this->x, this->y, this->z);
  }
  template <std::size_t M = N>
  typename std::enable_if<M == N && M == 4, std::string>::type fmt() const {
    return fmt::format("<{},{},{},{}>", this->x, this->y, this->z, this->w);
  }

  operator const glm::vec<N, T, Q> &() const {
    return *reinterpret_cast<glm::vec<N, T, Q>>(this);
  }
  operator glm::vec<N, T, Q> &() {
    return *reinterpret_cast<glm::vec<N, T, Q>>(this);
  }
};

template <typename T, glm::qualifier Q = glm::defaultp>
using Vector2 = Vector<2, T, Q>;
template <typename T, glm::qualifier Q = glm::defaultp>
using Vector3 = Vector<3, T, Q>;
template <typename T, glm::qualifier Q = glm::defaultp>
using Vector4 = Vector<4, T, Q>;

typedef Vector<2, Float> Vector2f;
typedef Vector<2, Int> Vector2i;
typedef Vector<3, Float> Vector3f;
typedef Vector<3, Int> Vector3i;
typedef Vector<4, Float> Vector4f;
typedef Vector<4, Int> Vector4i;

template <std::size_t N, typename T, glm::qualifier Q>
std::ostream &operator<<(std::ostream &out, const Vector<N, T, Q> &v) {
  return out << v.fmt();
}

template <std::size_t N, typename T, glm::qualifier Q>
inline T length2(const Vector<N, T, Q> &v) {
  return glm::length2<N, T, Q>(v);
}
template <typename T, glm::qualifier Q>
inline Vector3<T, Q> cross(const Vector3<T, Q> &v1, const Vector3<T, Q> &v2) {
  return glm::cross<T, Q>(v1, v2);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline T dot(const Vector<N, T, Q> &v1, const Vector<N, T, Q> &v2) {
  return glm::dot<N, T, Q>(v1, v2);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Vector<N, T, Q> abs(const Vector<N, T, Q> &v) {
  return glm::abs<N, T, Q>(v);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Vector<N, T, Q> ceil(const Vector<N, T, Q> &v) {
  return glm::ceil<N, T, Q>(v);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Vector<N, T, Q> clamp(const Vector<N, T, Q> &x,
                             const Vector<N, T, Q> &min_val,
                             const Vector<N, T, Q> &max_val) {
  return glm::clamp<N, T, Q>(x, min_val, max_val);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Vector<N, T, Q> floor(const Vector<N, T, Q> &v) {
  return glm::floor<N, T, Q>(v);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Vector<N, T, Q> isinf(const Vector<N, T, Q> &v) {
  return glm::isinf<N, T, Q>(v);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Vector<N, T, Q> isnan(const Vector<N, T, Q> &v) {
  return glm::isnan<N, T, Q>(v);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Vector<N, T, Q> max(const Vector<N, T, Q> &v1, const Vector<N, T, Q> &v2) {
  return glm::max<N, T, Q>(v1, v2);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Vector<N, T, Q> min(const Vector<N, T, Q> &v1, const Vector<N, T, Q> &v2) {
  return glm::min<N, T, Q>(v1, v2);
}
template <std::size_t N, typename T, typename U, glm::qualifier Q>
inline Vector<N, T, Q> mix(const Vector<N, T, Q> &v1, const Vector<N, T, Q> &v2, const U& t) {
  return glm::mix<N, T, Q>(v1, v2, t);
}

} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_VECTOR_HPP_
