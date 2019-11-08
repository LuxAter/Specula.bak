#ifndef SPECULA_MATH_GEOMETRIC_HPP_
#define SPECULA_MATH_GEOMETRIC_HPP_

#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

namespace specula {
template <typename _T>
inline vec3<_T> cross(const vec3<_T> &x, const vec3<_T> &y) {
  return vec3<_T>{x.y * y.z - y.y * x.z, x.z * y.x - y.z * x.x,
                  x.x * y.y - y.x * x.y};
}
template <typename _T> inline _T length(const _T &x) { return x; }
template <typename _T> inline _T length(const vec2<_T> &x) {
  return std::sqrt(x.x * x.x + x.y * x.y);
}
template <typename _T> inline _T length(const vec3<_T> &x) {
  return std::sqrt(x.x * x.x + x.y * x.y + x.z * x.z);
}
template <typename _T> inline _T length(const vec4<_T> &x) {
  return std::sqrt(x.x * x.x + x.y * x.y + x.z * x.z + x.w * x.w);
}

template <typename _T> inline _T distance(const _T &x, const _T &y) {
  return y - x;
}
template <typename _T>
inline _T distance(const vec2<_T> &x, const vec2<_T> &y) {
  const vec2<_T> diff = y - x;
  return std::sqrt(diff.x * diff.x + diff.y * diff.y);
}
template <typename _T>
inline _T distance(const vec3<_T> &x, const vec3<_T> &y) {
  const vec3<_T> diff = y - x;
  return std::sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
}
template <typename _T>
inline _T distance(const vec4<_T> &x, const vec4<_T> &y) {
  const vec4<_T> diff = y - x;
  return std::sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z +
                   diff.w * diff.w);
}

template <typename _T> inline _T dot(const _T &x, const _T &y) { return x * y; }
template <typename _T> inline _T dot(const vec2<_T> &x, const vec2<_T> &y) {
  return x.x * y.x + x.y * y.y;
}
template <typename _T> inline _T dot(const vec3<_T> &x, const vec3<_T> &y) {
  return x.x * y.x + x.y * y.y + x.z * y.z;
}
template <typename _T> inline _T dot(const vec4<_T> &x, const vec4<_T> &y) {
  return x.x * y.x + x.y * y.y + x.z * y.z + x.w * y.w;
}

template <typename _T> inline _T normalize(const _T &v) { return v / v; }
template <typename _T> inline vec2<_T> normalize(const vec2<_T> &v) {
  return v / std::sqrt(v.x * v.x + v.y * v.y);
}
template <typename _T> inline vec3<_T> normalize(const vec3<_T> &v) {
  return v / std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
template <typename _T> inline vec3<_T> normalize(const vec4<_T> &v) {
  return v / std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

template <typename _T>
inline _T faceforward(const _T &N, const _T &I, const _T &Nref) {
  return dot(Nref, I) < static_cast<_T>(0) ? N : -N;
}

template <typename _T> inline _T reflect(const _T &I, const _T &N) {
  return I - N * dot(N, I) * static_cast<_T>(2);
}

template <typename _T>
inline _T refract(const _T &I, const _T &N, const _T &eta) {
  _T const dot_value(dot(N, I));
  _T const k(static_cast<_T>(1) -
             eta * eta * (static_cast<_T>(1) - dot_value * dot_value));
  return (k >= static_cast<_T>(0))
             ? (eta * I - (eta * dot_value + std::sqrt(k)) * N)
             : _T(0);
}
template <typename _T>
inline vec2<_T> refract(const vec2<_T> &I, const vec2<_T> &N, const _T &eta) {
  _T const dot_value(dot(N, I));
  _T const k(static_cast<_T>(1) -
             eta * eta * (static_cast<_T>(1) - dot_value * dot_value));
  return (k >= static_cast<_T>(0))
             ? (eta * I - (eta * dot_value + std::sqrt(k)) * N)
             : vec2<_T>(0);
}
template <typename _T>
inline vec3<_T> refract(const vec3<_T> &I, const vec3<_T> &N, const _T &eta) {
  _T const dot_value(dot(N, I));
  _T const k(static_cast<_T>(1) -
             eta * eta * (static_cast<_T>(1) - dot_value * dot_value));
  return (k >= static_cast<_T>(0))
             ? (eta * I - (eta * dot_value + std::sqrt(k)) * N)
             : vec3<_T>(0);
}
template <typename _T>
inline vec4<_T> refract(const vec4<_T> &I, const vec4<_T> &N, const _T &eta) {
  _T const dot_value(dot(N, I));
  _T const k(static_cast<_T>(1) -
             eta * eta * (static_cast<_T>(1) - dot_value * dot_value));
  return (k >= static_cast<_T>(0))
             ? (eta * I - (eta * dot_value + std::sqrt(k)) * N)
             : vec4<_T>(0);
}

} // namespace specula

#endif // SPECULA_MATH_GEOMETRIC_HPP_
