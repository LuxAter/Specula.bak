#ifndef SPECULA_MATH_GEOMETRIC_HPP_
#define SPECULA_MATH_GEOMETRIC_HPP_

#include <cmath>

// #include "matrix.hpp"
#include "vector.hpp"

namespace specula {
namespace math {

  template <typename _T>
  inline _T length(const _T& x) {
    return x;
  }
  template <typename _T, std::size_t _N>
  inline _T length(const vec<_T, _N>& x) {
    _T sum = _T();
    for (std::size_t i = 0; i < _N; ++i) {
      sum += std::pow(x[i], _T(2));
    }
    return std::sqrt(sum);
  }

  template <typename _T>
  inline _T distance(const _T& p0, const _T& p1) {
    return p0 - p1;
  }
  template <typename _T, std::size_t _N>
  inline _T distance(const vec<_T, _N>& p0, const vec<_T, _N>& p1) {
    _T sum = _T();
    for (std::size_t i = 0; i < _N; ++i) {
      sum += std::pow(p0[i] - p1[i], _T(2));
    }
    return std::sqrt(sum);
  }

  template <typename _T>
  inline _T dot(const _T& x, const _T& y) {
    return x * y;
  }
  template <typename _T, std::size_t _N>
  inline _T dot(const vec<_T, _N>& x, const vec<_T, _N>& y) {
    _T sum = _T();
    for (std::size_t i = 0; i < _N; ++i) {
      sum += x[i] * y[i];
    }
    return sum;
  }

  template <typename _T>
  inline _T dot2(const _T& x) {
    return x * x;
  }
  template <typename _T, std::size_t _N>
  inline _T dot2(const vec<_T, _N>& x) {
    _T sum = _T();
    for (std::size_t i = 0; i < _N; ++i) {
      sum += x[i] * x[i];
    }
    return sum;
  }

  template <typename _T>
  inline vec<_T, 2> cross(const vec<_T, 2>& x) {
    return vec<_T, 2>{x[1], -x[0]};
  }
  template <typename _T>
  inline vec<_T, 3> cross(const vec<_T, 3>& x, const vec<_T, 3>& y) {
    return vec<_T, 3>{x[1] * y[2] - x[2] * y[1], x[2] * y[0] - x[0] * y[2],
                      x[0] * y[1] - x[1] * y[0]};
  }
  template <typename _T>
  vec<_T, 4> cross(const vec<_T, 4>& x, const vec<_T, 4>& y,
                   const vec<_T, 4>& z) {
    _T a = y[2] * z[3] - y[3] * z[2];
    _T b = y[1] * z[3] - y[3] * z[1];
    _T c = y[1] * z[2] - y[2] * z[1];
    _T d = y[0] * z[3] - y[3] * z[0];
    _T e = y[0] * z[2] - y[2] * z[0];
    _T f = y[0] * z[1] - y[1] * z[0];
    return vec<_T, 4>(
        x[1] * a - x[2] * b + x[3] * c, x[0] * a - x[2] * d + x[3] * e,
        x[0] * b - x[1] * d + x[3] * f, x[0] * c - x[1] * e + x[2] * f);
  }

  template <typename _T>
  inline _T normalize(const _T& x) {
    return _T(1);
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> normalize(const vec<_T, _N>& x) {
    return x / length(x);
  }

  template <typename _T>
  inline _T faceforward(const _T& N, const _T& I, const _T& Nref) {
    (dot(Nref, I) < 0) ? N : -N;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> faceforward(const vec<_T, _N>& N, const vec<_T, _N>& I,
                                 const vec<_T, _N>& Nref) {
    (dot(Nref, I) < 0) ? N : -N;
  }

  template <typename _T>
  inline _T reflect(const _T& I, const _T& N) {
    return I - _T(2) * dot(N, I) * N;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> reflect(const vec<_T, _N>& I, const vec<_T, _N>& N) {
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
  template <typename _T, std::size_t _N>
  vec<_T, _N> refract(const vec<_T, _N>& I, const vec<_T, _N>& N,
                      const _T& eta) {
    _T k = _T(1) - eta * eta * (_T(1) - dot(N, I) * dot(N, I));
    if (k < _T(0)) {
      return vec<_T, _N>(0);
    } else {
      return eta * I - (eta * dot(N, I) + sqrt(k)) * N;
    }
  }

  template <typename _T>
  void translate(mat<_T, 4, 4>& tran, mat<_T, 4, 4>& inv, const vec<_T, 3>& d) {
    mat<_T, 4, 4> t(_T(1));
    t(0, 3) = d[0];
    t(1, 3) = d[1];
    t(2, 3) = d[2];
    tran = t * tran;
    t(0, 3) = -d[0];
    t(1, 3) = -d[1];
    t(2, 3) = -d[2];
    inv = inv * t;
  }
  template <typename _T>
  void scale(mat<_T, 4, 4>& tran, mat<_T, 4, 4>& inv, const vec<_T, 3>& s) {
    mat<_T, 4, 4> t(_T(1));
    t(0, 0) = s[0];
    t(1, 1) = s[1];
    t(2, 2) = s[2];
    tran = t * tran;
    t(0, 0) = _T(1) / s[0];
    t(1, 1) = _T(1) / s[1];
    t(2, 2) = _T(1) / s[2];
    inv = inv * t;
  }
  template <typename _T>
  void rotateX(mat<_T, 4, 4>& tran, mat<_T, 4, 4>& inv, const _T& radians) {
    mat<_T, 4, 4> t(_T(1));
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
  void rotateY(mat<_T, 4, 4>& tran, mat<_T, 4, 4>& inv, const _T& radians) {
    mat<_T, 4, 4> t(_T(1));
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
  void rotateZ(mat<_T, 4, 4>& tran, mat<_T, 4, 4>& inv, const _T& radians) {
    mat<_T, 4, 4> t(_T(1));
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
  void rotateXYZ(mat<_T, 4, 4>& tran, mat<_T, 4, 4>& inv, const vec<_T, 3>& r) {
    rotateX(tran, inv, r[0]);
    rotateY(tran, inv, r[1]);
    rotateZ(tran, inv, r[2]);
  }
  template <typename _T>
  void rotateXZY(mat<_T, 4, 4>& tran, mat<_T, 4, 4>& inv, const vec<_T, 3>& r) {
    rotateX(tran, inv, r[0]);
    rotateZ(tran, inv, r[2]);
    rotateY(tran, inv, r[1]);
  }
  template <typename _T>
  void rotateYXZ(mat<_T, 4, 4>& tran, mat<_T, 4, 4>& inv, const vec<_T, 3>& r) {
    rotateY(tran, inv, r[1]);
    rotateX(tran, inv, r[0]);
    rotateZ(tran, inv, r[2]);
  }
  template <typename _T>
  void rotateYZX(mat<_T, 4, 4>& tran, mat<_T, 4, 4>& inv, const vec<_T, 3>& r) {
    rotateY(tran, inv, r[1]);
    rotateZ(tran, inv, r[2]);
    rotateX(tran, inv, r[0]);
  }
  template <typename _T>
  void rotateZXY(mat<_T, 4, 4>& tran, mat<_T, 4, 4>& inv, const vec<_T, 3>& r) {
    rotateZ(tran, inv, r[2]);
    rotateX(tran, inv, r[0]);
    rotateY(tran, inv, r[1]);
  }
  template <typename _T>
  void rotateZYX(mat<_T, 4, 4>& tran, mat<_T, 4, 4>& inv, const vec<_T, 3>& r) {
    rotateZ(tran, inv, r[2]);
    rotateY(tran, inv, r[1]);
    rotateX(tran, inv, r[0]);
  }

}  // namespace math
}  // namespace specula

#endif  // SPECULA_MATH_GEOMETRIC_HPP_
