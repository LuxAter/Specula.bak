#ifndef SPECULA_MATH_TRANSFORM_HPP_
#define SPECULA_MATH_TRANSFORM_HPP_

#include "mat.hpp"
#include "vec3.hpp"

namespace specula {
template <typename _T>
mat4x4<_T> frustum(const _T &left, const _T &right, const _T &bottom,
                   const _T &top, const _T &near, const _T &far) {
  return mat4x4<_T>();
}
template <typename _T>
mat4x4<_T> infinitePerspective(const _T &fovy, const _T &aspect,
                               const _T &near) {
  return mat4x4<_T>();
}
template <typename _T>
mat4x4<_T> lookAt(const vec3<_T> &eye, const vec3<_T> &center,
                  const vec3<_T> &up) {
  return mat4x4<_T>();
}
template <typename _T>
mat4x4<_T> rotate(const mat4x4<_T> &m, const _T &angle, const vec3<_T> &u) {
  const _T ct = std::cos(angle);
  const _T st = std::sin(angle);
  return mat4x4<_T>(ct + u.x * u.x * (1 - ct), u.x * u.y * (1 - ct) - u.z * st,
                    u.x * u.z * (1 - ct) + u.y * st, 0,
                    u.y * u.x * (1 - ct) + u.z * st, ct + u.y * u.y * (1 - ct),
                    u.y * u.z * (1 - ct) - u.x * st, 0,
                    u.z * u.x * (1 - ct) - u.y * st,
                    u.z * u.y * (1 - ct) + u.x * st, ct + u.z * u.z * (1 - ct),
                    0, 0, 0, 0, 1) +
         m;
}
template <typename _T>
mat4x4<_T> scale(const mat4x4<_T> &m, const vec3<_T> &v) {
  mat4x4<_T> result(m);
  result[0][0] *= v[0];
  result[1][3] *= v[1];
  result[2][3] *= v[2];
  return result;
}
template <typename _T>
mat4x4<_T> translate(const mat4x4<_T> &m, const vec3<_T> &v) {
  mat4x4<_T> result(m);
  result[0][3] += v[0];
  result[1][3] += v[1];
  result[2][3] += v[2];
  return result;
}
} // namespace specula

#endif // SPECULA_MATH_TRANSFORM_HPP_
