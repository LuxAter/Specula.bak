#ifndef SPECULA_MATH_STD_FUNCTIONS_HPP_
#define SPECULA_MATH_STD_FUNCTIONS_HPP_

#include <algorithm>
#include <cmath>
#include <numeric>

#include "generator.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

namespace specula {
namespace {
template <typename _T>
inline typename std::enable_if<std::is_arithmetic<_T>::value, _T>::type
__lerp(const _T &a, const _T &b, const _T &t) {
  return a + t * (b - a);
}
} // namespace

FUNC1(fabs, std::fabs)
FUNC1(abs, std::fabs)
FUNC2(fmod, std::fmod)
FUNC2(mod, std::fmod)
FUNC2(remainder, std::remainder)
FUNC2(remquo, std::remquo)
FUNC3(fma, std::fma)
FUNC2(fmax, std::fmax)
FUNC2(max, std::fmax)
FUNC2(fmin, std::fmin)
FUNC2(min, std::fmin)
FUNC2(fdim, std::fdim)
FUNC2(dim, std::fdim)
// FUNC3(lerp, std::lerp)

FUNC1(exp, std::exp)
FUNC1(exp2, std::exp2)
FUNC1(expm1, std::expm1)
FUNC1(log, std::log)
FUNC1(log10, std::log10)
FUNC1(log2, std::log2)
FUNC1(log1p, std::log1p)

FUNC2(pow, std::pow)
FUNC1(sqrt, std::sqrt)
FUNC1(cbrt, std::cbrt)
FUNC2(hypot, std::hypot)
FUNC3(hypot, std::hypot)

FUNC1(sin, std::sin)
FUNC1(cos, std::cos)
FUNC1(tan, std::tan)
FUNC1(asin, std::asin)
FUNC1(acos, std::acos)
FUNC1(atan, std::atan)
FUNC2(atan2, std::atan2)

FUNC1(sinh, std::sinh)
FUNC1(cosh, std::cosh)
FUNC1(tanh, std::tanh)
FUNC1(asinh, std::asinh)
FUNC1(acosh, std::acosh)
FUNC1(atanh, std::atanh)

FUNC1(erf, std::erf)
FUNC1(tgamma, std::tgamma)
FUNC1(lgamma, std::lgamma)

FUNC1(ceil, std::ceil)
FUNC1(floor, std::floor)
FUNC1(trunc, std::trunc)
FUNC1(round, std::round)
FUNC1(nearbyint, std::nearbyint)
FUNC1(rint, std::rint)

FUNC2(ldexp, std::ldexp)
FUNC2(scalbn, std::scalbn)
FUNC1(ilogb, std::ilogb)
FUNC1(logb, std::logb)
FUNC2(nextafter, std::nextafter)
FUNC2(nexttoward, std::nexttoward)
FUNC2(copysign, std::copysign)

// template <typename _T>
// inline _T distance(const vec2<_T> &a, const vec2<_T> &b) {
//   return length(b - a);
// }
//
// template <typename _T> inline _T dot(const vec2<_T> &a, const vec2<_T> &b) {
//   return a.x * b.x + a.y * b.y;
// }
// template <typename _T>
// inline _T faceforward(const vec2<_T> &N, const vec2<_T> &I,
//                       const vec2<_T> &Nref) {
//   return dot(Nref, I) < static_cast<_T>(0) ? N : -N;
// }
// template <typename _T> inline _T length(const vec2<_T> &a) {
//   return std::sqrt(a.x * a.x + a.y + a.y);
// }
// template <typename _T> inline _T normalize(const vec2<_T> &a) {
//   return a / std::sqrt(a.x * a.x + a.y * a.y);
// }
// template <typename _T>
// inline vec2<_T> reflect(const vec2<_T> &I, const vec2<_T> &N) {
//   return I - N * dot(N, I) * static_cast<_T>(2);
// }
// template <typename _T>
// inline vec2<_T> refract(const vec2<_T> &I, const vec2<_T> &N, const _T &eta)
// {
//   _T const dot_value(dot(N, I));
//   _T const k(static_cast<_T>(1) -
//              eta * eta * (static_cast<_T>(1) - dot_value * dot_value));
//   return (k >= static_cast<_T>(0))
//              ? (eta * I - (eta * dot_value + std::sqrt(k)) * N)
//              : vec2<_T>(0);
// }

} // namespace specula

#endif // SPECULA_MATH_STD_FUNCTIONS_HPP_
