#ifndef SPECULA_CORE_GEOMETRY_VECTOR_HPP_
#define SPECULA_CORE_GEOMETRY_VECTOR_HPP_

#include "../../global.hpp"
#include "inheritance.hpp"

namespace specula {
template <std::size_t N, typename T, glm::qualifier Q = glm::defaultp>
class Vector : public GlmInheritance, public glm::vec<N, T, Q> {
public:
  typedef glm::vec<N, T, Q> glm_type;
  typedef glm::length_t size_type;

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

  glm::vec<N, T, Q> &get_glm() {
    return *reinterpret_cast<glm::vec<N, T, Q> *>(this);
  }
  SPECULA_CONSTEXPR const glm::vec<N, T, Q> &get_glm() const {
    return *reinterpret_cast<const glm::vec<N, T, Q> *>(this);
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
} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_VECTOR_HPP_