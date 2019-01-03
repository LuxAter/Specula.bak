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
  inline Vec2<_T> pow(const Vec2<_T>& x, const Vec2<_T>& y) {
    return Vec2<_T>{std::pow(x.x, y.x), std::pow(x.y, y.y)};
  }
  template <typename _T>
  inline Vec3<_T> pow(const Vec3<_T>& x, const Vec3<_T>& y) {
    return Vec3<_T>{std::pow(x.x, y.x), std::pow(x.y, y.y), std::pow(x.z, y.z)};
  }
  template <typename _T>
  inline Vec4<_T> pow(const Vec4<_T>& x, const Vec4<_T>& y) {
    return Vec4<_T>{std::pow(x.x, y.x), std::pow(x.y, y.y), std::pow(x.z, y.z),
                    std::pow(x.w, y.w)};
  }

  template <typename _T>
  inline _T exp(const _T& x) {
    return std::exp(x);
  }
  template <typename _T>
  inline Vec2<_T> exp(const Vec2<_T>& x) {
    return Vec2<_T>{std::exp(x.x), std::exp(x.y)};
  }
  template <typename _T>
  inline Vec3<_T> exp(const Vec3<_T>& x) {
    return Vec3<_T>{std::exp(x.x), std::exp(x.y), std::exp(x.z)};
  }
  template <typename _T>
  inline Vec4<_T> exp(const Vec4<_T>& x) {
    return Vec4<_T>{std::exp(x.x), std::exp(x.y), std::exp(x.z), std::exp(x.w)};
  }

  template <typename _T>
  inline _T log(const _T& x) {
    return std::log(x);
  }
  template <typename _T>
  inline Vec2<_T> log(const Vec2<_T>& x) {
    return Vec2<_T>{std::log(x.x), std::log(x.y)};
  }
  template <typename _T>
  inline Vec3<_T> log(const Vec3<_T>& x) {
    return Vec3<_T>{std::log(x.x), std::log(x.y), std::log(x.z)};
  }
  template <typename _T>
  inline Vec4<_T> log(const Vec4<_T>& x) {
    return Vec4<_T>{std::log(x.x), std::log(x.y), std::log(x.z), std::log(x.w)};
  }

  template <typename _T>
  inline _T exp2(const _T& x) {
    return std::exp2(x);
  }
  template <typename _T>
  inline Vec2<_T> exp2(const Vec2<_T>& x) {
    return Vec2<_T>{std::exp2(x.x), std::exp2(x.y)};
  }
  template <typename _T>
  inline Vec3<_T> exp2(const Vec3<_T>& x) {
    return Vec3<_T>{std::exp2(x.x), std::exp2(x.y), std::exp2(x.z)};
  }
  template <typename _T>
  inline Vec4<_T> exp2(const Vec4<_T>& x) {
    return Vec4<_T>{std::exp2(x.x), std::exp2(x.y), std::exp2(x.z),
                    std::exp2(x.w)};
  }

  template <typename _T>
  inline _T log2(const _T& x) {
    return std::log2(x);
  }
  template <typename _T>
  inline Vec2<_T> log2(const Vec2<_T>& x) {
    return Vec2<_T>{std::log2(x.x), std::log2(x.y)};
  }
  template <typename _T>
  inline Vec3<_T> log2(const Vec3<_T>& x) {
    return Vec3<_T>{std::log2(x.x), std::log2(x.y), std::log2(x.z)};
  }
  template <typename _T>
  inline Vec4<_T> log2(const Vec4<_T>& x) {
    return Vec4<_T>{std::log2(x.x), std::log2(x.y), std::log2(x.z),
                    std::log2(x.w)};
  }

  template <typename _T>
  inline _T sqrt(const _T& x) {
    return std::sqrt(x);
  }
  template <typename _T>
  inline Vec2<_T> sqrt(const Vec2<_T>& x) {
    return Vec2<_T>{std::sqrt(x.x), std::sqrt(x.y)};
  }
  template <typename _T>
  inline Vec3<_T> sqrt(const Vec3<_T>& x) {
    return Vec3<_T>{std::sqrt(x.x), std::sqrt(x.y), std::sqrt(x.z)};
  }
  template <typename _T>
  inline Vec4<_T> sqrt(const Vec4<_T>& x) {
    return Vec4<_T>{std::sqrt(x.x), std::sqrt(x.y), std::sqrt(x.z),
                    std::sqrt(x.w)};
  }
}  // namespace math
}  // namespace specula

#endif  // SPECULA_MATH_EXPO_HPP_
