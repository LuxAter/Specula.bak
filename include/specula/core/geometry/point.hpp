#ifndef SPECULA_CORE_GEOMETRY_POINT_HPP_
#define SPECULA_CORE_GEOMETRY_POINT_HPP_

#include "../../global.hpp"

namespace specula {
template <std::size_t N, typename T, glm::qualifier Q = glm::defaultp>
class Point : public glm::vec<N, T, Q> {
public:
  Point() : glm::vec<N, T, Q>() {}
  Point(const glm::vec<N, T, Q> &v) : glm::vec<N, T, Q>(v) {}
  template <typename... Args>
  Point(const Args &... args) : glm::vec<N, T, Q>(args...) {}
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
using Point2 = Point<2, T, Q>;
template <typename T, glm::qualifier Q = glm::defaultp>
using Point3 = Point<3, T, Q>;
template <typename T, glm::qualifier Q = glm::defaultp>
using Point4 = Point<4, T, Q>;

typedef Point<2, Float> Point2f;
typedef Point<2, Int> Point2i;
typedef Point<3, Float> Point3f;
typedef Point<3, Int> Point3i;
typedef Point<4, Float> Point4f;
typedef Point<4, Int> Point4i;

template <std::size_t N, typename T, glm::qualifier Q>
std::ostream &operator<<(std::ostream &out, const Point<N, T, Q> &v) {
  return out << v.fmt();
}

template <std::size_t N, typename T, glm::qualifier Q>
inline T length2(const Point<N, T, Q> &v) {
  return glm::length2<N, T, Q>(v);
}
template <typename T, glm::qualifier Q>
inline Point3<T, Q> cross(const Point3<T, Q> &v1, const Point3<T, Q> &v2) {
  return glm::cross<T, Q>(v1, v2);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline T dot(const Point<N, T, Q> &v1, const Point<N, T, Q> &v2) {
  return glm::dot<N, T, Q>(v1, v2);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Point<N, T, Q> abs(const Point<N, T, Q> &v) {
  return glm::abs<N, T, Q>(v);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Point<N, T, Q> ceil(const Point<N, T, Q> &v) {
  return glm::ceil<N, T, Q>(v);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Point<N, T, Q> clamp(const Point<N, T, Q> &x,
                             const Point<N, T, Q> &min_val,
                             const Point<N, T, Q> &max_val) {
  return glm::clamp<N, T, Q>(x, min_val, max_val);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Point<N, T, Q> floor(const Point<N, T, Q> &v) {
  return glm::floor<N, T, Q>(v);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Point<N, T, Q> isinf(const Point<N, T, Q> &v) {
  return glm::isinf<N, T, Q>(v);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Point<N, T, Q> isnan(const Point<N, T, Q> &v) {
  return glm::isnan<N, T, Q>(v);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Point<N, T, Q> max(const Point<N, T, Q> &v1, const Point<N, T, Q> &v2) {
  return glm::max<N, T, Q>(v1, v2);
}
template <std::size_t N, typename T, glm::qualifier Q>
inline Point<N, T, Q> min(const Point<N, T, Q> &v1, const Point<N, T, Q> &v2) {
  return glm::min<N, T, Q>(v1, v2);
}
template <std::size_t N, typename T, typename U, glm::qualifier Q>
inline Point<N, T, Q> mix(const Point<N, T, Q> &v1, const Point<N, T, Q> &v2, const U& t) {
  return glm::mix<N, T, Q>(v1, v2, t);
}
} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_POINT_HPP_
