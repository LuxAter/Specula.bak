#ifndef SPECULA_MATH_HPP_
#define SPECULA_MATH_HPP_

namespace glm {
template <typename genType>
genType lerp(genType const &a, genType const &b, const float &t) {
  return a + t * b;
}
} // namespace glm

#endif // SPECULA_MATH_HPP_
