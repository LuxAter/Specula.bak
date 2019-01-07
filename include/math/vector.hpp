#ifndef SPECULA_MATH_VECTOR_HPP_
#define SPECULA_MATH_VECTOR_HPP_

#include <array>
#include <cmath>
#include <functional>
#include <iostream>
#include <memory>

namespace specula {
namespace math {
  template <typename _T, std::size_t _N>
  class vec_base;
  template <typename _T, std::size_t _N>
  class swizzel;
  template <typename _T, std::size_t _N>
  class vec;

  template <typename _T, std::size_t _N>
  class vec_base {
   public:
    vec_base() {
      for (std::size_t i = 0; i < _N; ++i) {
        data_[i] = std::make_shared<_T>(_T());
      }
    }

    inline vec_base<_T, _N>& operator=(const vec_base<_T, _N>& vec) {
      for (std::size_t i = 0; i < _N; ++i) {
        *data_[i] = vec[i];
      }
      return *this;
    }

    template <typename _U>
    inline vec_base<_T, _N>& operator+=(const _U& rhs) {
      for (std::size_t i = 0; i < _N; ++i) {
        *data_[i] += rhs;
      }
      return *this;
    }
    template <typename _U, std::size_t _M>
    inline vec_base<_T, _N>& operator+=(const vec_base<_U, _M>& rhs) {
      for (std::size_t i = 0; i < std::min(_N, _M); ++i) {
        *data_[i] += rhs[i];
      }
      return *this;
    }
    template <typename _U>
    inline vec_base<_T, _N>& operator-=(const _U& rhs) {
      for (std::size_t i = 0; i < _N; ++i) {
        *data_[i] -= rhs;
      }
      return *this;
    }
    template <typename _U, std::size_t _M>
    inline vec_base<_T, _N>& operator-=(const vec_base<_U, _M>& rhs) {
      for (std::size_t i = 0; i < std::min(_N, _M); ++i) {
        *data_[i] -= rhs[i];
      }
      return *this;
    }
    template <typename _U>
    inline vec_base<_T, _N>& operator*=(const _U& rhs) {
      for (std::size_t i = 0; i < _N; ++i) {
        *data_[i] *= rhs;
      }
      return *this;
    }
    template <typename _U, std::size_t _M>
    inline vec_base<_T, _N>& operator*=(const vec_base<_U, _M>& rhs) {
      for (std::size_t i = 0; i < std::min(_N, _M); ++i) {
        *data_[i] *= rhs[i];
      }
      return *this;
    }
    template <typename _U>
    inline vec_base<_T, _N>& operator/=(const _U& rhs) {
      for (std::size_t i = 0; i < _N; ++i) {
        *data_[i] /= rhs;
      }
      return *this;
    }
    template <typename _U, std::size_t _M>
    inline vec_base<_T, _N>& operator/=(const vec_base<_U, _M>& rhs) {
      for (std::size_t i = 0; i < std::min(_N, _M); ++i) {
        *data_[i] /= rhs[i];
      }
      return *this;
    }

    inline _T& operator[](std::size_t i) { return *data_[i]; }
    inline const _T& operator[](std::size_t i) const { return *data_[i]; }
    inline _T at(std::size_t i) { return *data_[i]; }
    inline const _T at(std::size_t i) const { return *data_[i]; }

    inline _T& x() { return *data_[0]; }
    inline _T& y() { return *data_[1]; }
    inline _T& z() { return *data_[2]; }
    inline _T& w() { return *data_[3]; }

    inline swizzel<_T, 2> xx() { return swizzel<_T, 2>{data_[0], data_[0]}; }
    inline swizzel<_T, 2> xy() { return swizzel<_T, 2>{data_[0], data_[1]}; }
    inline swizzel<_T, 2> xz() { return swizzel<_T, 2>{data_[0], data_[2]}; }
    inline swizzel<_T, 2> xw() { return swizzel<_T, 2>{data_[0], data_[3]}; }
    inline swizzel<_T, 2> yx() { return swizzel<_T, 2>{data_[1], data_[0]}; }
    inline swizzel<_T, 2> yy() { return swizzel<_T, 2>{data_[1], data_[1]}; }
    inline swizzel<_T, 2> yz() { return swizzel<_T, 2>{data_[1], data_[2]}; }
    inline swizzel<_T, 2> yw() { return swizzel<_T, 2>{data_[1], data_[3]}; }
    inline swizzel<_T, 2> zx() { return swizzel<_T, 2>{data_[2], data_[0]}; }
    inline swizzel<_T, 2> zy() { return swizzel<_T, 2>{data_[2], data_[1]}; }
    inline swizzel<_T, 2> zz() { return swizzel<_T, 2>{data_[2], data_[2]}; }
    inline swizzel<_T, 2> zw() { return swizzel<_T, 2>{data_[2], data_[3]}; }
    inline swizzel<_T, 2> wx() { return swizzel<_T, 2>{data_[3], data_[0]}; }
    inline swizzel<_T, 2> wy() { return swizzel<_T, 2>{data_[3], data_[1]}; }
    inline swizzel<_T, 2> wz() { return swizzel<_T, 2>{data_[3], data_[2]}; }
    inline swizzel<_T, 2> ww() { return swizzel<_T, 2>{data_[3], data_[3]}; }

    inline swizzel<_T, 3> xxx() {
      return swizzel<_T, 3>{data_[0], data_[0], data_[0]};
    }
    inline swizzel<_T, 3> xxy() {
      return swizzel<_T, 3>{data_[0], data_[0], data_[1]};
    }
    inline swizzel<_T, 3> xxz() {
      return swizzel<_T, 3>{data_[0], data_[0], data_[2]};
    }
    inline swizzel<_T, 3> xxw() {
      return swizzel<_T, 3>{data_[0], data_[0], data_[3]};
    }
    inline swizzel<_T, 3> xyx() {
      return swizzel<_T, 3>{data_[0], data_[1], data_[0]};
    }
    inline swizzel<_T, 3> xyy() {
      return swizzel<_T, 3>{data_[0], data_[1], data_[1]};
    }
    inline swizzel<_T, 3> xyz() {
      return swizzel<_T, 3>{data_[0], data_[1], data_[2]};
    }
    inline swizzel<_T, 3> xyw() {
      return swizzel<_T, 3>{data_[0], data_[1], data_[3]};
    }
    inline swizzel<_T, 3> xzx() {
      return swizzel<_T, 3>{data_[0], data_[2], data_[0]};
    }
    inline swizzel<_T, 3> xzy() {
      return swizzel<_T, 3>{data_[0], data_[2], data_[1]};
    }
    inline swizzel<_T, 3> xzz() {
      return swizzel<_T, 3>{data_[0], data_[2], data_[2]};
    }
    inline swizzel<_T, 3> xzw() {
      return swizzel<_T, 3>{data_[0], data_[2], data_[3]};
    }
    inline swizzel<_T, 3> xwx() {
      return swizzel<_T, 3>{data_[0], data_[3], data_[0]};
    }
    inline swizzel<_T, 3> xwy() {
      return swizzel<_T, 3>{data_[0], data_[3], data_[1]};
    }
    inline swizzel<_T, 3> xwz() {
      return swizzel<_T, 3>{data_[0], data_[3], data_[2]};
    }
    inline swizzel<_T, 3> xww() {
      return swizzel<_T, 3>{data_[0], data_[3], data_[3]};
    }

    inline swizzel<_T, 3> yxx() {
      return swizzel<_T, 3>{data_[1], data_[0], data_[0]};
    }
    inline swizzel<_T, 3> yxy() {
      return swizzel<_T, 3>{data_[1], data_[0], data_[1]};
    }
    inline swizzel<_T, 3> yxz() {
      return swizzel<_T, 3>{data_[1], data_[0], data_[2]};
    }
    inline swizzel<_T, 3> yxw() {
      return swizzel<_T, 3>{data_[1], data_[0], data_[3]};
    }
    inline swizzel<_T, 3> yyx() {
      return swizzel<_T, 3>{data_[1], data_[1], data_[0]};
    }
    inline swizzel<_T, 3> yyy() {
      return swizzel<_T, 3>{data_[1], data_[1], data_[1]};
    }
    inline swizzel<_T, 3> yyz() {
      return swizzel<_T, 3>{data_[1], data_[1], data_[2]};
    }
    inline swizzel<_T, 3> yyw() {
      return swizzel<_T, 3>{data_[1], data_[1], data_[3]};
    }
    inline swizzel<_T, 3> yzx() {
      return swizzel<_T, 3>{data_[1], data_[2], data_[0]};
    }
    inline swizzel<_T, 3> yzy() {
      return swizzel<_T, 3>{data_[1], data_[2], data_[1]};
    }
    inline swizzel<_T, 3> yzz() {
      return swizzel<_T, 3>{data_[1], data_[2], data_[2]};
    }
    inline swizzel<_T, 3> yzw() {
      return swizzel<_T, 3>{data_[1], data_[2], data_[3]};
    }
    inline swizzel<_T, 3> ywx() {
      return swizzel<_T, 3>{data_[1], data_[3], data_[0]};
    }
    inline swizzel<_T, 3> ywy() {
      return swizzel<_T, 3>{data_[1], data_[3], data_[1]};
    }
    inline swizzel<_T, 3> ywz() {
      return swizzel<_T, 3>{data_[1], data_[3], data_[2]};
    }
    inline swizzel<_T, 3> yww() {
      return swizzel<_T, 3>{data_[1], data_[3], data_[3]};
    }

    inline swizzel<_T, 3> zxx() {
      return swizzel<_T, 3>{data_[2], data_[0], data_[0]};
    }
    inline swizzel<_T, 3> zxy() {
      return swizzel<_T, 3>{data_[2], data_[0], data_[1]};
    }
    inline swizzel<_T, 3> zxz() {
      return swizzel<_T, 3>{data_[2], data_[0], data_[2]};
    }
    inline swizzel<_T, 3> zxw() {
      return swizzel<_T, 3>{data_[2], data_[0], data_[3]};
    }
    inline swizzel<_T, 3> zyx() {
      return swizzel<_T, 3>{data_[2], data_[1], data_[0]};
    }
    inline swizzel<_T, 3> zyy() {
      return swizzel<_T, 3>{data_[2], data_[1], data_[1]};
    }
    inline swizzel<_T, 3> zyz() {
      return swizzel<_T, 3>{data_[2], data_[1], data_[2]};
    }
    inline swizzel<_T, 3> zyw() {
      return swizzel<_T, 3>{data_[2], data_[1], data_[3]};
    }
    inline swizzel<_T, 3> zzx() {
      return swizzel<_T, 3>{data_[2], data_[2], data_[0]};
    }
    inline swizzel<_T, 3> zzy() {
      return swizzel<_T, 3>{data_[2], data_[2], data_[1]};
    }
    inline swizzel<_T, 3> zzz() {
      return swizzel<_T, 3>{data_[2], data_[2], data_[2]};
    }
    inline swizzel<_T, 3> zzw() {
      return swizzel<_T, 3>{data_[2], data_[2], data_[3]};
    }
    inline swizzel<_T, 3> zwx() {
      return swizzel<_T, 3>{data_[2], data_[3], data_[0]};
    }
    inline swizzel<_T, 3> zwy() {
      return swizzel<_T, 3>{data_[2], data_[3], data_[1]};
    }
    inline swizzel<_T, 3> zwz() {
      return swizzel<_T, 3>{data_[2], data_[3], data_[2]};
    }
    inline swizzel<_T, 3> zww() {
      return swizzel<_T, 3>{data_[2], data_[3], data_[3]};
    }

    inline swizzel<_T, 3> wxx() {
      return swizzel<_T, 3>{data_[3], data_[0], data_[0]};
    }
    inline swizzel<_T, 3> wxy() {
      return swizzel<_T, 3>{data_[3], data_[0], data_[1]};
    }
    inline swizzel<_T, 3> wxz() {
      return swizzel<_T, 3>{data_[3], data_[0], data_[2]};
    }
    inline swizzel<_T, 3> wxw() {
      return swizzel<_T, 3>{data_[3], data_[0], data_[3]};
    }
    inline swizzel<_T, 3> wyx() {
      return swizzel<_T, 3>{data_[3], data_[1], data_[0]};
    }
    inline swizzel<_T, 3> wyy() {
      return swizzel<_T, 3>{data_[3], data_[1], data_[1]};
    }
    inline swizzel<_T, 3> wyz() {
      return swizzel<_T, 3>{data_[3], data_[1], data_[2]};
    }
    inline swizzel<_T, 3> wyw() {
      return swizzel<_T, 3>{data_[3], data_[1], data_[3]};
    }
    inline swizzel<_T, 3> wzx() {
      return swizzel<_T, 3>{data_[3], data_[2], data_[0]};
    }
    inline swizzel<_T, 3> wzy() {
      return swizzel<_T, 3>{data_[3], data_[2], data_[1]};
    }
    inline swizzel<_T, 3> wzz() {
      return swizzel<_T, 3>{data_[3], data_[2], data_[2]};
    }
    inline swizzel<_T, 3> wzw() {
      return swizzel<_T, 3>{data_[3], data_[2], data_[3]};
    }
    inline swizzel<_T, 3> wwx() {
      return swizzel<_T, 3>{data_[3], data_[3], data_[0]};
    }
    inline swizzel<_T, 3> wwy() {
      return swizzel<_T, 3>{data_[3], data_[3], data_[1]};
    }
    inline swizzel<_T, 3> wwz() {
      return swizzel<_T, 3>{data_[3], data_[3], data_[2]};
    }
    inline swizzel<_T, 3> www() {
      return swizzel<_T, 3>{data_[3], data_[3], data_[3]};
    }

    inline swizzel<_T, 4> xxxx() {
      return swizzel<_T, 4>{data_[0], data_[0], data_[0], data_[0]};
    }
    inline swizzel<_T, 4> xxxy() {
      return swizzel<_T, 4>{data_[0], data_[0], data_[0], data_[1]};
    }
    inline swizzel<_T, 4> xxxz() {
      return swizzel<_T, 4>{data_[0], data_[0], data_[0], data_[2]};
    }
    inline swizzel<_T, 4> xxxw() {
      return swizzel<_T, 4>{data_[0], data_[0], data_[0], data_[3]};
    }
    inline swizzel<_T, 4> xxyx() {
      return swizzel<_T, 4>{data_[0], data_[0], data_[1], data_[0]};
    }
    inline swizzel<_T, 4> xxyy() {
      return swizzel<_T, 4>{data_[0], data_[0], data_[1], data_[1]};
    }
    inline swizzel<_T, 4> xxyz() {
      return swizzel<_T, 4>{data_[0], data_[0], data_[1], data_[2]};
    }
    inline swizzel<_T, 4> xxyw() {
      return swizzel<_T, 4>{data_[0], data_[0], data_[1], data_[3]};
    }
    inline swizzel<_T, 4> xxzx() {
      return swizzel<_T, 4>{data_[0], data_[0], data_[2], data_[0]};
    }
    inline swizzel<_T, 4> xxzy() {
      return swizzel<_T, 4>{data_[0], data_[0], data_[2], data_[1]};
    }
    inline swizzel<_T, 4> xxzz() {
      return swizzel<_T, 4>{data_[0], data_[0], data_[2], data_[2]};
    }
    inline swizzel<_T, 4> xxzw() {
      return swizzel<_T, 4>{data_[0], data_[0], data_[2], data_[3]};
    }
    inline swizzel<_T, 4> xxwx() {
      return swizzel<_T, 4>{data_[0], data_[0], data_[3], data_[0]};
    }
    inline swizzel<_T, 4> xxwy() {
      return swizzel<_T, 4>{data_[0], data_[0], data_[3], data_[1]};
    }
    inline swizzel<_T, 4> xxwz() {
      return swizzel<_T, 4>{data_[0], data_[0], data_[3], data_[2]};
    }
    inline swizzel<_T, 4> xxww() {
      return swizzel<_T, 4>{data_[0], data_[0], data_[3], data_[3]};
    }

    inline swizzel<_T, 4> xyxx() {
      return swizzel<_T, 4>{data_[0], data_[1], data_[0], data_[0]};
    }
    inline swizzel<_T, 4> xyxy() {
      return swizzel<_T, 4>{data_[0], data_[1], data_[0], data_[1]};
    }
    inline swizzel<_T, 4> xyxz() {
      return swizzel<_T, 4>{data_[0], data_[1], data_[0], data_[2]};
    }
    inline swizzel<_T, 4> xyxw() {
      return swizzel<_T, 4>{data_[0], data_[1], data_[0], data_[3]};
    }
    inline swizzel<_T, 4> xyyx() {
      return swizzel<_T, 4>{data_[0], data_[1], data_[1], data_[0]};
    }
    inline swizzel<_T, 4> xyyy() {
      return swizzel<_T, 4>{data_[0], data_[1], data_[1], data_[1]};
    }
    inline swizzel<_T, 4> xyyz() {
      return swizzel<_T, 4>{data_[0], data_[1], data_[1], data_[2]};
    }
    inline swizzel<_T, 4> xyyw() {
      return swizzel<_T, 4>{data_[0], data_[1], data_[1], data_[3]};
    }
    inline swizzel<_T, 4> xyzx() {
      return swizzel<_T, 4>{data_[0], data_[1], data_[2], data_[0]};
    }
    inline swizzel<_T, 4> xyzy() {
      return swizzel<_T, 4>{data_[0], data_[1], data_[2], data_[1]};
    }
    inline swizzel<_T, 4> xyzz() {
      return swizzel<_T, 4>{data_[0], data_[1], data_[2], data_[2]};
    }
    inline swizzel<_T, 4> xyzw() {
      return swizzel<_T, 4>{data_[0], data_[1], data_[2], data_[3]};
    }
    inline swizzel<_T, 4> xywx() {
      return swizzel<_T, 4>{data_[0], data_[1], data_[3], data_[0]};
    }
    inline swizzel<_T, 4> xywy() {
      return swizzel<_T, 4>{data_[0], data_[1], data_[3], data_[1]};
    }
    inline swizzel<_T, 4> xywz() {
      return swizzel<_T, 4>{data_[0], data_[1], data_[3], data_[2]};
    }
    inline swizzel<_T, 4> xyww() {
      return swizzel<_T, 4>{data_[0], data_[1], data_[3], data_[3]};
    }

    inline swizzel<_T, 4> xzxx() {
      return swizzel<_T, 4>{data_[0], data_[2], data_[0], data_[0]};
    }
    inline swizzel<_T, 4> xzxy() {
      return swizzel<_T, 4>{data_[0], data_[2], data_[0], data_[1]};
    }
    inline swizzel<_T, 4> xzxz() {
      return swizzel<_T, 4>{data_[0], data_[2], data_[0], data_[2]};
    }
    inline swizzel<_T, 4> xzxw() {
      return swizzel<_T, 4>{data_[0], data_[2], data_[0], data_[3]};
    }
    inline swizzel<_T, 4> xzyx() {
      return swizzel<_T, 4>{data_[0], data_[2], data_[1], data_[0]};
    }
    inline swizzel<_T, 4> xzyy() {
      return swizzel<_T, 4>{data_[0], data_[2], data_[1], data_[1]};
    }
    inline swizzel<_T, 4> xzyz() {
      return swizzel<_T, 4>{data_[0], data_[2], data_[1], data_[2]};
    }
    inline swizzel<_T, 4> xzyw() {
      return swizzel<_T, 4>{data_[0], data_[2], data_[1], data_[3]};
    }
    inline swizzel<_T, 4> xzzx() {
      return swizzel<_T, 4>{data_[0], data_[2], data_[2], data_[0]};
    }
    inline swizzel<_T, 4> xzzy() {
      return swizzel<_T, 4>{data_[0], data_[2], data_[2], data_[1]};
    }
    inline swizzel<_T, 4> xzzz() {
      return swizzel<_T, 4>{data_[0], data_[2], data_[2], data_[2]};
    }
    inline swizzel<_T, 4> xzzw() {
      return swizzel<_T, 4>{data_[0], data_[2], data_[2], data_[3]};
    }
    inline swizzel<_T, 4> xzwx() {
      return swizzel<_T, 4>{data_[0], data_[2], data_[3], data_[0]};
    }
    inline swizzel<_T, 4> xzwy() {
      return swizzel<_T, 4>{data_[0], data_[2], data_[3], data_[1]};
    }
    inline swizzel<_T, 4> xzwz() {
      return swizzel<_T, 4>{data_[0], data_[2], data_[3], data_[2]};
    }
    inline swizzel<_T, 4> xzww() {
      return swizzel<_T, 4>{data_[0], data_[2], data_[3], data_[3]};
    }

    inline swizzel<_T, 4> xwxx() {
      return swizzel<_T, 4>{data_[0], data_[3], data_[0], data_[0]};
    }
    inline swizzel<_T, 4> xwxy() {
      return swizzel<_T, 4>{data_[0], data_[3], data_[0], data_[1]};
    }
    inline swizzel<_T, 4> xwxz() {
      return swizzel<_T, 4>{data_[0], data_[3], data_[0], data_[2]};
    }
    inline swizzel<_T, 4> xwxw() {
      return swizzel<_T, 4>{data_[0], data_[3], data_[0], data_[3]};
    }
    inline swizzel<_T, 4> xwyx() {
      return swizzel<_T, 4>{data_[0], data_[3], data_[1], data_[0]};
    }
    inline swizzel<_T, 4> xwyy() {
      return swizzel<_T, 4>{data_[0], data_[3], data_[1], data_[1]};
    }
    inline swizzel<_T, 4> xwyz() {
      return swizzel<_T, 4>{data_[0], data_[3], data_[1], data_[2]};
    }
    inline swizzel<_T, 4> xwyw() {
      return swizzel<_T, 4>{data_[0], data_[3], data_[1], data_[3]};
    }
    inline swizzel<_T, 4> xwzx() {
      return swizzel<_T, 4>{data_[0], data_[3], data_[2], data_[0]};
    }
    inline swizzel<_T, 4> xwzy() {
      return swizzel<_T, 4>{data_[0], data_[3], data_[2], data_[1]};
    }
    inline swizzel<_T, 4> xwzz() {
      return swizzel<_T, 4>{data_[0], data_[3], data_[2], data_[2]};
    }
    inline swizzel<_T, 4> xwzw() {
      return swizzel<_T, 4>{data_[0], data_[3], data_[2], data_[3]};
    }
    inline swizzel<_T, 4> xwwx() {
      return swizzel<_T, 4>{data_[0], data_[3], data_[3], data_[0]};
    }
    inline swizzel<_T, 4> xwwy() {
      return swizzel<_T, 4>{data_[0], data_[3], data_[3], data_[1]};
    }
    inline swizzel<_T, 4> xwwz() {
      return swizzel<_T, 4>{data_[0], data_[3], data_[3], data_[2]};
    }
    inline swizzel<_T, 4> xwww() {
      return swizzel<_T, 4>{data_[0], data_[3], data_[3], data_[3]};
    }

    inline swizzel<_T, 4> yxxx() {
      return swizzel<_T, 4>{data_[1], data_[0], data_[0], data_[0]};
    }
    inline swizzel<_T, 4> yxxy() {
      return swizzel<_T, 4>{data_[1], data_[0], data_[0], data_[1]};
    }
    inline swizzel<_T, 4> yxxz() {
      return swizzel<_T, 4>{data_[1], data_[0], data_[0], data_[2]};
    }
    inline swizzel<_T, 4> yxxw() {
      return swizzel<_T, 4>{data_[1], data_[0], data_[0], data_[3]};
    }
    inline swizzel<_T, 4> yxyx() {
      return swizzel<_T, 4>{data_[1], data_[0], data_[1], data_[0]};
    }
    inline swizzel<_T, 4> yxyy() {
      return swizzel<_T, 4>{data_[1], data_[0], data_[1], data_[1]};
    }
    inline swizzel<_T, 4> yxyz() {
      return swizzel<_T, 4>{data_[1], data_[0], data_[1], data_[2]};
    }
    inline swizzel<_T, 4> yxyw() {
      return swizzel<_T, 4>{data_[1], data_[0], data_[1], data_[3]};
    }
    inline swizzel<_T, 4> yxzx() {
      return swizzel<_T, 4>{data_[1], data_[0], data_[2], data_[0]};
    }
    inline swizzel<_T, 4> yxzy() {
      return swizzel<_T, 4>{data_[1], data_[0], data_[2], data_[1]};
    }
    inline swizzel<_T, 4> yxzz() {
      return swizzel<_T, 4>{data_[1], data_[0], data_[2], data_[2]};
    }
    inline swizzel<_T, 4> yxzw() {
      return swizzel<_T, 4>{data_[1], data_[0], data_[2], data_[3]};
    }
    inline swizzel<_T, 4> yxwx() {
      return swizzel<_T, 4>{data_[1], data_[0], data_[3], data_[0]};
    }
    inline swizzel<_T, 4> yxwy() {
      return swizzel<_T, 4>{data_[1], data_[0], data_[3], data_[1]};
    }
    inline swizzel<_T, 4> yxwz() {
      return swizzel<_T, 4>{data_[1], data_[0], data_[3], data_[2]};
    }
    inline swizzel<_T, 4> yxww() {
      return swizzel<_T, 4>{data_[1], data_[0], data_[3], data_[3]};
    }

    inline swizzel<_T, 4> yyxx() {
      return swizzel<_T, 4>{data_[1], data_[1], data_[0], data_[0]};
    }
    inline swizzel<_T, 4> yyxy() {
      return swizzel<_T, 4>{data_[1], data_[1], data_[0], data_[1]};
    }
    inline swizzel<_T, 4> yyxz() {
      return swizzel<_T, 4>{data_[1], data_[1], data_[0], data_[2]};
    }
    inline swizzel<_T, 4> yyxw() {
      return swizzel<_T, 4>{data_[1], data_[1], data_[0], data_[3]};
    }
    inline swizzel<_T, 4> yyyx() {
      return swizzel<_T, 4>{data_[1], data_[1], data_[1], data_[0]};
    }
    inline swizzel<_T, 4> yyyy() {
      return swizzel<_T, 4>{data_[1], data_[1], data_[1], data_[1]};
    }
    inline swizzel<_T, 4> yyyz() {
      return swizzel<_T, 4>{data_[1], data_[1], data_[1], data_[2]};
    }
    inline swizzel<_T, 4> yyyw() {
      return swizzel<_T, 4>{data_[1], data_[1], data_[1], data_[3]};
    }
    inline swizzel<_T, 4> yyzx() {
      return swizzel<_T, 4>{data_[1], data_[1], data_[2], data_[0]};
    }
    inline swizzel<_T, 4> yyzy() {
      return swizzel<_T, 4>{data_[1], data_[1], data_[2], data_[1]};
    }
    inline swizzel<_T, 4> yyzz() {
      return swizzel<_T, 4>{data_[1], data_[1], data_[2], data_[2]};
    }
    inline swizzel<_T, 4> yyzw() {
      return swizzel<_T, 4>{data_[1], data_[1], data_[2], data_[3]};
    }
    inline swizzel<_T, 4> yywx() {
      return swizzel<_T, 4>{data_[1], data_[1], data_[3], data_[0]};
    }
    inline swizzel<_T, 4> yywy() {
      return swizzel<_T, 4>{data_[1], data_[1], data_[3], data_[1]};
    }
    inline swizzel<_T, 4> yywz() {
      return swizzel<_T, 4>{data_[1], data_[1], data_[3], data_[2]};
    }
    inline swizzel<_T, 4> yyww() {
      return swizzel<_T, 4>{data_[1], data_[1], data_[3], data_[3]};
    }

    inline swizzel<_T, 4> yzxx() {
      return swizzel<_T, 4>{data_[1], data_[2], data_[0], data_[0]};
    }
    inline swizzel<_T, 4> yzxy() {
      return swizzel<_T, 4>{data_[1], data_[2], data_[0], data_[1]};
    }
    inline swizzel<_T, 4> yzxz() {
      return swizzel<_T, 4>{data_[1], data_[2], data_[0], data_[2]};
    }
    inline swizzel<_T, 4> yzxw() {
      return swizzel<_T, 4>{data_[1], data_[2], data_[0], data_[3]};
    }
    inline swizzel<_T, 4> yzyx() {
      return swizzel<_T, 4>{data_[1], data_[2], data_[1], data_[0]};
    }
    inline swizzel<_T, 4> yzyy() {
      return swizzel<_T, 4>{data_[1], data_[2], data_[1], data_[1]};
    }
    inline swizzel<_T, 4> yzyz() {
      return swizzel<_T, 4>{data_[1], data_[2], data_[1], data_[2]};
    }
    inline swizzel<_T, 4> yzyw() {
      return swizzel<_T, 4>{data_[1], data_[2], data_[1], data_[3]};
    }
    inline swizzel<_T, 4> yzzx() {
      return swizzel<_T, 4>{data_[1], data_[2], data_[2], data_[0]};
    }
    inline swizzel<_T, 4> yzzy() {
      return swizzel<_T, 4>{data_[1], data_[2], data_[2], data_[1]};
    }
    inline swizzel<_T, 4> yzzz() {
      return swizzel<_T, 4>{data_[1], data_[2], data_[2], data_[2]};
    }
    inline swizzel<_T, 4> yzzw() {
      return swizzel<_T, 4>{data_[1], data_[2], data_[2], data_[3]};
    }
    inline swizzel<_T, 4> yzwx() {
      return swizzel<_T, 4>{data_[1], data_[2], data_[3], data_[0]};
    }
    inline swizzel<_T, 4> yzwy() {
      return swizzel<_T, 4>{data_[1], data_[2], data_[3], data_[1]};
    }
    inline swizzel<_T, 4> yzwz() {
      return swizzel<_T, 4>{data_[1], data_[2], data_[3], data_[2]};
    }
    inline swizzel<_T, 4> yzww() {
      return swizzel<_T, 4>{data_[1], data_[2], data_[3], data_[3]};
    }

    inline swizzel<_T, 4> ywxx() {
      return swizzel<_T, 4>{data_[1], data_[3], data_[0], data_[0]};
    }
    inline swizzel<_T, 4> ywxy() {
      return swizzel<_T, 4>{data_[1], data_[3], data_[0], data_[1]};
    }
    inline swizzel<_T, 4> ywxz() {
      return swizzel<_T, 4>{data_[1], data_[3], data_[0], data_[2]};
    }
    inline swizzel<_T, 4> ywxw() {
      return swizzel<_T, 4>{data_[1], data_[3], data_[0], data_[3]};
    }
    inline swizzel<_T, 4> ywyx() {
      return swizzel<_T, 4>{data_[1], data_[3], data_[1], data_[0]};
    }
    inline swizzel<_T, 4> ywyy() {
      return swizzel<_T, 4>{data_[1], data_[3], data_[1], data_[1]};
    }
    inline swizzel<_T, 4> ywyz() {
      return swizzel<_T, 4>{data_[1], data_[3], data_[1], data_[2]};
    }
    inline swizzel<_T, 4> ywyw() {
      return swizzel<_T, 4>{data_[1], data_[3], data_[1], data_[3]};
    }
    inline swizzel<_T, 4> ywzx() {
      return swizzel<_T, 4>{data_[1], data_[3], data_[2], data_[0]};
    }
    inline swizzel<_T, 4> ywzy() {
      return swizzel<_T, 4>{data_[1], data_[3], data_[2], data_[1]};
    }
    inline swizzel<_T, 4> ywzz() {
      return swizzel<_T, 4>{data_[1], data_[3], data_[2], data_[2]};
    }
    inline swizzel<_T, 4> ywzw() {
      return swizzel<_T, 4>{data_[1], data_[3], data_[2], data_[3]};
    }
    inline swizzel<_T, 4> ywwx() {
      return swizzel<_T, 4>{data_[1], data_[3], data_[3], data_[0]};
    }
    inline swizzel<_T, 4> ywwy() {
      return swizzel<_T, 4>{data_[1], data_[3], data_[3], data_[1]};
    }
    inline swizzel<_T, 4> ywwz() {
      return swizzel<_T, 4>{data_[1], data_[3], data_[3], data_[2]};
    }
    inline swizzel<_T, 4> ywww() {
      return swizzel<_T, 4>{data_[1], data_[3], data_[3], data_[3]};
    }

    inline swizzel<_T, 4> zxxx() {
      return swizzel<_T, 4>{data_[2], data_[0], data_[0], data_[0]};
    }
    inline swizzel<_T, 4> zxxy() {
      return swizzel<_T, 4>{data_[2], data_[0], data_[0], data_[1]};
    }
    inline swizzel<_T, 4> zxxz() {
      return swizzel<_T, 4>{data_[2], data_[0], data_[0], data_[2]};
    }
    inline swizzel<_T, 4> zxxw() {
      return swizzel<_T, 4>{data_[2], data_[0], data_[0], data_[3]};
    }
    inline swizzel<_T, 4> zxyx() {
      return swizzel<_T, 4>{data_[2], data_[0], data_[1], data_[0]};
    }
    inline swizzel<_T, 4> zxyy() {
      return swizzel<_T, 4>{data_[2], data_[0], data_[1], data_[1]};
    }
    inline swizzel<_T, 4> zxyz() {
      return swizzel<_T, 4>{data_[2], data_[0], data_[1], data_[2]};
    }
    inline swizzel<_T, 4> zxyw() {
      return swizzel<_T, 4>{data_[2], data_[0], data_[1], data_[3]};
    }
    inline swizzel<_T, 4> zxzx() {
      return swizzel<_T, 4>{data_[2], data_[0], data_[2], data_[0]};
    }
    inline swizzel<_T, 4> zxzy() {
      return swizzel<_T, 4>{data_[2], data_[0], data_[2], data_[1]};
    }
    inline swizzel<_T, 4> zxzz() {
      return swizzel<_T, 4>{data_[2], data_[0], data_[2], data_[2]};
    }
    inline swizzel<_T, 4> zxzw() {
      return swizzel<_T, 4>{data_[2], data_[0], data_[2], data_[3]};
    }
    inline swizzel<_T, 4> zxwx() {
      return swizzel<_T, 4>{data_[2], data_[0], data_[3], data_[0]};
    }
    inline swizzel<_T, 4> zxwy() {
      return swizzel<_T, 4>{data_[2], data_[0], data_[3], data_[1]};
    }
    inline swizzel<_T, 4> zxwz() {
      return swizzel<_T, 4>{data_[2], data_[0], data_[3], data_[2]};
    }
    inline swizzel<_T, 4> zxww() {
      return swizzel<_T, 4>{data_[2], data_[0], data_[3], data_[3]};
    }

    inline swizzel<_T, 4> zyxx() {
      return swizzel<_T, 4>{data_[2], data_[1], data_[0], data_[0]};
    }
    inline swizzel<_T, 4> zyxy() {
      return swizzel<_T, 4>{data_[2], data_[1], data_[0], data_[1]};
    }
    inline swizzel<_T, 4> zyxz() {
      return swizzel<_T, 4>{data_[2], data_[1], data_[0], data_[2]};
    }
    inline swizzel<_T, 4> zyxw() {
      return swizzel<_T, 4>{data_[2], data_[1], data_[0], data_[3]};
    }
    inline swizzel<_T, 4> zyyx() {
      return swizzel<_T, 4>{data_[2], data_[1], data_[1], data_[0]};
    }
    inline swizzel<_T, 4> zyyy() {
      return swizzel<_T, 4>{data_[2], data_[1], data_[1], data_[1]};
    }
    inline swizzel<_T, 4> zyyz() {
      return swizzel<_T, 4>{data_[2], data_[1], data_[1], data_[2]};
    }
    inline swizzel<_T, 4> zyyw() {
      return swizzel<_T, 4>{data_[2], data_[1], data_[1], data_[3]};
    }
    inline swizzel<_T, 4> zyzx() {
      return swizzel<_T, 4>{data_[2], data_[1], data_[2], data_[0]};
    }
    inline swizzel<_T, 4> zyzy() {
      return swizzel<_T, 4>{data_[2], data_[1], data_[2], data_[1]};
    }
    inline swizzel<_T, 4> zyzz() {
      return swizzel<_T, 4>{data_[2], data_[1], data_[2], data_[2]};
    }
    inline swizzel<_T, 4> zyzw() {
      return swizzel<_T, 4>{data_[2], data_[1], data_[2], data_[3]};
    }
    inline swizzel<_T, 4> zywx() {
      return swizzel<_T, 4>{data_[2], data_[1], data_[3], data_[0]};
    }
    inline swizzel<_T, 4> zywy() {
      return swizzel<_T, 4>{data_[2], data_[1], data_[3], data_[1]};
    }
    inline swizzel<_T, 4> zywz() {
      return swizzel<_T, 4>{data_[2], data_[1], data_[3], data_[2]};
    }
    inline swizzel<_T, 4> zyww() {
      return swizzel<_T, 4>{data_[2], data_[1], data_[3], data_[3]};
    }

    inline swizzel<_T, 4> zzxx() {
      return swizzel<_T, 4>{data_[2], data_[2], data_[0], data_[0]};
    }
    inline swizzel<_T, 4> zzxy() {
      return swizzel<_T, 4>{data_[2], data_[2], data_[0], data_[1]};
    }
    inline swizzel<_T, 4> zzxz() {
      return swizzel<_T, 4>{data_[2], data_[2], data_[0], data_[2]};
    }
    inline swizzel<_T, 4> zzxw() {
      return swizzel<_T, 4>{data_[2], data_[2], data_[0], data_[3]};
    }
    inline swizzel<_T, 4> zzyx() {
      return swizzel<_T, 4>{data_[2], data_[2], data_[1], data_[0]};
    }
    inline swizzel<_T, 4> zzyy() {
      return swizzel<_T, 4>{data_[2], data_[2], data_[1], data_[1]};
    }
    inline swizzel<_T, 4> zzyz() {
      return swizzel<_T, 4>{data_[2], data_[2], data_[1], data_[2]};
    }
    inline swizzel<_T, 4> zzyw() {
      return swizzel<_T, 4>{data_[2], data_[2], data_[1], data_[3]};
    }
    inline swizzel<_T, 4> zzzx() {
      return swizzel<_T, 4>{data_[2], data_[2], data_[2], data_[0]};
    }
    inline swizzel<_T, 4> zzzy() {
      return swizzel<_T, 4>{data_[2], data_[2], data_[2], data_[1]};
    }
    inline swizzel<_T, 4> zzzz() {
      return swizzel<_T, 4>{data_[2], data_[2], data_[2], data_[2]};
    }
    inline swizzel<_T, 4> zzzw() {
      return swizzel<_T, 4>{data_[2], data_[2], data_[2], data_[3]};
    }
    inline swizzel<_T, 4> zzwx() {
      return swizzel<_T, 4>{data_[2], data_[2], data_[3], data_[0]};
    }
    inline swizzel<_T, 4> zzwy() {
      return swizzel<_T, 4>{data_[2], data_[2], data_[3], data_[1]};
    }
    inline swizzel<_T, 4> zzwz() {
      return swizzel<_T, 4>{data_[2], data_[2], data_[3], data_[2]};
    }
    inline swizzel<_T, 4> zzww() {
      return swizzel<_T, 4>{data_[2], data_[2], data_[3], data_[3]};
    }

    inline swizzel<_T, 4> zwxx() {
      return swizzel<_T, 4>{data_[2], data_[3], data_[0], data_[0]};
    }
    inline swizzel<_T, 4> zwxy() {
      return swizzel<_T, 4>{data_[2], data_[3], data_[0], data_[1]};
    }
    inline swizzel<_T, 4> zwxz() {
      return swizzel<_T, 4>{data_[2], data_[3], data_[0], data_[2]};
    }
    inline swizzel<_T, 4> zwxw() {
      return swizzel<_T, 4>{data_[2], data_[3], data_[0], data_[3]};
    }
    inline swizzel<_T, 4> zwyx() {
      return swizzel<_T, 4>{data_[2], data_[3], data_[1], data_[0]};
    }
    inline swizzel<_T, 4> zwyy() {
      return swizzel<_T, 4>{data_[2], data_[3], data_[1], data_[1]};
    }
    inline swizzel<_T, 4> zwyz() {
      return swizzel<_T, 4>{data_[2], data_[3], data_[1], data_[2]};
    }
    inline swizzel<_T, 4> zwyw() {
      return swizzel<_T, 4>{data_[2], data_[3], data_[1], data_[3]};
    }
    inline swizzel<_T, 4> zwzx() {
      return swizzel<_T, 4>{data_[2], data_[3], data_[2], data_[0]};
    }
    inline swizzel<_T, 4> zwzy() {
      return swizzel<_T, 4>{data_[2], data_[3], data_[2], data_[1]};
    }
    inline swizzel<_T, 4> zwzz() {
      return swizzel<_T, 4>{data_[2], data_[3], data_[2], data_[2]};
    }
    inline swizzel<_T, 4> zwzw() {
      return swizzel<_T, 4>{data_[2], data_[3], data_[2], data_[3]};
    }
    inline swizzel<_T, 4> zwwx() {
      return swizzel<_T, 4>{data_[2], data_[3], data_[3], data_[0]};
    }
    inline swizzel<_T, 4> zwwy() {
      return swizzel<_T, 4>{data_[2], data_[3], data_[3], data_[1]};
    }
    inline swizzel<_T, 4> zwwz() {
      return swizzel<_T, 4>{data_[2], data_[3], data_[3], data_[2]};
    }
    inline swizzel<_T, 4> zwww() {
      return swizzel<_T, 4>{data_[2], data_[3], data_[3], data_[3]};
    }

    inline swizzel<_T, 4> wxxx() {
      return swizzel<_T, 4>{data_[3], data_[0], data_[0], data_[0]};
    }
    inline swizzel<_T, 4> wxxy() {
      return swizzel<_T, 4>{data_[3], data_[0], data_[0], data_[1]};
    }
    inline swizzel<_T, 4> wxxz() {
      return swizzel<_T, 4>{data_[3], data_[0], data_[0], data_[2]};
    }
    inline swizzel<_T, 4> wxxw() {
      return swizzel<_T, 4>{data_[3], data_[0], data_[0], data_[3]};
    }
    inline swizzel<_T, 4> wxyx() {
      return swizzel<_T, 4>{data_[3], data_[0], data_[1], data_[0]};
    }
    inline swizzel<_T, 4> wxyy() {
      return swizzel<_T, 4>{data_[3], data_[0], data_[1], data_[1]};
    }
    inline swizzel<_T, 4> wxyz() {
      return swizzel<_T, 4>{data_[3], data_[0], data_[1], data_[2]};
    }
    inline swizzel<_T, 4> wxyw() {
      return swizzel<_T, 4>{data_[3], data_[0], data_[1], data_[3]};
    }
    inline swizzel<_T, 4> wxzx() {
      return swizzel<_T, 4>{data_[3], data_[0], data_[2], data_[0]};
    }
    inline swizzel<_T, 4> wxzy() {
      return swizzel<_T, 4>{data_[3], data_[0], data_[2], data_[1]};
    }
    inline swizzel<_T, 4> wxzz() {
      return swizzel<_T, 4>{data_[3], data_[0], data_[2], data_[2]};
    }
    inline swizzel<_T, 4> wxzw() {
      return swizzel<_T, 4>{data_[3], data_[0], data_[2], data_[3]};
    }
    inline swizzel<_T, 4> wxwx() {
      return swizzel<_T, 4>{data_[3], data_[0], data_[3], data_[0]};
    }
    inline swizzel<_T, 4> wxwy() {
      return swizzel<_T, 4>{data_[3], data_[0], data_[3], data_[1]};
    }
    inline swizzel<_T, 4> wxwz() {
      return swizzel<_T, 4>{data_[3], data_[0], data_[3], data_[2]};
    }
    inline swizzel<_T, 4> wxww() {
      return swizzel<_T, 4>{data_[3], data_[0], data_[3], data_[3]};
    }

    inline swizzel<_T, 4> wyxx() {
      return swizzel<_T, 4>{data_[3], data_[1], data_[0], data_[0]};
    }
    inline swizzel<_T, 4> wyxy() {
      return swizzel<_T, 4>{data_[3], data_[1], data_[0], data_[1]};
    }
    inline swizzel<_T, 4> wyxz() {
      return swizzel<_T, 4>{data_[3], data_[1], data_[0], data_[2]};
    }
    inline swizzel<_T, 4> wyxw() {
      return swizzel<_T, 4>{data_[3], data_[1], data_[0], data_[3]};
    }
    inline swizzel<_T, 4> wyyx() {
      return swizzel<_T, 4>{data_[3], data_[1], data_[1], data_[0]};
    }
    inline swizzel<_T, 4> wyyy() {
      return swizzel<_T, 4>{data_[3], data_[1], data_[1], data_[1]};
    }
    inline swizzel<_T, 4> wyyz() {
      return swizzel<_T, 4>{data_[3], data_[1], data_[1], data_[2]};
    }
    inline swizzel<_T, 4> wyyw() {
      return swizzel<_T, 4>{data_[3], data_[1], data_[1], data_[3]};
    }
    inline swizzel<_T, 4> wyzx() {
      return swizzel<_T, 4>{data_[3], data_[1], data_[2], data_[0]};
    }
    inline swizzel<_T, 4> wyzy() {
      return swizzel<_T, 4>{data_[3], data_[1], data_[2], data_[1]};
    }
    inline swizzel<_T, 4> wyzz() {
      return swizzel<_T, 4>{data_[3], data_[1], data_[2], data_[2]};
    }
    inline swizzel<_T, 4> wyzw() {
      return swizzel<_T, 4>{data_[3], data_[1], data_[2], data_[3]};
    }
    inline swizzel<_T, 4> wywx() {
      return swizzel<_T, 4>{data_[3], data_[1], data_[3], data_[0]};
    }
    inline swizzel<_T, 4> wywy() {
      return swizzel<_T, 4>{data_[3], data_[1], data_[3], data_[1]};
    }
    inline swizzel<_T, 4> wywz() {
      return swizzel<_T, 4>{data_[3], data_[1], data_[3], data_[2]};
    }
    inline swizzel<_T, 4> wyww() {
      return swizzel<_T, 4>{data_[3], data_[1], data_[3], data_[3]};
    }

    inline swizzel<_T, 4> wzxx() {
      return swizzel<_T, 4>{data_[3], data_[2], data_[0], data_[0]};
    }
    inline swizzel<_T, 4> wzxy() {
      return swizzel<_T, 4>{data_[3], data_[2], data_[0], data_[1]};
    }
    inline swizzel<_T, 4> wzxz() {
      return swizzel<_T, 4>{data_[3], data_[2], data_[0], data_[2]};
    }
    inline swizzel<_T, 4> wzxw() {
      return swizzel<_T, 4>{data_[3], data_[2], data_[0], data_[3]};
    }
    inline swizzel<_T, 4> wzyx() {
      return swizzel<_T, 4>{data_[3], data_[2], data_[1], data_[0]};
    }
    inline swizzel<_T, 4> wzyy() {
      return swizzel<_T, 4>{data_[3], data_[2], data_[1], data_[1]};
    }
    inline swizzel<_T, 4> wzyz() {
      return swizzel<_T, 4>{data_[3], data_[2], data_[1], data_[2]};
    }
    inline swizzel<_T, 4> wzyw() {
      return swizzel<_T, 4>{data_[3], data_[2], data_[1], data_[3]};
    }
    inline swizzel<_T, 4> wzzx() {
      return swizzel<_T, 4>{data_[3], data_[2], data_[2], data_[0]};
    }
    inline swizzel<_T, 4> wzzy() {
      return swizzel<_T, 4>{data_[3], data_[2], data_[2], data_[1]};
    }
    inline swizzel<_T, 4> wzzz() {
      return swizzel<_T, 4>{data_[3], data_[2], data_[2], data_[2]};
    }
    inline swizzel<_T, 4> wzzw() {
      return swizzel<_T, 4>{data_[3], data_[2], data_[2], data_[3]};
    }
    inline swizzel<_T, 4> wzwx() {
      return swizzel<_T, 4>{data_[3], data_[2], data_[3], data_[0]};
    }
    inline swizzel<_T, 4> wzwy() {
      return swizzel<_T, 4>{data_[3], data_[2], data_[3], data_[1]};
    }
    inline swizzel<_T, 4> wzwz() {
      return swizzel<_T, 4>{data_[3], data_[2], data_[3], data_[2]};
    }
    inline swizzel<_T, 4> wzww() {
      return swizzel<_T, 4>{data_[3], data_[2], data_[3], data_[3]};
    }

    inline swizzel<_T, 4> wwxx() {
      return swizzel<_T, 4>{data_[3], data_[3], data_[0], data_[0]};
    }
    inline swizzel<_T, 4> wwxy() {
      return swizzel<_T, 4>{data_[3], data_[3], data_[0], data_[1]};
    }
    inline swizzel<_T, 4> wwxz() {
      return swizzel<_T, 4>{data_[3], data_[3], data_[0], data_[2]};
    }
    inline swizzel<_T, 4> wwxw() {
      return swizzel<_T, 4>{data_[3], data_[3], data_[0], data_[3]};
    }
    inline swizzel<_T, 4> wwyx() {
      return swizzel<_T, 4>{data_[3], data_[3], data_[1], data_[0]};
    }
    inline swizzel<_T, 4> wwyy() {
      return swizzel<_T, 4>{data_[3], data_[3], data_[1], data_[1]};
    }
    inline swizzel<_T, 4> wwyz() {
      return swizzel<_T, 4>{data_[3], data_[3], data_[1], data_[2]};
    }
    inline swizzel<_T, 4> wwyw() {
      return swizzel<_T, 4>{data_[3], data_[3], data_[1], data_[3]};
    }
    inline swizzel<_T, 4> wwzx() {
      return swizzel<_T, 4>{data_[3], data_[3], data_[2], data_[0]};
    }
    inline swizzel<_T, 4> wwzy() {
      return swizzel<_T, 4>{data_[3], data_[3], data_[2], data_[1]};
    }
    inline swizzel<_T, 4> wwzz() {
      return swizzel<_T, 4>{data_[3], data_[3], data_[2], data_[2]};
    }
    inline swizzel<_T, 4> wwzw() {
      return swizzel<_T, 4>{data_[3], data_[3], data_[2], data_[3]};
    }
    inline swizzel<_T, 4> wwwx() {
      return swizzel<_T, 4>{data_[3], data_[3], data_[3], data_[0]};
    }
    inline swizzel<_T, 4> wwwy() {
      return swizzel<_T, 4>{data_[3], data_[3], data_[3], data_[1]};
    }
    inline swizzel<_T, 4> wwwz() {
      return swizzel<_T, 4>{data_[3], data_[3], data_[3], data_[2]};
    }
    inline swizzel<_T, 4> wwww() {
      return swizzel<_T, 4>{data_[3], data_[3], data_[3], data_[3]};
    }

    std::array<std::shared_ptr<_T>, _N> data() { return data_; }

   protected:
    std::array<std::shared_ptr<_T>, _N> data_;
  };

  template <typename _T, std::size_t _N>
  class swizzel : public vec_base<_T, _N> {
   public:
    explicit swizzel(const std::initializer_list<std::shared_ptr<_T>>& init)
        : vec_base<_T, _N>() {
      std::size_t i = 0;
      for (auto it = init.begin(); it != init.end() && i < _N; ++it, ++i) {
        this->data_[i] = *it;
      }
    }
    explicit swizzel(const swizzel<_T, _N>& init) : vec_base<_T, _N>() {
      for (std::size_t i = 0; i < _N; ++i) {
        *this->data_[i] = init[i];
      }
    }
    inline swizzel<_T, _N>& operator=(const std::initializer_list<_T>& init) {
      std::size_t i = 0;
      for (auto it = init.begin(); it != init.end() && i < _N; ++it, ++i) {
        *this->data_[i] = *it;
      }
      return *this;
    }
    template <typename _U, std::size_t _M>
    inline typename std::enable_if<_M <= _N, swizzel<_T, _N>&>::type operator=(
        const vec<_U, _M>& vec) {
      for (std::size_t i = 0; i < std::min(_N, _M); ++i) {
        *this->data_[i] = _T(vec[i]);
      }
      return *this;
    }
    template <typename _U, std::size_t _M>
    inline typename std::enable_if<_M <= _N, swizzel<_T, _N>&>::type operator=(
        const swizzel<_U, _M>& vec) {
      for (std::size_t i = 0; i < std::min(_N, _M); ++i) {
        *this->data_[i] = _T(vec[i]);
      }
      return *this;
    }
  };

  template <typename _T, std::size_t _N>
  class vec : public vec_base<_T, _N> {
   public:
    template <typename _U, std::size_t _M>
    vec(const vec<_U, _M>& copy, typename std::enable_if<_M <= _N>::type* = 0)
        : vec_base<_T, _N>() {
      for (std::size_t i = 0; i < _M; ++i) {
        *this->data_[i] = copy[i];
      }
    }
    template <typename _U, std::size_t _M>
    vec(const swizzel<_U, _M>& copy,
        typename std::enable_if<_M <= _N>::type* = 0)
        : vec_base<_T, _N>() {
      for (std::size_t i = 0; i < _M; ++i) {
        *this->data_[i] = copy[i];
      }
    }
    vec(const std::initializer_list<_T>& init) : vec_base<_T, _N>() {
      std::size_t i = 0;
      for (auto it = init.begin(); it != init.end() && i < _N; ++it, ++i) {
        *this->data_[i] = *it;
      }
    }
    template <typename... _ARGS>
    vec(const _ARGS&... args) : vec_base<_T, _N>() {
      constructor<0>(args...);
    }

    template <typename _U, std::size_t _M>
    inline typename std::enable_if<_M <= _N, vec<_T, _N>&>::type operator=(
        const vec<_U, _M>& vec) {
      for (std::size_t i = 0; i < _N; ++i) {
        if (i < _M)
          *this->data_[i] = _T(vec.at(i));
        else
          *this->data_[i] = _T();
      }
      return *this;
    }
    vec<_T, _N>& operator=(const std::initializer_list<_T>& init) {
      std::size_t i = 0;
      for (auto it = init.begin(); it != init.end() && i < _N; ++it, ++i) {
        *this->data_[i] = _T(*it);
      }
      for (; i < _N; ++i) {
        *this->data_[i] = _T();
      }
      return *this;
    }
    template <typename... _ARGS>
    vec<_T, _N>& operator=(const _ARGS&... args) {
      constructor<0>(args...);
      return *this;
    }

   private:
    template <std::size_t _I, typename... _ARGS>
        typename std::enable_if <
        _I<_N, void>::type constructor(const _T& t, const _ARGS&... args) {
      *this->data_[_I] = t;
      constructor<_I + 1>(args...);
    }
    template <std::size_t _I, typename... _ARGS>
        typename std::enable_if <
        _I<_N && _I != 0, void>::type constructor(const _T& t) {
      *this->data_[_I] = t;
    }
    template <std::size_t _I, typename... _ARGS>
    typename std::enable_if<_I == 0, void>::type constructor(const _T& t) {
      for (uint32_t i = 0; i < _N; ++i) {
        *this->data_[i] = t;
      }
    }
  };
  template <typename _T, std::size_t _N>
  std::ostream& operator<<(std::ostream& out,
                           const vec_base<_T, _N>& vec_base) {
    out << '<';
    for (std::size_t i = 0; i < _N - 1; ++i) {
      out << vec_base[i] << ',';
    }
    out << vec_base[_N - 1] << '>';
    return out;
  }
  template <typename _T, std::size_t _N>
  inline bool operator==(const vec<_T, _N>& lhs, const vec<_T, _N>& rhs) {
    for (std::size_t i = 0; i < _N; ++i) {
      if (lhs[i] != rhs[i]) return false;
    }
    return true;
  }
  template <typename _T, std::size_t _N>
  inline bool operator!=(const vec<_T, _N>& lhs, const vec<_T, _N>& rhs) {
    return !(lhs == rhs);
  }

  template <typename _T, std::size_t _N>
  inline vec<_T, _N> operator+(const vec<_T, _N>& lhs, const _T& rhs) {
    vec<_T, _N> res;
    for (std:; size_t i = 0; i < _N; ++i) {
      res[i] = lhs[i] + rhs;
    }
    return res;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> operator+(const vec<_T, _N>& lhs, const vec<_T, _N>& rhs) {
    vec<_T, _N> res;
    for (std:; size_t i = 0; i < _N; ++i) {
      res[i] = lhs[i] + rhs[i];
    }
    return res;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> operator-(const vec<_T, _N>& lhs, const _T& rhs) {
    vec<_T, _N> res;
    for (std:; size_t i = 0; i < _N; ++i) {
      res[i] = lhs[i] - rhs;
    }
    return res;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> operator-(const vec<_T, _N>& lhs, const vec<_T, _N>& rhs) {
    vec<_T, _N> res;
    for (std:; size_t i = 0; i < _N; ++i) {
      res[i] = lhs[i] - rhs[i];
    }
    return res;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> operator*(const vec<_T, _N>& lhs, const _T& rhs) {
    vec<_T, _N> res;
    for (std:; size_t i = 0; i < _N; ++i) {
      res[i] = lhs[i] * rhs;
    }
    return res;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> operator*(const _T& lhs, const vec<_T, _N>& rhs) {
    vec<_T, _N> res;
    for (std:; size_t i = 0; i < _N; ++i) {
      res[i] = lhs * rhs[i];
    }
    return res;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> operator*(const vec<_T, _N>& lhs, const vec<_T, _N>& rhs) {
    vec<_T, _N> res;
    for (std:; size_t i = 0; i < _N; ++i) {
      res[i] = lhs[i] * rhs[i];
    }
    return res;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> operator/(const vec<_T, _N>& lhs, const _T& rhs) {
    vec<_T, _N> res;
    for (std:; size_t i = 0; i < _N; ++i) {
      res[i] = lhs[i] / rhs;
    }
    return res;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> operator/(const vec<_T, _N>& lhs, const vec<_T, _N>& rhs) {
    vec<_T, _N> res;
    for (std:; size_t i = 0; i < _N; ++i) {
      res[i] = lhs[i] / rhs[i];
    }
    return res;
  }

  template <typename _T, std::size_t _N>
  inline vec<_T, _N> component_op(const vec<_T, _N>& lhs,
                                  _T (*func)(const _T&)) {
    vec<_T, _N> ret;
    for (std::size_t i = 0; i < _N; ++i) {
      ret[i] = func(lhs[i]);
    }
    return ret;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> component_op(const vec<_T, _N>& lhs,
                                  const vec<_T, _N>& rhs,
                                  _T (*func)(const _T&, const _T&)) {
    vec<_T, _N> ret;
    for (std::size_t i = 0; i < _N; ++i) {
      ret[i] = func(lhs[i], rhs[i]);
    }
    return ret;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> component_op(const vec<_T, _N>& lhs, const _T& rhs,
                                  _T (*func)(const _T&, const _T&)) {
    vec<_T, _N> ret;
    for (std::size_t i = 0; i < _N; ++i) {
      ret[i] = func(lhs[i], rhs);
    }
    return ret;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> component_op(const _T& lhs, const vec<_T, _N>& rhs,
                                  _T (*func)(const _T&, const _T&)) {
    vec<_T, _N> ret;
    for (std::size_t i = 0; i < _N; ++i) {
      ret[i] = func(lhs, rhs[i]);
    }
    return ret;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> component_op(const vec<_T, _N>& x, const vec<_T, _N>& y,
                                  const vec<_T, _N>& z,
                                  _T (*func)(const _T&, const _T&, const _T&)) {
    vec<_T, _N> ret;
    for (std::size_t i = 0; i < _N; ++i) {
      ret[i] = func(x[i], y[i], z[i]);
    }
    return ret;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> component_op(const vec<_T, _N>& x, const vec<_T, _N>& y,
                                  const _T& z,
                                  _T (*func)(const _T&, const _T&, const _T&)) {
    vec<_T, _N> ret;
    for (std::size_t i = 0; i < _N; ++i) {
      ret[i] = func(x[i], y[i], z);
    }
    return ret;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> component_op(const vec<_T, _N>& x, const _T& y,
                                  const _T& z,
                                  _T (*func)(const _T&, const _T&, const _T&)) {
    vec<_T, _N> ret;
    for (std::size_t i = 0; i < _N; ++i) {
      ret[i] = func(x[i], y, z);
    }
    return ret;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> component_op(const _T& x, const _T& y,
                                  const vec<_T, _N>& z,
                                  _T (*func)(const _T&, const _T&, const _T&)) {
    vec<_T, _N> ret;
    for (std::size_t i = 0; i < _N; ++i) {
      ret[i] = func(x, y, z[i]);
    }
    return ret;
  }

  typedef vec<bool, 2> bvec2;
  typedef vec<bool, 3> bvec3;
  typedef vec<bool, 4> bvec4;
  typedef vec<bool, 8> bvec8;
  typedef vec<bool, 16> bvec16;
  typedef vec<int, 2> ivec2;
  typedef vec<int, 3> ivec3;
  typedef vec<int, 4> ivec4;
  typedef vec<int, 8> ivec8;
  typedef vec<int, 16> ivec16;
  typedef vec<float, 2> vec2;
  typedef vec<float, 3> vec3;
  typedef vec<float, 4> vec4;
  typedef vec<float, 8> vec8;
  typedef vec<float, 16> vec16;
}  // namespace math
}  // namespace specula

#endif  // SPECULA_MATH_VECTOR_HPP_
