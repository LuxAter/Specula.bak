#ifndef SPECULA_CORE_GEOMETRY_NORMAL_HPP_
#define SPECULA_CORE_GEOMETRY_NORMAL_HPP_

#include "../../global.hpp"

namespace specula {
template <std::size_t N, typename T, glm::qualifier Q = glm::defaultp>
class Normal : public glm::vec<N, T, Q> {
public:
  Normal() : glm::vec<N, T, Q>() {}
  Normal(const glm::vec<N, T, Q> &v) : glm::vec<N, T, Q>(v) {}
  template <typename... Args>
  Normal(const Args &... args) : glm::vec<N, T, Q>(args...) {}
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
};

template <typename T, glm::qualifier Q = glm::defaultp>
using Normal2 = Normal<2, T, Q>;
template <typename T, glm::qualifier Q = glm::defaultp>
using Normal3 = Normal<3, T, Q>;
template <typename T, glm::qualifier Q = glm::defaultp>
using Normal4 = Normal<4, T, Q>;

typedef Normal<2, Float> Normal2f;
typedef Normal<2, Int> Normal2i;
typedef Normal<3, Float> Normal3f;
typedef Normal<3, Int> Normal3i;
typedef Normal<4, Float> Normal4f;
typedef Normal<4, Int> Normal4i;

template <std::size_t N, typename T, glm::qualifier Q>
std::ostream &operator<<(std::ostream &out, const Normal<N, T, Q> &v) {
  return out << v.fmt();
}

template <std::size_t N, typename T, glm::qualifier Q>
inline T length2(const Normal<N, T, Q> &v) {
  return glm::length2<N, T, Q>(v);
}
template <typename T, glm::qualifier Q>
inline Normal3<T, Q> cross(const Normal3<T, Q> &v1, const Normal3<T, Q> &v2) {
  return glm::cross<T, Q>(v1, v2);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline T dot(const Normal<N, T, Q> &v1, const Normal<N, T, Q> &v2) {
  return glm::dot<N, T, Q>(v1, v2);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Normal<N, T, Q> abs(const Normal<N, T, Q> &v) {
  return glm::abs<N, T, Q>(v);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Normal<N, T, Q> ceil(const Normal<N, T, Q> &v) {
  return glm::ceil<N, T, Q>(v);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Normal<N, T, Q> clamp(const Normal<N, T, Q> &x,
                             const Normal<N, T, Q> &min_val,
                             const Normal<N, T, Q> &max_val) {
  return glm::clamp<N, T, Q>(x, min_val, max_val);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Normal<N, T, Q> floor(const Normal<N, T, Q> &v) {
  return glm::floor<N, T, Q>(v);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Normal<N, T, Q> isinf(const Normal<N, T, Q> &v) {
  return glm::isinf<N, T, Q>(v);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Normal<N, T, Q> isnan(const Normal<N, T, Q> &v) {
  return glm::isnan<N, T, Q>(v);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Normal<N, T, Q> max(const Normal<N, T, Q> &v1, const Normal<N, T, Q> &v2) {
  return glm::max<N, T, Q>(v1, v2);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Normal<N, T, Q> min(const Normal<N, T, Q> &v1, const Normal<N, T, Q> &v2) {
  return glm::min<N, T, Q>(v1, v2);
}
template <std::size_t N, typename T, typename U, glm::qualifier Q>
inline Normal<N, T, Q> mix(const Normal<N, T, Q> &v1, const Normal<N, T, Q> &v2, const U& t) {
  return glm::mix<N, T, Q>(v1, v2, t);
}
} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_NORMAL_HPP_
