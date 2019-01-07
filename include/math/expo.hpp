#ifndef SPECULA_MATH_EXPO_HPP_
#define SPECULA_MATH_EXPO_HPP_

#include <cmath>

#include "vector.hpp"

namespace specula {
namespace math {

  template <typename _T>
  inline _T pow(const _T& x, const _T& y) {
    return std::pow(x, y);
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> pow(const vec<_T, _N>& x, const vec<_T, _N>& y) {
    return component_op(x, y, math::pow);
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> pow(const vec<_T, _N>& x, const _T& y) {
    return component_op(x, y, math::pow);
  }

  template <typename _T>
  inline _T exp(const _T& x) {
    return std::exp(x);
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> exp(const vec<_T, _N>& x) {
    return component_op(x, math::exp);
  }

  template <typename _T>
  inline _T log(const _T& x) {
    return std::log(x);
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> log(const vec<_T, _N>& x) {
    return component_op(x, math::log);
  }

  template <typename _T>
  inline _T exp2(const _T& x) {
    return std::exp2(x);
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> exp2(const vec<_T, _N>& x) {
    return component_op(x, math::exp2);
  }

  template <typename _T>
  inline _T log2(const _T& x) {
    return std::log2(x);
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> log2(const vec<_T, _N>& x) {
    return component_op(x, math::log2);
  }

  template <typename _T>
  inline _T sqrt(const _T& x) {
    return std::sqrt(x);
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> sqrt(const vec<_T, _N>& x) {
    return component_op(x, math::sqrt);
  }
}  // namespace math
}  // namespace specula

#endif  // SPECULA_MATH_EXPO_HPP_
