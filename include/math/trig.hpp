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
  template <typename _T>
  inline Vec2<_T> radians(const Vec2<_T>& degrees) {
    return Vec2<_T>{(M_PI * degrees.x) / _T(180), (M_PI * degrees.y)._T(180)};
  }
  template <typename _T>
  inline Vec3<_T> radians(const Vec3<_T>& degrees) {
    return Vec3<_T>{(M_PI * degrees.x) / _T(180), (M_PI * degrees.y) / _T(180),
                    (M_PI * degrees.z) / _T(180)};
  }
  template <typename _T>
  inline Vec4<_T> radians(const Vec4<_T>& degrees) {
    return Vec4<_T>{(M_PI * degrees.x) / _T(180), (M_PI * degrees.y) / _T(180),
                    (M_PI * degrees.z) / _T(180), (M_PI * degrees.w) / _T(180)};
  }

  template <typename _T>
  inline _T degrees(const _T& radians) {
    return (_T(180) * radians) / M_PI;
  }
  template <typename _T>
  inline Vec2<_T> degrees(const Vec2<_T>& radians) {
    return Vec2<_T>{(_T(180) * radians.x) / M_PI, (_T(180) * radians.y) / M_PI};
  }
  template <typename _T>
  inline Vec3<_T> degrees(const Vec3<_T>& radians) {
    return Vec2<_T>{(_T(180) * radians.x) / M_PI, (_T(180) * radians.y) / M_PI,
                    (_T(180) * radians.z) / M_PI};
  }
  template <typename _T>
  inline Vec4<_T> degrees(const Vec4<_T>& radians) {
    return Vec2<_T>{(_T(180) * radians.x) / M_PI, (_T(180) * radians.y) / M_PI,
                    (_T(180) * radians.z) / M_PI, (_T(180) * radians.w) / M_PI};
  }

  template <typename _T>
  inline _T sin(const _T& angle) {
    return std::sin(angle);
  }
  template <typename _T>
  inline Vec2<_T> sin(const Vec2<_T>& angle) {
    return Vec2<_T>{std::sin(angle.x), std::sin(angle.y)};
  }
  template <typename _T>
  inline Vec3<_T> sin(const Vec3<_T>& angle) {
    return Vec3<_T>{std::sin(angle.x), std::sin(angle.y), std::sin(angle.z)};
  }
  template <typename _T>
  inline Vec4<_T> sin(const Vec4<_T>& angle) {
    return Vec4<_T>{std::sin(angle.x), std::sin(angle.y), std::sin(angle.z),
                    std::sin(angle.w)};
  }

  template <typename _T>
  inline _T cos(const _T& angle) {
    return std::cos(angle);
  }
  template <typename _T>
  inline Vec2<_T> cos(const Vec2<_T>& angle) {
    return Vec2<_T>{std::cos(angle.x), std::cos(angle.y)};
  }
  template <typename _T>
  inline Vec3<_T> cos(const Vec3<_T>& angle) {
    return Vec3<_T>{std::cos(angle.x), std::cos(angle.y), std::cos(angle.z)};
  }
  template <typename _T>
  inline Vec4<_T> cos(const Vec4<_T>& angle) {
    return Vec4<_T>{std::cos(angle.x), std::cos(angle.y), std::cos(angle.z),
                    std::cos(angle.w)};
  }

  template <typename _T>
  inline _T tan(const _T& angle) {
    return std::tan(angle);
  }
  template <typename _T>
  inline Vec2<_T> tan(const Vec2<_T>& angle) {
    return Vec2<_T>{std::tan(angle.x), std::tan(angle.y)};
  }
  template <typename _T>
  inline Vec3<_T> tan(const Vec3<_T>& angle) {
    return Vec3<_T>{std::tan(angle.x), std::tan(angle.y), std::tan(angle.z)};
  }
  template <typename _T>
  inline Vec4<_T> tan(const Vec4<_T>& angle) {
    return Vec4<_T>{std::tan(angle.x), std::tan(angle.y), std::tan(angle.z),
                    std::tan(angle.w)};
  }

  template <typename _T>
  inline _T asin(const _T& x) {
    return std::asin(x);
  }
  template <typename _T>
  inline Vec2<_T> asin(const Vec2<_T>& x) {
    return Vec2<_T>{std::asin(x.x), std::asin(x.y)};
  }
  template <typename _T>
  inline Vec3<_T> asin(const Vec3<_T>& x) {
    return Vec3<_T>{std::asin(x.x), std::asin(x.y), std::asin(x.z)};
  }
  template <typename _T>
  inline Vec4<_T> asin(const Vec4<_T>& x) {
    return Vec4<_T>{std::asin(x.x), std::asin(x.y), std::asin(x.z),
                    std::asin(x.w)};
  }

  template <typename _T>
  inline _T acos(const _T& x) {
    return std::acos(x);
  }
  template <typename _T>
  inline Vec2<_T> acos(const Vec2<_T>& x) {
    return Vec2<_T>{std::acos(x.x), std::acos(x.y)};
  }
  template <typename _T>
  inline Vec3<_T> acos(const Vec3<_T>& x) {
    return Vec3<_T>{std::acos(x.x), std::acos(x.y), std::acos(x.z)};
  }
  template <typename _T>
  inline Vec4<_T> acos(const Vec4<_T>& x) {
    return Vec4<_T>{std::acos(x.x), std::acos(x.y), std::acos(x.z),
                    std::acos(x.w)};
  }

  template <typename _T>
  inline _T atan(const _T& y_over_x) {
    return std::atan(y_over_x);
  }
  template <typename _T>
  inline Vec2<_T> atan(const Vec2<_T>& y_over_x) {
    return Vec2<_T>{std::atan(y_over_x.x), std::atan(y_over_x.y)};
  }
  template <typename _T>
  inline Vec3<_T> atan(const Vec3<_T>& y_over_x) {
    return Vec3<_T>{std::atan(y_over_x.x), std::atan(y_over_x.y),
                    std::atan(y_over_x.z)};
  }
  template <typename _T>
  inline Vec4<_T> atan(const Vec4<_T>& y_over_x) {
    return Vec4<_T>{std::atan(y_over_x.x), std::atan(y_over_x.y),
                    std::atan(y_over_x.z), std::atan(y_over_x.w)};
  }

  template <typename _T>
  inline _T atan(const _T& x, const _T& y) {
    return std::atan2(x, y);
  }
  template <typename _T>
  inline Vec2<_T> atan(const Vec2<_T>& x, const Vec2<_T>& y) {
    return Vec2<_T>{std::atan2(x.x, y.x), std::atan2(x.y, y.y)};
  }
  template <typename _T>
  inline Vec3<_T> atan(const Vec3<_T>& x, const Vec3<_T>& y) {
    return Vec3<_T>{std::atan2(x.x, y.x), std::atan2(x.y, y.y),
                    std::atan2(x.z, y.z)};
  }
  template <typename _T>
  inline Vec4<_T> atan(const Vec4<_T>& x, const Vec4<_T>& y) {
    return Vec4<_T>{std::atan2(x.x, y.x), std::atan2(x.y, y.y),
                    std::atan2(x.z, y.z), std::atan2(x.w, y.w)};
  }
}  // namespace math
}  // namespace specula

#endif  // SPECULA_MATH_TRIG_HPP_
