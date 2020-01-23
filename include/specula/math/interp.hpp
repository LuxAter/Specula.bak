#ifndef SPECULA_MATH_INTERP_HPP_
#define SPECULA_MATH_INTERP_HPP_

#include "../types.hpp"

namespace specula {
template <typename T> inline T lerp(const T &a, const T &b, const Float &t) {
  return (1 - t) * a + t * b;
}
} // namespace specula

#endif // SPECULA_MATH_INTERP_HPP_