#ifndef SPECULA_MATH_COMMON_HPP_
#define SPECULA_MATH_COMMON_HPP_

#include <cmath>

#include "vector.hpp"

namespace specula {
namespace math {

  template <typename _T>
  inline _T abs(const _T& x) {
    return std::abs(x);
  }
  template <typename _T>
  inline vec2<_T> abs(const vec2<_T>& x) {
    return component_op(x, math::abs);
  }
  template <typename _T>
  inline vec3<_T> abs(const vec3<_T>& x) {
    return component_op(x, math::abs);
  }
  template <typename _T>
  inline vec4<_T> abs(const vec4<_T>& x) {
    return component_op(x, math::abs);
  }

  template <typename _T>
  inline _T sign(const _T& x) {
    return (_T(0) < x) - (x < _T(0));
  }
  template <typename _T>
  inline vec2<_T> sign(const vec2<_T>& x) {
    return component_op(x, math::sign);
  }
  template <typename _T>
  inline vec3<_T> sign(const vec3<_T>& x) {
    return component_op(x, math::sign);
  }
  template <typename _T>
  inline vec4<_T> sign(const vec4<_T>& x) {
    return component_op(x, math::sign);
  }

  template <typename _T>
  inline _T floor(const _T& x) {
    return std::floor(x);
  }
  template <typename _T>
  inline vec2<_T> floor(const vec2<_T>& x) {
    return component_op(x, math::floor);
  }
  template <typename _T>
  inline vec3<_T> floor(const vec3<_T>& x) {
    return component_op(x, math::floor);
  }
  template <typename _T>
  inline vec4<_T> floor(const vec4<_T>& x) {
    return component_op(x, math::floor);
  }

  template <typename _T>
  inline _T ceil(const _T& x) {
    return std::ceil(x);
  }
  template <typename _T>
  inline vec2<_T> ceil(const vec2<_T>& x) {
    return component_op(x, math::ceil);
  }
  template <typename _T>
  inline vec3<_T> ceil(const vec3<_T>& x) {
    return component_op(x, math::ceil);
  }
  template <typename _T>
  inline vec4<_T> ceil(const vec4<_T>& x) {
    return component_op(x, math::ceil);
  }

  template <typename _T>
  inline _T fract(const _T& x) {
    return (x - std::floor(x));
  }
  template <typename _T>
  inline vec2<_T> fract(const vec2<_T>& x) {
    return component_op(x, math::fract);
  }
  template <typename _T>
  inline vec3<_T> fract(const vec3<_T>& x) {
    return component_op(x, math::fract);
  }
  template <typename _T>
  inline vec4<_T> fract(const vec4<_T>& x) {
    return component_op(x, math::fract);
  }

  template <typename _T>
  inline _T mod(const _T& x, const _T& y) {
    return std::fmod(x, y);
  }
  template <typename _T>
  inline vec2<_T> mod(const vec2<_T>& x, const vec2<_T>& y) {
    return component_op(x, y, math::mod);
  }
  template <typename _T>
  inline vec3<_T> mod(const vec3<_T>& x, const vec3<_T>& y) {
    return component_op(x, y, math::mod);
  }
  template <typename _T>
  inline vec4<_T> mod(const vec4<_T>& x, const vec4<_T>& y) {
    return component_op(x, y, math::mod);
  }

  template <typename _T>
  inline _T min(const _T& x, const _T& y) {
    return std::min(x, y);
  }
  template <typename _T>
  inline vec2<_T> min(const vec2<_T>& x, const vec2<_T>& y) {
    return component_op(x, y, math::min);
  }
  template <typename _T>
  inline vec3<_T> min(const vec3<_T>& x, const vec3<_T>& y) {
    return component_op(x, y, math::min);
  }
  template <typename _T>
  inline vec4<_T> min(const vec4<_T>& x, const vec4<_T>& y) {
    return component_op(x, y, math::min);
  }
  template <typename _T>
  inline vec2<_T> min(const vec2<_T>& x, const _T& y) {
    return component_op(x, y, math::min);
  }
  template <typename _T>
  inline vec3<_T> min(const vec3<_T>& x, const _T& y) {
    return component_op(x, y, math::min);
  }
  template <typename _T>
  inline vec4<_T> min(const vec4<_T>& x, const _T& y) {
    return component_op(x, y, math::min);
  }

  template <typename _T>
  inline _T max(const _T& x, const _T& y) {
    return std::max(x, y);
  }
  template <typename _T>
  inline vec2<_T> max(const vec2<_T>& x, const vec2<_T>& y) {
    return component_op(x, y, math::max);
  }
  template <typename _T>
  inline vec3<_T> max(const vec3<_T>& x, const vec3<_T>& y) {
    return component_op(x, y, math::max);
  }
  template <typename _T>
  inline vec4<_T> max(const vec4<_T>& x, const vec4<_T>& y) {
    return component_op(x, y, math::max);
  }
  template <typename _T>
  inline vec2<_T> max(const vec2<_T>& x, const _T& y) {
    return component_op(x, y, math::max);
  }
  template <typename _T>
  inline vec3<_T> max(const vec3<_T>& x, const _T& y) {
    return component_op(x, y, math::max);
  }
  template <typename _T>
  inline vec4<_T> max(const vec4<_T>& x, const _T& y) {
    return component_op(x, y, math::max);
  }

  template <typename _T>
  inline _T clamp(const _T& x, const _T& minVal, const _T& maxVal) {
    return std::min(std::max(x, minVal), maxVal);
  }
  template <typename _T>
  inline vec2<_T> clamp(const vec2<_T>& x, const vec2<_T>& y,
                        const vec2<_T>& z) {
    return component_op(x, y, z, math::clamp);
  }
  template <typename _T>
  inline vec3<_T> clamp(const vec3<_T>& x, const vec3<_T>& y,
                        const vec3<_T>& z) {
    return component_op(x, y, z, math::clamp);
  }
  template <typename _T>
  inline vec4<_T> clamp(const vec4<_T>& x, const vec4<_T>& y,
                        const vec4<_T>& z) {
    return component_op(x, y, z, math::clamp);
  }
  template <typename _T>
  inline vec2<_T> clamp(const vec2<_T>& x, const _T& y, const _T& z) {
    return component_op(x, y, z, math::clamp);
  }
  template <typename _T>
  inline vec3<_T> clamp(const vec3<_T>& x, const _T& y, const _T& z) {
    return component_op(x, y, z, math::clamp);
  }
  template <typename _T>
  inline vec4<_T> clamp(const vec4<_T>& x, const _T& y, const _T& z) {
    return component_op(x, y, z, math::clamp);
  }

  template <typename _T>
  inline _T mix(const _T& x, const _T& y, const _T& a) {
    return (x * (_T(1) - a) + y * a);
  }
  template <typename _T>
  inline vec2<_T> mix(const vec2<_T>& x, const vec2<_T>& y, const vec2<_T>& a) {
    return component_op(x, y, a, math::mix);
  }
  template <typename _T>
  inline vec3<_T> mix(const vec3<_T>& x, const vec3<_T>& y, const vec3<_T>& a) {
    return component_op(x, y, a, math::mix);
  }
  template <typename _T>
  inline vec4<_T> mix(const vec4<_T>& x, const vec4<_T>& y, const vec4<_T>& a) {
    return component_op(x, y, a, math::mix);
  }
  template <typename _T>
  inline vec2<_T> mix(const vec2<_T>& x, const vec2<_T>& y, const _T& a) {
    return component_op(x, y, a, math::mix);
  }
  template <typename _T>
  inline vec3<_T> mix(const vec3<_T>& x, const vec3<_T>& y, const _T& a) {
    return component_op(x, y, a, math::mix);
  }
  template <typename _T>
  inline vec4<_T> mix(const vec4<_T>& x, const vec4<_T>& y, const _T& a) {
    return component_op(x, y, a, math::mix);
  }

  template <typename _T>
  inline _T step(const _T& edge, const _T& x) {
    return (x < edge) ? _T(0) : _T(1);
  }
  template <typename _T>
  inline vec2<_T> step(const vec2<_T>& edge, const vec2<_T>&& x) {
    return component_op(edge, x, math::mix);
  }
  template <typename _T>
  inline vec3<_T> step(const vec3<_T>& edge, const vec3<_T>&& x) {
    return component_op(edge, x, math::mix);
  }
  template <typename _T>
  inline vec4<_T> step(const vec4<_T>& edge, const vec4<_T>&& x) {
    return component_op(edge, x, math::mix);
  }
  template <typename _T>
  inline vec2<_T> step(const _T& edge, const vec2<_T>&& x) {
    return component_op(edge, x, math::mix);
  }
  template <typename _T>
  inline vec3<_T> step(const _T& edge, const vec3<_T>&& x) {
    return component_op(edge, x, math::mix);
  }
  template <typename _T>
  inline vec4<_T> step(const _T& edge, const vec4<_T>&& x) {
    return component_op(edge, x, math::mix);
  }

  template <typename _T>
  _T smoothstep(const _T& edge0, const _T& edge1, const _T& x) {
    _T t = std::min(std::max((x - edge0) / (edge1 - edge0), 0.0), 1.0);
    return t * t * (_T(3) - _T(2) * t);
  }
  template <typename _T>
  inline vec2<_T> smoothstep(const vec2<_T>& edge0, const vec2<_T>& edge1,
                             const vec2<_T>&& x) {
    return component_op(edge0, edge1, x, math::smoothstep);
  }
  template <typename _T>
  inline vec3<_T> smoothstep(const vec3<_T>& edge0, const vec3<_T>& edge1,
                             const vec3<_T>&& x) {
    return component_op(edge0, edge1, x, math::smoothstep);
  }
  template <typename _T>
  inline vec4<_T> smoothstep(const vec4<_T>& edge0, const vec4<_T>& edge1,
                             const vec4<_T>&& x) {
    return component_op(edge0, edge1, x, math::smoothstep);
  }
  template <typename _T>
  inline vec2<_T> smoothstep(const _T& edge0, const _T& edge1,
                             const vec2<_T>&& x) {
    return component_op(edge0, edge1, x, math::smoothstep);
  }
  template <typename _T>
  inline vec3<_T> smoothstep(const _T& edge0, const _T& edge1,
                             const vec3<_T>&& x) {
    return component_op(edge0, edge1, x, math::smoothstep);
  }
  template <typename _T>
  inline vec4<_T> smoothstep(const _T& edge0, const _T& edge1,
                             const vec4<_T>&& x) {
    return component_op(edge0, edge1, x, math::smoothstep);
  }
}  // namespace math
}  // namespace specula

#endif  // SPECULA_MATH_COMMON_HPP_
