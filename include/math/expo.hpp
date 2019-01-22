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
  template <typename _T>
  inline vec2<_T> pow(const vec2<_T>& x, const vec2<_T>& y) {
    return component_op(x, y, math::pow);
  }
  template <typename _T>
  inline vec3<_T> pow(const vec3<_T>& x, const vec3<_T>& y) {
    return component_op(x, y, math::pow);
  }
  template <typename _T>
  inline vec4<_T> pow(const vec4<_T>& x, const vec4<_T>& y) {
    return component_op(x, y, math::pow);
  }
  template <typename _T>
  inline vec2<_T> pow(const vec2<_T>& x, const _T& y) {
    return component_op(x, y, math::pow);
  }
  template <typename _T>
  inline vec3<_T> pow(const vec3<_T>& x, const _T& y) {
    return component_op(x, y, math::pow);
  }
  template <typename _T>
  inline vec4<_T> pow(const vec4<_T>& x, const _T& y) {
    return component_op(x, y, math::pow);
  }

  template <typename _T>
  inline _T exp(const _T& x) {
    return std::exp(x);
  }
  template <typename _T>
  inline vec2<_T> exp(const vec2<_T>& x) {
    return component_op(x, math::exp);
  }
  template <typename _T>
  inline vec3<_T> exp(const vec3<_T>& x) {
    return component_op(x, math::exp);
  }
  template <typename _T>
  inline vec4<_T> exp(const vec4<_T>& x) {
    return component_op(x, math::exp);
  }

  template <typename _T>
  inline _T log(const _T& x) {
    return std::log(x);
  }
  template <typename _T>
  inline vec2<_T> log(const vec2<_T>& x) {
    return component_op(x, math::log);
  }
  template <typename _T>
  inline vec3<_T> log(const vec3<_T>& x) {
    return component_op(x, math::log);
  }
  template <typename _T>
  inline vec4<_T> log(const vec4<_T>& x) {
    return component_op(x, math::log);
  }

  template <typename _T>
  inline _T exp2(const _T& x) {
    return std::exp2(x);
  }
  template <typename _T>
  inline vec2<_T> exp2(const vec2<_T>& x) {
    return component_op(x, math::exp2);
  }
  template <typename _T>
  inline vec3<_T> exp2(const vec3<_T>& x) {
    return component_op(x, math::exp2);
  }
  template <typename _T>
  inline vec4<_T> exp2(const vec4<_T>& x) {
    return component_op(x, math::exp2);
  }

  template <typename _T>
  inline _T log2(const _T& x) {
    return std::log2(x);
  }
  template <typename _T>
  inline vec2<_T> log2(const vec2<_T>& x) {
    return component_op(x, math::log2);
  }
  template <typename _T>
  inline vec3<_T> log2(const vec3<_T>& x) {
    return component_op(x, math::log2);
  }
  template <typename _T>
  inline vec4<_T> log2(const vec4<_T>& x) {
    return component_op(x, math::log2);
  }

  template <typename _T>
  inline _T sqrt(const _T& x) {
    return std::sqrt(x);
  }
  template <typename _T>
  inline vec2<_T> sqrt(const vec2<_T>& x) {
    return component_op(x, math::sqrt);
  }
  template <typename _T>
  inline vec3<_T> sqrt(const vec3<_T>& x) {
    return component_op(x, math::sqrt);
  }
  template <typename _T>
  inline vec4<_T> sqrt(const vec4<_T>& x) {
    return component_op(x, math::sqrt);
  }
}  // namespace math
}  // namespace specula

#endif  // SPECULA_MATH_EXPO_HPP_
