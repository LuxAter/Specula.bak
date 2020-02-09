#ifndef SPECULA_CORE_GEOMETRY_NORMAL_HPP_
#define SPECULA_CORE_GEOMETRY_NORMAL_HPP_

#include "../../global.hpp"
#include "inheritance.hpp"

namespace specula {
template <std::size_t N, typename T, glm::qualifier Q = glm::defaultp>
class Normal : public GlmInheritance, public glm::vec<N, T, Q> {
public:
  typedef glm::vec<N, T, Q> glm_type;
  typedef glm::length_t size_type;

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

  glm::vec<N, T, Q> &get_glm() {
    return *reinterpret_cast<glm::vec<N, T, Q> *>(this);
  }
  SPECULA_CONSTEXPR const glm::vec<N, T, Q> &get_glm() const {
    return *reinterpret_cast<const glm::vec<N, T, Q> *>(this);
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
} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_NORMAL_HPP_