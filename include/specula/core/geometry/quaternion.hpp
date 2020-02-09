#ifndef SPECULA_CORE_GEOMETRY_QUATERNION_HPP_
#define SPECULA_CORE_GEOMETRY_QUATERNION_HPP_

#include "../../global.hpp"
#include "inheritance.hpp"

namespace specula {
template <typename T, glm::qualifier Q = glm::defaultp>
class Quaternion : public GlmInheritance, public glm::qua<T, Q> {
public:
  typedef glm::qua<T, Q> glm_type;
  typedef glm::length_t size_type;

  template <typename... Args>
  Quaternion(const Args &... args) : glm::qua<T, Q>(args...) {}
  Quaternion(const Matrix<3, 3, T, Q> &m) : glm::qua<T, Q>(glm::quat_cast(m)) {}
  Quaternion(const Matrix<4, 4, T, Q> &m) : glm::qua<T, Q>(glm::quat_cast(m)) {}

  std::string fmt() const {
    return fmt::format("{}{:+}i{:+}j{:+}k", this->w, this->x, this->y, this->z);
  }

  glm::qua<T, Q> &get_glm() {
    return *reinterpret_cast<glm::qua<T, Q> *>(this);
  }
  SPECULA_CONSTEXPR const glm::qua<T, Q> &get_glm() const {
    return *reinterpret_cast<const glm::qua<T, Q> *>(this);
  }
};
typedef Quaternion<Float> Quaternionf;
typedef Quaternion<Int> Quaternioni;

template <typename T, glm::qualifier Q>
std::ostream &operator<<(std::ostream &out, const Quaternion<T, Q> &q) {
  return out << q.fmt();
}
} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_QUATERNION_HPP_