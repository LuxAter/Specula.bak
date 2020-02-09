#ifndef SPECULA_CORE_GEOMETRY_NORM_HPP_
#define SPECULA_CORE_GEOMETRY_NORM_HPP_

#include <type_traits>

#include "matrix.hpp"
#include "normal.hpp"
#include "point.hpp"
#include "quaternion.hpp"
#include "vector.hpp"

#include "inheritance.hpp"

namespace specula {
GLM_FUNC(distance2, p0, p1);
// GLM_FUNC(length2, x);
template <typename T>
inline auto length2(const T &x) -> typename std::enable_if<
    std::is_base_of<GlmInheritance, T>::value &&
        std::is_same<typename T::glm_type,
                     decltype(glm::length2(x.get_glm()))>::value,
    T>::type {
  return glm::length2(x.get_glm());
}
template <typename T>
inline auto length2(const T &x) -> typename std::enable_if<
    std::is_base_of<GlmInheritance, T>::value &&
        !std::is_same<typename T::glm_type,
                      decltype(glm::length2(x.get_glm()))>::value,
    decltype(glm::length2(x.get_glm()))>::type {
  return glm::length2(x.get_glm());
}
template <typename T>
inline auto length2(const T &x) ->
    typename std::enable_if<!std::is_base_of<GlmInheritance, T>::value,
                            decltype(glm::length2(x))>::type {
  return glm::length2(x);
}
} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_NORM_HPP_