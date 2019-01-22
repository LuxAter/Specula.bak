#ifndef SPECULA_MATH_GEOMETRIC_HPP_
#define SPECULA_MATH_GEOMETRIC_HPP_

#include <cmath>

#include "matrix.hpp"
#include "vector.hpp"

namespace specula {
namespace math {

  template <typename _T>
  inline _T length(const _T& x) {
    return x;
  }
  template <typename _T>
  inline _T length(const vec2<_T>& x) {
    return std::sqrt(std::pow(x.x, _T(2)) + std::pow(x.y, _T(2)));
  }
  template <typename _T>
  inline _T length(const vec3<_T>& x) {
    return std::sqrt(std::pow(x.x, _T(2)) + std::pow(x.y, _T(2)) +
                     std::pow(x.z, _T(2)));
  }
  template <typename _T>
  inline _T length(const vec4<_T>& x) {
    return std::sqrt(std::pow(x.x, _T(2)) + std::pow(x.y, _T(2)) +
                     std::pow(x.z, _T(2)) + std::pow(x.w, _T(2)));
  }

  template <typename _T>
  inline _T distance(const _T& p0, const _T& p1) {
    return p0 - p1;
  }
  template <typename _T>
  inline _T distance(const vec2<_T>& p0, const vec2<_T>& p1) {
    return std::sqrt(std::pow(p0.x - p1.x, _T(2)) +
                     std::pow(p0.y - p1.y, _T(2)));
  }
  template <typename _T>
  inline _T distance(const vec3<_T>& p0, const vec3<_T>& p1) {
    return std::sqrt(std::pow(p0.x - p1.x, _T(2)) +
                     std::pow(p0.y - p1.y, _T(2)) +
                     std::pow(p0.z - p1.z, _T(2)));
  }
  template <typename _T>
  inline _T distance(const vec4<_T>& p0, const vec4<_T>& p1) {
    return std::sqrt(
        std::pow(p0.x - p1.x, _T(2)) + std::pow(p0.y - p1.y, _T(2)) +
        std::pow(p0.z - p1.z, _T(2)) + std::pow(p0.w - p1.w, _T(2)));
  }

  template <typename _T>
  inline _T dot(const _T& x, const _T& y) {
    return x * y;
  }
  template <typename _T>
  inline _T dot(const vec2<_T>& x, const vec2<_T>& y) {
    return x.x * y.x + x.y * y.y;
  }
  template <typename _T>
  inline _T dot(const vec3<_T>& x, const vec3<_T>& y) {
    return x.x * y.x + x.y * y.y + x.z * y.z;
  }
  template <typename _T>
  inline _T dot(const vec4<_T>& x, const vec4<_T>& y) {
    return x.x * y.x + x.y * y.y + x.z * y.z + x.w * y.w;
  }

  template <typename _T>
  inline _T dot2(const _T& x) {
    return x * x;
  }
  template <typename _T>
  inline _T dot2(const vec2<_T>& x) {
    return x.x * x.x + x.y * x.y;
  }
  template <typename _T>
  inline _T dot2(const vec3<_T>& x) {
    return x.x * x.x + x.y * x.y + x.z * x.z;
  }
  template <typename _T>
  inline _T dot2(const vec4<_T>& x) {
    return x.x * x.x + x.y * x.y + x.z * x.z + x.w * x.w;
  }

  template <typename _T>
  inline vec2<_T> cross(const vec2<_T>& x) {
    return vec2<_T>{x.y, -x.x};
  }
  template <typename _T>
  inline vec3<_T> cross(const vec3<_T>& x, const vec3<_T>& y) {
    return vec3<_T>{x.y * y.z - x.z * y.y, x.z * y.x - x.x * y.z,
                    x.x * y.y - x.y * y.x};
  }
  template <typename _T>
  vec4<_T> cross(const vec4<_T>& x, const vec4<_T>& y, const vec4<_T>& z) {
    _T a = y.z * z.w - y.w * z.z;
    _T b = y.y * z.w - y.w * z.y;
    _T c = y.y * z.z - y.z * z.y;
    _T d = y.x * z.w - y.w * z.x;
    _T e = y.x * z.z - y.z * z.x;
    _T f = y.x * z.y - y.y * z.x;
    return vec4<_T>(x.y * a - x.z * b + x.w * c, x.x * a - x.z * d + x.w * e,
                    x.x * b - x.y * d + x.w * f, x.x * c - x.y * e + x.z * f);
  }

  template <typename _T>
  inline _T normalize(const _T& x) {
    return _T(1);
  }
  template <typename _T>
  inline vec2<_T> normalize(const vec2<_T>& x) {
    return x / (std::sqrt(std::pow(x.x, _T(2)) + std::pow(x.y, _T(2))));
  }
  template <typename _T>
  inline vec3<_T> normalize(const vec3<_T>& x) {
    return x / (std::sqrt(std::pow(x.x, _T(2)) + std::pow(x.y, _T(2)) +
                          std::pow(x.z, _T(2))));
  }
  template <typename _T>
  inline vec4<_T> normalize(const vec4<_T>& x) {
    return x / (std::sqrt(std::pow(x.x, _T(2)) + std::pow(x.y, _T(2)) +
                          std::pow(x.z, _T(2)) + std::pow(x.w, _T(2))));
  }

  template <typename _T>
  inline _T faceforward(const _T& N, const _T& I, const _T& Nref) {
    (dot(Nref, I) < 0) ? N : -N;
  }
  template <typename _T>
  inline vec2<_T> faceforward(const vec2<_T>& N, const vec2<_T>& I,
                              const vec2<_T>& Nref) {
    (dot(Nref, I) < 0) ? N : -N;
  }
  template <typename _T>
  inline vec3<_T> faceforward(const vec3<_T>& N, const vec3<_T>& I,
                              const vec3<_T>& Nref) {
    (dot(Nref, I) < 0) ? N : -N;
  }
  template <typename _T>
  inline vec4<_T> faceforward(const vec4<_T>& N, const vec4<_T>& I,
                              const vec4<_T>& Nref) {
    (dot(Nref, I) < 0) ? N : -N;
  }

  template <typename _T>
  inline _T reflect(const _T& I, const _T& N) {
    return I - _T(2) * dot(N, I) * N;
  }
  template <typename _T>
  inline vec2<_T> reflect(const vec2<_T>& I, const vec2<_T>& N) {
    return I - _T(2) * dot(N, I) * N;
  }
  template <typename _T>
  inline vec3<_T> reflect(const vec3<_T>& I, const vec3<_T>& N) {
    return I - _T(2) * dot(N, I) * N;
  }
  template <typename _T>
  inline vec4<_T> reflect(const vec4<_T>& I, const vec4<_T>& N) {
    return I - _T(2) * dot(N, I) * N;
  }

  template <typename _T>
  _T refract(const _T& I, const _T& N, const _T& eta) {
    _T k = _T(1) - eta * eta * (_T(1) - dot(N, I) * dot(N, I));
    if (k < _T(0)) {
      return _T(0);
    } else {
      return eta * I - (eta * dot(N, I) + sqrt(k)) * N;
    }
  }
  template <typename _T>
  vec2<_T> refract(const vec2<_T>& I, const vec2<_T>& N, const _T& eta) {
    _T k = _T(1) - eta * eta * (_T(1) - dot(N, I) * dot(N, I));
    if (k < _T(0)) {
      return vec2<_T>(0);
    } else {
      return eta * I - (eta * dot(N, I) + sqrt(k)) * N;
    }
  }
  template <typename _T>
  vec3<_T> refract(const vec3<_T>& I, const vec3<_T>& N, const _T& eta) {
    _T k = _T(1) - eta * eta * (_T(1) - dot(N, I) * dot(N, I));
    if (k < _T(0)) {
      return vec3<_T>(0);
    } else {
      return eta * I - (eta * dot(N, I) + sqrt(k)) * N;
    }
  }
  template <typename _T>
  vec4<_T> refract(const vec4<_T>& I, const vec4<_T>& N, const _T& eta) {
    _T k = _T(1) - eta * eta * (_T(1) - dot(N, I) * dot(N, I));
    if (k < _T(0)) {
      return vec4<_T>(0);
    } else {
      return eta * I - (eta * dot(N, I) + sqrt(k)) * N;
    }
  }

  template <typename _T>
  void translate(mat4<_T>& tran, mat4<_T>& inv, const vec3<_T>& d) {
    mat4<_T> t(_T(1));
    t(0, 3) = d.x;
    t(1, 3) = d.y;
    t(2, 3) = d.z;
    tran = t * tran;
    t(0, 3) = -d.x;
    t(1, 3) = -d.y;
    t(2, 3) = -d.z;
    inv = inv * t;
  }
  template <typename _T>
  void scale(mat4<_T>& tran, mat4<_T>& inv, const _T& s) {
    mat4<_T> t(_T(1));
    t(0, 0) = s;
    t(1, 1) = s;
    t(2, 2) = s;
    tran = t * tran;
    t(0, 0) = _T(1) / s;
    t(1, 1) = _T(1) / s;
    t(2, 2) = _T(1) / s;
    inv = inv * t;
  }
  template <typename _T>
  void scale(mat4<_T>& tran, mat4<_T>& inv, const vec3<_T>& s) {
    mat4<_T> t(_T(1));
    t(0, 0) = s.x;
    t(1, 1) = s.y;
    t(2, 2) = s.z;
    tran = t * tran;
    t(0, 0) = _T(1) / s.x;
    t(1, 1) = _T(1) / s.y;
    t(2, 2) = _T(1) / s.z;
    inv = inv * t;
  }
  template <typename _T>
  void rotateX(mat4<_T>& tran, mat4<_T>& inv, const _T& radians) {
    mat4<_T> t(_T(1));
    _T cs = cos(radians), sn = sin(radians);
    t(1, 1) = cs;
    t(1, 2) = -sn;
    t(2, 1) = sn;
    t(2, 2) = cs;
    tran = t * tran;
    t(1, 1) = cs;
    t(1, 2) = sn;
    t(2, 1) = -sn;
    t(2, 2) = cs;
    inv = inv * t;
  }
  template <typename _T>
  void rotateY(mat4<_T>& tran, mat4<_T>& inv, const _T& radians) {
    mat4<_T> t(_T(1));
    _T cs = cos(radians), sn = sin(radians);
    t(0, 0) = cs;
    t(0, 2) = sn;
    t(2, 0) = -sn;
    t(2, 2) = cs;
    tran = t * tran;
    t(0, 0) = cs;
    t(0, 2) = -sn;
    t(2, 0) = sn;
    t(2, 2) = cs;
    inv = inv * t;
  }
  template <typename _T>
  void rotateZ(mat4<_T>& tran, mat4<_T>& inv, const _T& radians) {
    mat4<_T> t(_T(1));
    _T cs = cos(radians), sn = sin(radians);
    t(0, 0) = cs;
    t(0, 1) = -sn;
    t(1, 0) = sn;
    t(1, 1) = cs;
    tran = t * tran;
    t(0, 0) = cs;
    t(0, 1) = sn;
    t(1, 0) = -sn;
    t(1, 1) = cs;
    inv = inv * t;
  }
  template <typename _T>
  void rotateXYZ(mat4<_T>& tran, mat4<_T>& inv, const vec3<_T>& r) {
    rotateX(tran, inv, r.x);
    rotateY(tran, inv, r.y);
    rotateZ(tran, inv, r.z);
  }
  template <typename _T>
  void rotateXZY(mat4<_T>& tran, mat4<_T>& inv, const vec3<_T>& r) {
    rotateX(tran, inv, r.x);
    rotateZ(tran, inv, r.z);
    rotateY(tran, inv, r.y);
  }
  template <typename _T>
  void rotateYXZ(mat4<_T>& tran, mat4<_T>& inv, const vec3<_T>& r) {
    rotateY(tran, inv, r.y);
    rotateX(tran, inv, r.x);
    rotateZ(tran, inv, r.z);
  }
  template <typename _T>
  void rotateYZX(mat4<_T>& tran, mat4<_T>& inv, const vec3<_T>& r) {
    rotateY(tran, inv, r.y);
    rotateZ(tran, inv, r.z);
    rotateX(tran, inv, r.x);
  }
  template <typename _T>
  void rotateZXY(mat4<_T>& tran, mat4<_T>& inv, const vec3<_T>& r) {
    rotateZ(tran, inv, r.z);
    rotateX(tran, inv, r.x);
    rotateY(tran, inv, r.y);
  }
  template <typename _T>
  void rotateZYX(mat4<_T>& tran, mat4<_T>& inv, const vec3<_T>& r) {
    rotateZ(tran, inv, r.z);
    rotateY(tran, inv, r.y);
    rotateX(tran, inv, r.x);
  }

}  // namespace math
}  // namespace specula

#endif  // SPECULA_MATH_GEOMETRIC_HPP_
