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
  inline Vec2<_T> abs(const Vec2<_T>& x) {
    return Vec2<_T>{std::abs(x.x), std::abs(x.y)};
  }
  template <typename _T>
  inline Vec3<_T> abs(const Vec3<_T>& x) {
    return Vec3<_T>{std::abs(x.x), std::abs(x.y), std::abs(x.z)};
  }
  template <typename _T>
  inline Vec4<_T> abs(const Vec4<_T>& x) {
    return Vec4<_T>{std::abs(x.x), std::abs(x.y), std::abs(x.z), std::abs(x.w)};
  }

  template <typename _T>
  inline _T sign(const _T& x) {
    return (_T(0) < x) - (x < _T(0));
  }
  template <typename _T>
  inline Vec2<_T> sign(const Vec2<_T>& x) {
    return Vec2<_T>{(_T(0) < x.x) - (x.x < _T(0)),
                    (_T(0) < x.y) - (x.y < _T(0))};
  }
  template <typename _T>
  inline Vec3<_T> sign(const Vec3<_T>& x) {
    return Vec2<_T>{(_T(0) < x.x) - (x.x < _T(0)),
                    (_T(0) < x.y) - (x.y < _T(0)),
                    (_T(0) < x.z) - (x.z < _T(0))};
  }
  template <typename _T>
  inline Vec4<_T> sign(const Vec4<_T>& x) {
    return Vec2<_T>{
        (_T(0) < x.x) - (x.x < _T(0)), (_T(0) < x.y) - (x.y < _T(0)),
        (_T(0) < x.z) - (x.z < _T(0)), (_T(0) < x.w) - (x.w < _T(0))};
  }

  template <typename _T>
  inline _T floor(const _T& x) {
    return std::floor(x);
  }
  template <typename _T>
  inline Vec2<_T> floor(const Vec2<_T>& x) {
    return Vec2<_T>{std::floor(x.x), std::floor(x.y)};
  }
  template <typename _T>
  inline Vec3<_T> floor(const Vec3<_T>& x) {
    return Vec3<_T>{std::floor(x.x), std::floor(x.y), std::floor(x.z)};
  }
  template <typename _T>
  inline Vec4<_T> floor(const Vec4<_T>& x) {
    return Vec4<_T>{std::floor(x.x), std::floor(x.y), std::floor(x.z),
                    std::floor(x.w)};
  }

  template <typename _T>
  inline _T ceil(const _T& x) {
    return std::ceil(x);
  }
  template <typename _T>
  inline Vec2<_T> ceil(const Vec2<_T>& x) {
    return Vec2<_T>{std::ceil(x.x), std::ceil(x.y)};
  }
  template <typename _T>
  inline Vec3<_T> ceil(const Vec3<_T>& x) {
    return Vec3<_T>{std::ceil(x.x), std::ceil(x.y), std::ceil(x.z)};
  }
  template <typename _T>
  inline Vec4<_T> ceil(const Vec4<_T>& x) {
    return Vec4<_T>{std::ceil(x.x), std::ceil(x.y), std::ceil(x.z),
                    std::ceil(x.w)};
  }

  template <typename _T>
  inline _T fract(const _T& x) {
    return (x - std::floor(x));
  }
  template <typename _T>
  inline Vec2<_T> fract(const Vec2<_T>& x) {
    return Vec2<_T>{x.x - std::floor(x.x), x.y - std::floor(x.y)};
  }
  template <typename _T>
  inline Vec3<_T> fract(const Vec3<_T>& x) {
    return Vec2<_T>{x.x - std::floor(x.x), x.y - std::floor(x.y),
                    x.z - std::floor(x.z)};
  }
  template <typename _T>
  inline Vec4<_T> fract(const Vec4<_T>& x) {
    return Vec2<_T>{x.x - std::floor(x.x), x.y - std::floor(x.y),
                    x.z - std::floor(x.z), x.w - std::floor(x.w)};
  }

  template <typename _T>
  inline _T mod(const _T& x, const _T& y) {
    return std::fmod(x, y);
  }
  template <typename _T>
  inline Vec2<_T> mod(const Vec2<_T>& x, const Vec2<_T>& y) {
    return Vec2<_T>{std::fmod(x.x, y.x), std::fmod(x.y, y.y)};
  }
  template <typename _T>
  inline Vec3<_T> mod(const Vec3<_T>& x, const Vec3<_T>& y) {
    return Vec3<_T>{std::fmod(x.x, y.x), std::fmod(x.y, y.y),
                    std::fmod(x.z, y.z)};
  }
  template <typename _T>
  inline Vec4<_T> mod(const Vec4<_T>& x, const Vec4<_T>& y) {
    return Vec4<_T>{std::fmod(x.x, y.x), std::fmod(x.y, y.y),
                    std::fmod(x.z, y.z), std::fmod(x.w, y.w)};
  }

  template <typename _T>
  inline _T min(const _T& x, const _T& y) {
    return std::min(x, y);
  }
  template <typename _T>
  inline Vec2<_T> min(const Vec2<_T>& x, const Vec2<_T>& y) {
    return Vec2<_T>{std::min(x.x, y.x), std::min(x.y, y.y)};
  }
  template <typename _T>
  inline Vec3<_T> min(const Vec3<_T>& x, const Vec3<_T>& y) {
    return Vec3<_T>{std::min(x.x, y.x), std::min(x.y, y.y), std::min(x.z, y.z)};
  }
  template <typename _T>
  inline Vec4<_T> min(const Vec4<_T>& x, const Vec4<_T>& y) {
    return Vec4<_T>{std::min(x.x, y.x), std::min(x.y, y.y), std::min(x.z, y.z),
                    std::min(x.w, y.w)};
  }

  template <typename _T>
  inline Vec2<_T> min(const Vec2<_T>& x, const _T& y) {
    return Vec2<_T>{std::min(x.x, y), std::min(x.y, y)};
  }
  template <typename _T>
  inline Vec3<_T> min(const Vec3<_T>& x, const _T& y) {
    return Vec3<_T>{std::min(x.x, y), std::min(x.y, y), std::min(x.z, y)};
  }
  template <typename _T>
  inline Vec4<_T> min(const Vec4<_T>& x, const _T& y) {
    return Vec4<_T>{std::min(x.x, y), std::min(x.y, y), std::min(x.z, y),
                    std::min(x.w, y)};
  }

  template <typename _T>
  inline _T max(const _T& x, const _T& y) {
    return std::max(x, y);
  }
  template <typename _T>
  inline Vec2<_T> max(const Vec2<_T>& x, const Vec2<_T>& y) {
    return Vec2<_T>{std::max(x.x, y.x), std::max(x.y, y.y)};
  }
  template <typename _T>
  inline Vec3<_T> max(const Vec3<_T>& x, const Vec3<_T>& y) {
    return Vec3<_T>{std::max(x.x, y.x), std::max(x.y, y.y), std::max(x.z, y.z)};
  }
  template <typename _T>
  inline Vec4<_T> max(const Vec4<_T>& x, const Vec4<_T>& y) {
    return Vec4<_T>{std::max(x.x, y.x), std::max(x.y, y.y), std::max(x.z, y.z),
                    std::max(x.w, y.w)};
  }

  template <typename _T>
  inline Vec2<_T> max(const Vec2<_T>& x, const _T& y) {
    return Vec2<_T>{std::max(x.x, y), std::max(x.y, y)};
  }
  template <typename _T>
  inline Vec3<_T> max(const Vec3<_T>& x, const _T& y) {
    return Vec3<_T>{std::max(x.x, y), std::max(x.y, y), std::max(x.z, y)};
  }
  template <typename _T>
  inline Vec4<_T> max(const Vec4<_T>& x, const _T& y) {
    return Vec4<_T>{std::max(x.x, y), std::max(x.y, y), std::max(x.z, y),
                    std::max(x.w, y)};
  }

  template <typename _T>
  inline _T clamp(const _T& x, const _T& minVal, const _T& maxVal) {
    return std::min(std::max(x, minVal), maxVal);
  }
  template <typename _T>
  inline Vec2<_T> clamp(const Vec2<_T>& x, const Vec2<_T>& minVal,
                 const Vec2<_T>& maxVal) {
    return Vec2<_T>{std::min(std::max(x.x, minVal.x), maxVal.x),
                    std::min(std::max(x.y, minVal.y), maxVal.y)};
  }
  template <typename _T>
  inline Vec3<_T> clamp(const Vec3<_T>& x, const Vec3<_T>& minVal,
                 const Vec3<_T>& maxVal) {
    return Vec2<_T>{std::min(std::max(x.x, minVal.x), maxVal.x),
                    std::min(std::max(x.y, minVal.y), maxVal.y),
                    std::min(std::max(x.z, minVal.z), maxVal.z)};
  }
  template <typename _T>
  inline Vec4<_T> clamp(const Vec4<_T>& x, const Vec4<_T>& minVal,
                 const Vec3<_T>& maxVal) {
    return Vec2<_T>{std::min(std::max(x.x, minVal.x), maxVal.x),
                    std::min(std::max(x.y, minVal.y), maxVal.y),
                    std::min(std::max(x.z, minVal.z), maxVal.z),
                    std::min(std::max(x.w, minVal.w), maxVal.w)};
  }

  template <typename _T>
  inline Vec2<_T> clamp(const Vec2<_T>& x, const _T& minVal, const _T& maxVal) {
    return Vec2<_T>{std::min(std::max(x.x, minVal), maxVal),
                    std::min(std::max(x.y, minVal), maxVal)};
  }
  template <typename _T>
  inline Vec3<_T> clamp(const Vec3<_T>& x, const _T& minVal, const _T& maxVal) {
    return Vec2<_T>{std::min(std::max(x.x, minVal), maxVal),
                    std::min(std::max(x.y, minVal), maxVal),
                    std::min(std::max(x.z, minVal), maxVal)};
  }
  template <typename _T>
  inline Vec4<_T> clamp(const Vec4<_T>& x, const _T& minVal, const _T& maxVal) {
    return Vec2<_T>{std::min(std::max(x.x, minVal), maxVal),
                    std::min(std::max(x.y, minVal), maxVal),
                    std::min(std::max(x.z, minVal), maxVal),
                    std::min(std::max(x.w, minVal), maxVal)};
  }

  template <typename _T>
  inline _T mix(const _T& x, const _T& y, const _T& a) {
    return (x * (_T(1) - a) + y * a);
  }
  template <typename _T>
  inline Vec2<_T> mix(const Vec2<_T>& x, const Vec2<_T>& y, const Vec2<_T>& a) {
    return Vec2<_T>{x.x * (_T(1) - a.x) + y.x * a.x,
                    x.y * (_T(1) - a.y) + y.y * a.y};
  }
  template <typename _T>
  inline Vec3<_T> mix(const Vec3<_T>& x, const Vec3<_T>& y, const Vec2<_T>& a) {
    return Vec3<_T>{x.x * (_T(1) - a.x) + y.x * a.x,
                    x.y * (_T(1) - a.y) + y.y * a.y,
                    x.z * (_T(1) - a.z) + y.z * a.z};
  }
  template <typename _T>
  inline Vec4<_T> mix(const Vec4<_T>& x, const Vec4<_T>& y, const Vec2<_T>& a) {
    return Vec4<_T>{
        x.x * (_T(1) - a.x) + y.x * a.x, x.y * (_T(1) - a.y) + y.y * a.y,
        x.z * (_T(1) - a.z) + y.z * a.z, x.w * (_T(1) - a.w) + y.w * a.w};
  }

  template <typename _T>
  inline Vec2<_T> mix(const Vec2<_T>& x, const Vec2<_T>& y, const _T& a) {
    return Vec2<_T>{x.x * (_T(1) - a) + y.x * a, x.y * (_T(1) - a) + y.y * a};
  }
  template <typename _T>
  inline Vec3<_T> mix(const Vec3<_T>& x, const Vec3<_T>& y, const _T& a) {
    return Vec3<_T>{x.x * (_T(1) - a) + y.x * a, x.y * (_T(1) - a) + y.y * a,
                    x.z * (_T(1) - a) + y.z * a};
  }
  template <typename _T>
  inline Vec4<_T> mix(const Vec4<_T>& x, const Vec4<_T>& y, const _T& a) {
    return Vec4<_T>{x.x * (_T(1) - a) + y.x * a, x.y * (_T(1) - a) + y.y * a,
                    x.z * (_T(1) - a) + y.z * a, x.w * (_T(1) - a) + y.w * a};
  }

  template <typename _T>
  inline _T step(const _T& edge, const _T& x) {
    return (x < edge) ? _T(0) : _T(1);
  }
  template <typename _T>
  inline Vec2<_T> step(const Vec2<_T>& edge, const Vec2<_T>& x) {
    return Vec2<_T>{(x.x < edge.x) ? _T(0) : _T(1),
                    (x.y < edge.y) ? _T(0) : _T(1)};
  }
  template <typename _T>
  inline Vec3<_T> step(const Vec3<_T>& edge, const Vec3<_T>& x) {
    return Vec3<_T>{(x.x < edge.x) ? _T(0) : _T(1),
                    (x.y < edge.y) ? _T(0) : _T(1),
                    (x.z < edge.z) ? _T(0) : _T(1)};
  }
  template <typename _T>
  inline Vec4<_T> step(const Vec4<_T>& edge, const Vec4<_T>& x) {
    return Vec4<_T>{
        (x.x < edge.x) ? _T(0) : _T(1), (x.y < edge.y) ? _T(0) : _T(1),
        (x.z < edge.z) ? _T(0) : _T(1), (x.w < edge.w) ? _T(0) : _T(1)};
  }

  template <typename _T>
  inline Vec2<_T> step(const _T& edge, const Vec2<_T>& x) {
    return Vec2<_T>{(x.x < edge) ? _T(0) : _T(1), (x.y < edge) ? _T(0) : _T(1)};
  }
  template <typename _T>
  inline Vec3<_T> step(const _T& edge, const Vec3<_T>& x) {
    return Vec3<_T>{(x.x < edge) ? _T(0) : _T(1), (x.y < edge) ? _T(0) : _T(1),
                    (x.z < edge) ? _T(0) : _T(1)};
  }
  template <typename _T>
  inline Vec4<_T> step(const _T& edge, const Vec4<_T>& x) {
    return Vec4<_T>{(x.x < edge) ? _T(0) : _T(1), (x.y < edge) ? _T(0) : _T(1),
                    (x.z < edge) ? _T(0) : _T(1), (x.w < edge) ? _T(0) : _T(1)};
  }

  template <typename _T>
  _T smoothstep(const _T& edge0, const _T& edge1, const _T& x) {
    _T t = std::min(std::max((x - edge0) / (edge1 - edge0), 0.0), 1.0);
    return t * t * (_T(3) - _T(2) * t);
  }
  template <typename _T>
  Vec2<_T> smoothstep(const Vec2<_T>& edge0, const Vec2<_T>& edge1,
                      const Vec2<_T>& x) {
    Vec2<_T> t{
        std::min(std::max((x.x - edge0.x) / (edge1.x - edge0.x), 0.0), 1.0),
        std::min(std::max((x.y - edge0.y) / (edge1.y - edge0.y), 0.0), 1.0)};
    return Vec2<_T>{t.x * t.x * (_T(3) - _T(2) * t.x),
                    t.y * t.y * (_T(3) - _T(2) * t.y)};
  }
  template <typename _T>
  Vec3<_T> smoothstep(const Vec3<_T>& edge0, const Vec3<_T>& edge1,
                      const Vec3<_T>& x) {
    Vec3<_T> t{
        std::min(std::max((x.x - edge0.x) / (edge1.x - edge0.x), 0.0), 1.0),
        std::min(std::max((x.y - edge0.y) / (edge1.y - edge0.y), 0.0), 1.0),
        std::min(std::max((x.z - edge0.z) / (edge1.z - edge0.z), 0.0), 1.0),
    };
    return Vec3<_T>{
        t.x * t.x * (_T(3) - _T(2) * t.x),
        t.y * t.y * (_T(3) - _T(2) * t.y),
        t.z * t.z * (_T(3) - _T(2) * t.z),
    };
  }
  template <typename _T>
  Vec4<_T> smoothstep(const Vec4<_T>& edge0, const Vec4<_T>& edge1,
                      const Vec4<_T>& x) {
    Vec4<_T> t{
        std::min(std::max((x.x - edge0.x) / (edge1.x - edge0.x), 0.0), 1.0),
        std::min(std::max((x.y - edge0.y) / (edge1.y - edge0.y), 0.0), 1.0),
        std::min(std::max((x.z - edge0.z) / (edge1.z - edge0.z), 0.0), 1.0),
        std::min(std::max((x.w - edge0.w) / (edge1.w - edge0.w), 0.0), 1.0),
    };
    return Vec4<_T>{
        t.x * t.x * (_T(3) - _T(2) * t.x),
        t.y * t.y * (_T(3) - _T(2) * t.y),
        t.z * t.z * (_T(3) - _T(2) * t.z),
        t.w * t.w * (_T(3) - _T(2) * t.w),
    };
  }

  template <typename _T>
  Vec2<_T> smoothstep(const _T& edge0, const _T& edge1, const Vec2<_T>& x) {
    Vec2<_T> t{std::min(std::max((x.x - edge0) / (edge1 - edge0), 0.0), 1.0),
               std::min(std::max((x.y - edge0) / (edge1 - edge0), 0.0), 1.0)};
    return Vec2<_T>{t.x * t.x * (_T(3) - _T(2) * t.x),
                    t.y * t.y * (_T(3) - _T(2) * t.y)};
  }
  template <typename _T>
  Vec3<_T> smoothstep(const _T& edge0, const _T& edge1, const Vec3<_T>& x) {
    Vec3<_T> t{
        std::min(std::max((x.x - edge0) / (edge1 - edge0), 0.0), 1.0),
        std::min(std::max((x.y - edge0) / (edge1 - edge0), 0.0), 1.0),
        std::min(std::max((x.z - edge0) / (edge1 - edge0), 0.0), 1.0),
    };
    return Vec3<_T>{
        t.x * t.x * (_T(3) - _T(2) * t.x),
        t.y * t.y * (_T(3) - _T(2) * t.y),
        t.z * t.z * (_T(3) - _T(2) * t.z),
    };
  }
  template <typename _T>
  Vec4<_T> smoothstep(const _T& edge0, const _T& edge1, const Vec4<_T>& x) {
    Vec4<_T> t{
        std::min(std::max((x.x - edge0) / (edge1 - edge0), 0.0), 1.0),
        std::min(std::max((x.y - edge0) / (edge1 - edge0), 0.0), 1.0),
        std::min(std::max((x.z - edge0) / (edge1 - edge0), 0.0), 1.0),
        std::min(std::max((x.w - edge0) / (edge1 - edge0), 0.0), 1.0),
    };
    return Vec4<_T>{
        t.x * t.x * (_T(3) - _T(2) * t.x),
        t.y * t.y * (_T(3) - _T(2) * t.y),
        t.z * t.z * (_T(3) - _T(2) * t.z),
        t.w * t.w * (_T(3) - _T(2) * t.w),
    };
  }
}  // namespace math
}  // namespace specula

#endif  // SPECULA_MATH_COMMON_HPP_
