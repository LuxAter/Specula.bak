#ifndef SPECULA_CORE_GEOMETRY_POINT_HPP_
#define SPECULA_CORE_GEOMETRY_POINT_HPP_

#include "../../global.hpp"
#include "inheritance.hpp"

namespace specula {
template <std::size_t N, typename T, glm::qualifier Q = glm::defaultp>
class Point : public GlmInheritance, public glm::vec<N, T, Q> {
public:
  typedef glm::vec<N, T, Q> glm_type;
  typedef glm::length_t size_type;

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

  glm::vec<N, T, Q> &get_glm() {
    return *reinterpret_cast<glm::vec<N, T, Q> *>(this);
  }
  SPECULA_CONSTEXPR const glm::vec<N, T, Q> &get_glm() const {
    return *reinterpret_cast<const glm::vec<N, T, Q> *>(this);
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
} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_POINT_HPP_