#ifndef SPECULA_MATH_TRIG_HPP_
#define SPECULA_MATH_TRIG_HPP_

#include <cmath>

#include "vector.hpp"

namespace specula {
namespace math {

  template <typename _T>
  inline _T radians(const _T& degrees) {
    return (M_PI * degrees) / _T(180);
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> radians(const vec<_T, _N>& degrees) {
    return component_op(degrees, math::radians);
  }

  template <typename _T>
  inline _T degrees(const _T& radians) {
    return (_T(180) * radians) / M_PI;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> degrees(const vec<_T, _N>& radians) {
    return component_op(radians, math::degrees);
  }

  template <typename _T>
  inline _T sin(const _T& angle) {
    return std::sin(angle);
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> sin(const vec<_T, _N>& angle) {
    return component_op(angle, math::sin);
  }

  template <typename _T>
  inline _T cos(const _T& angle) {
    return std::cos(angle);
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> cos(const vec<_T, _N>& angle) {
    return component_op(angle, math::cos);
  }

  template <typename _T>
  inline _T tan(const _T& angle) {
    return std::tan(angle);
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> tan(const vec<_T, _N>& angle) {
    return component_op(angle, math::tan);
  }

  template <typename _T>
  inline _T asin(const _T& x) {
    return std::asin(x);
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> asin(const vec<_T, _N>& x) {
    return component_op(x, math::asin);
  }

  template <typename _T>
  inline _T acos(const _T& x) {
    return std::acos(x);
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> acos(const vec<_T, _N>& x) {
    return component_op(x, math::acos);
  }

  template <typename _T>
  inline _T atan(const _T& y_over_x) {
    return std::atan(y_over_x);
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> atan(const vec<_T, _N>& y_over_x) {
    return component_op(y_over_x, math::atan);
  }

  template <typename _T>
  inline _T atan(const _T& x, const _T& y) {
    return std::atan2(x, y);
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> atan(const vec<_T, _N>& x, const vec<_T, _N>& y) {
    return component_op(x, y, math::atan);
  }
}  // namespace math
}  // namespace specula

#endif  // SPECULA_MATH_TRIG_HPP_
