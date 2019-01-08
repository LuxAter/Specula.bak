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

    inline const _T x() const { return *data_[0]; }
    inline const _T y() const { return *data_[1]; }
    inline const _T z() const { return *data_[2]; }
    inline const _T w() const { return *data_[3]; }

    inline const vec<_T, 2> xx() const {
      return vec<_T, 2>{*data_[0], *data_[0]};
    }
    inline const vec<_T, 2> xy() const {
      return vec<_T, 2>{*data_[0], *data_[1]};
    }
    inline const vec<_T, 2> xz() const {
      return vec<_T, 2>{*data_[0], *data_[2]};
    }
    inline const vec<_T, 2> xw() const {
      return vec<_T, 2>{*data_[0], *data_[3]};
    }
    inline const vec<_T, 2> yx() const {
      return vec<_T, 2>{*data_[1], *data_[0]};
    }
    inline const vec<_T, 2> yy() const {
      return vec<_T, 2>{*data_[1], *data_[1]};
    }
    inline const vec<_T, 2> yz() const {
      return vec<_T, 2>{*data_[1], *data_[2]};
    }
    inline const vec<_T, 2> yw() const {
      return vec<_T, 2>{*data_[1], *data_[3]};
    }
    inline const vec<_T, 2> zx() const {
      return vec<_T, 2>{*data_[2], *data_[0]};
    }
    inline const vec<_T, 2> zy() const {
      return vec<_T, 2>{*data_[2], *data_[1]};
    }
    inline const vec<_T, 2> zz() const {
      return vec<_T, 2>{*data_[2], *data_[2]};
    }
    inline const vec<_T, 2> zw() const {
      return vec<_T, 2>{*data_[2], *data_[3]};
    }
    inline const vec<_T, 2> wx() const {
      return vec<_T, 2>{*data_[3], *data_[0]};
    }
    inline const vec<_T, 2> wy() const {
      return vec<_T, 2>{*data_[3], *data_[1]};
    }
    inline const vec<_T, 2> wz() const {
      return vec<_T, 2>{*data_[3], *data_[2]};
    }
    inline const vec<_T, 2> ww() const {
      return vec<_T, 2>{*data_[3], *data_[3]};
    }

    inline const vec<_T, 3> xxx() const {
      return vec<_T, 3>{*data_[0], *data_[0], *data_[0]};
    }
    inline const vec<_T, 3> xxy() const {
      return vec<_T, 3>{*data_[0], *data_[0], *data_[1]};
    }
    inline const vec<_T, 3> xxz() const {
      return vec<_T, 3>{*data_[0], *data_[0], *data_[2]};
    }
    inline const vec<_T, 3> xxw() const {
      return vec<_T, 3>{*data_[0], *data_[0], *data_[3]};
    }
    inline const vec<_T, 3> xyx() const {
      return vec<_T, 3>{*data_[0], *data_[1], *data_[0]};
    }
    inline const vec<_T, 3> xyy() const {
      return vec<_T, 3>{*data_[0], *data_[1], *data_[1]};
    }
    inline const vec<_T, 3> xyz() const {
      return vec<_T, 3>{*data_[0], *data_[1], *data_[2]};
    }
    inline const vec<_T, 3> xyw() const {
      return vec<_T, 3>{*data_[0], *data_[1], *data_[3]};
    }
    inline const vec<_T, 3> xzx() const {
      return vec<_T, 3>{*data_[0], *data_[2], *data_[0]};
    }
    inline const vec<_T, 3> xzy() const {
      return vec<_T, 3>{*data_[0], *data_[2], *data_[1]};
    }
    inline const vec<_T, 3> xzz() const {
      return vec<_T, 3>{*data_[0], *data_[2], *data_[2]};
    }
    inline const vec<_T, 3> xzw() const {
      return vec<_T, 3>{*data_[0], *data_[2], *data_[3]};
    }
    inline const vec<_T, 3> xwx() const {
      return vec<_T, 3>{*data_[0], *data_[3], *data_[0]};
    }
    inline const vec<_T, 3> xwy() const {
      return vec<_T, 3>{*data_[0], *data_[3], *data_[1]};
    }
    inline const vec<_T, 3> xwz() const {
      return vec<_T, 3>{*data_[0], *data_[3], *data_[2]};
    }
    inline const vec<_T, 3> xww() const {
      return vec<_T, 3>{*data_[0], *data_[3], *data_[3]};
    }

    inline const vec<_T, 3> yxx() const {
      return vec<_T, 3>{*data_[1], *data_[0], *data_[0]};
    }
    inline const vec<_T, 3> yxy() const {
      return vec<_T, 3>{*data_[1], *data_[0], *data_[1]};
    }
    inline const vec<_T, 3> yxz() const {
      return vec<_T, 3>{*data_[1], *data_[0], *data_[2]};
    }
    inline const vec<_T, 3> yxw() const {
      return vec<_T, 3>{*data_[1], *data_[0], *data_[3]};
    }
    inline const vec<_T, 3> yyx() const {
      return vec<_T, 3>{*data_[1], *data_[1], *data_[0]};
    }
    inline const vec<_T, 3> yyy() const {
      return vec<_T, 3>{*data_[1], *data_[1], *data_[1]};
    }
    inline const vec<_T, 3> yyz() const {
      return vec<_T, 3>{*data_[1], *data_[1], *data_[2]};
    }
    inline const vec<_T, 3> yyw() const {
      return vec<_T, 3>{*data_[1], *data_[1], *data_[3]};
    }
    inline const vec<_T, 3> yzx() const {
      return vec<_T, 3>{*data_[1], *data_[2], *data_[0]};
    }
    inline const vec<_T, 3> yzy() const {
      return vec<_T, 3>{*data_[1], *data_[2], *data_[1]};
    }
    inline const vec<_T, 3> yzz() const {
      return vec<_T, 3>{*data_[1], *data_[2], *data_[2]};
    }
    inline const vec<_T, 3> yzw() const {
      return vec<_T, 3>{*data_[1], *data_[2], *data_[3]};
    }
    inline const vec<_T, 3> ywx() const {
      return vec<_T, 3>{*data_[1], *data_[3], *data_[0]};
    }
    inline const vec<_T, 3> ywy() const {
      return vec<_T, 3>{*data_[1], *data_[3], *data_[1]};
    }
    inline const vec<_T, 3> ywz() const {
      return vec<_T, 3>{*data_[1], *data_[3], *data_[2]};
    }
    inline const vec<_T, 3> yww() const {
      return vec<_T, 3>{*data_[1], *data_[3], *data_[3]};
    }

    inline const vec<_T, 3> zxx() const {
      return vec<_T, 3>{*data_[2], *data_[0], *data_[0]};
    }
    inline const vec<_T, 3> zxy() const {
      return vec<_T, 3>{*data_[2], *data_[0], *data_[1]};
    }
    inline const vec<_T, 3> zxz() const {
      return vec<_T, 3>{*data_[2], *data_[0], *data_[2]};
    }
    inline const vec<_T, 3> zxw() const {
      return vec<_T, 3>{*data_[2], *data_[0], *data_[3]};
    }
    inline const vec<_T, 3> zyx() const {
      return vec<_T, 3>{*data_[2], *data_[1], *data_[0]};
    }
    inline const vec<_T, 3> zyy() const {
      return vec<_T, 3>{*data_[2], *data_[1], *data_[1]};
    }
    inline const vec<_T, 3> zyz() const {
      return vec<_T, 3>{*data_[2], *data_[1], *data_[2]};
    }
    inline const vec<_T, 3> zyw() const {
      return vec<_T, 3>{*data_[2], *data_[1], *data_[3]};
    }
    inline const vec<_T, 3> zzx() const {
      return vec<_T, 3>{*data_[2], *data_[2], *data_[0]};
    }
    inline const vec<_T, 3> zzy() const {
      return vec<_T, 3>{*data_[2], *data_[2], *data_[1]};
    }
    inline const vec<_T, 3> zzz() const {
      return vec<_T, 3>{*data_[2], *data_[2], *data_[2]};
    }
    inline const vec<_T, 3> zzw() const {
      return vec<_T, 3>{*data_[2], *data_[2], *data_[3]};
    }
    inline const vec<_T, 3> zwx() const {
      return vec<_T, 3>{*data_[2], *data_[3], *data_[0]};
    }
    inline const vec<_T, 3> zwy() const {
      return vec<_T, 3>{*data_[2], *data_[3], *data_[1]};
    }
    inline const vec<_T, 3> zwz() const {
      return vec<_T, 3>{*data_[2], *data_[3], *data_[2]};
    }
    inline const vec<_T, 3> zww() const {
      return vec<_T, 3>{*data_[2], *data_[3], *data_[3]};
    }

    inline const vec<_T, 3> wxx() const {
      return vec<_T, 3>{*data_[3], *data_[0], *data_[0]};
    }
    inline const vec<_T, 3> wxy() const {
      return vec<_T, 3>{*data_[3], *data_[0], *data_[1]};
    }
    inline const vec<_T, 3> wxz() const {
      return vec<_T, 3>{*data_[3], *data_[0], *data_[2]};
    }
    inline const vec<_T, 3> wxw() const {
      return vec<_T, 3>{*data_[3], *data_[0], *data_[3]};
    }
    inline const vec<_T, 3> wyx() const {
      return vec<_T, 3>{*data_[3], *data_[1], *data_[0]};
    }
    inline const vec<_T, 3> wyy() const {
      return vec<_T, 3>{*data_[3], *data_[1], *data_[1]};
    }
    inline const vec<_T, 3> wyz() const {
      return vec<_T, 3>{*data_[3], *data_[1], *data_[2]};
    }
    inline const vec<_T, 3> wyw() const {
      return vec<_T, 3>{*data_[3], *data_[1], *data_[3]};
    }
    inline const vec<_T, 3> wzx() const {
      return vec<_T, 3>{*data_[3], *data_[2], *data_[0]};
    }
    inline const vec<_T, 3> wzy() const {
      return vec<_T, 3>{*data_[3], *data_[2], *data_[1]};
    }
    inline const vec<_T, 3> wzz() const {
      return vec<_T, 3>{*data_[3], *data_[2], *data_[2]};
    }
    inline const vec<_T, 3> wzw() const {
      return vec<_T, 3>{*data_[3], *data_[2], *data_[3]};
    }
    inline const vec<_T, 3> wwx() const {
      return vec<_T, 3>{*data_[3], *data_[3], *data_[0]};
    }
    inline const vec<_T, 3> wwy() const {
      return vec<_T, 3>{*data_[3], *data_[3], *data_[1]};
    }
    inline const vec<_T, 3> wwz() const {
      return vec<_T, 3>{*data_[3], *data_[3], *data_[2]};
    }
    inline const vec<_T, 3> www() const {
      return vec<_T, 3>{*data_[3], *data_[3], *data_[3]};
    }

    inline const vec<_T, 4> xxxx() const {
      return vec<_T, 4>{*data_[0], *data_[0], *data_[0], *data_[0]};
    }
    inline const vec<_T, 4> xxxy() const {
      return vec<_T, 4>{*data_[0], *data_[0], *data_[0], *data_[1]};
    }
    inline const vec<_T, 4> xxxz() const {
      return vec<_T, 4>{*data_[0], *data_[0], *data_[0], *data_[2]};
    }
    inline const vec<_T, 4> xxxw() const {
      return vec<_T, 4>{*data_[0], *data_[0], *data_[0], *data_[3]};
    }
    inline const vec<_T, 4> xxyx() const {
      return vec<_T, 4>{*data_[0], *data_[0], *data_[1], *data_[0]};
    }
    inline const vec<_T, 4> xxyy() const {
      return vec<_T, 4>{*data_[0], *data_[0], *data_[1], *data_[1]};
    }
    inline const vec<_T, 4> xxyz() const {
      return vec<_T, 4>{*data_[0], *data_[0], *data_[1], *data_[2]};
    }
    inline const vec<_T, 4> xxyw() const {
      return vec<_T, 4>{*data_[0], *data_[0], *data_[1], *data_[3]};
    }
    inline const vec<_T, 4> xxzx() const {
      return vec<_T, 4>{*data_[0], *data_[0], *data_[2], *data_[0]};
    }
    inline const vec<_T, 4> xxzy() const {
      return vec<_T, 4>{*data_[0], *data_[0], *data_[2], *data_[1]};
    }
    inline const vec<_T, 4> xxzz() const {
      return vec<_T, 4>{*data_[0], *data_[0], *data_[2], *data_[2]};
    }
    inline const vec<_T, 4> xxzw() const {
      return vec<_T, 4>{*data_[0], *data_[0], *data_[2], *data_[3]};
    }
    inline const vec<_T, 4> xxwx() const {
      return vec<_T, 4>{*data_[0], *data_[0], *data_[3], *data_[0]};
    }
    inline const vec<_T, 4> xxwy() const {
      return vec<_T, 4>{*data_[0], *data_[0], *data_[3], *data_[1]};
    }
    inline const vec<_T, 4> xxwz() const {
      return vec<_T, 4>{*data_[0], *data_[0], *data_[3], *data_[2]};
    }
    inline const vec<_T, 4> xxww() const {
      return vec<_T, 4>{*data_[0], *data_[0], *data_[3], *data_[3]};
    }

    inline const vec<_T, 4> xyxx() const {
      return vec<_T, 4>{*data_[0], *data_[1], *data_[0], *data_[0]};
    }
    inline const vec<_T, 4> xyxy() const {
      return vec<_T, 4>{*data_[0], *data_[1], *data_[0], *data_[1]};
    }
    inline const vec<_T, 4> xyxz() const {
      return vec<_T, 4>{*data_[0], *data_[1], *data_[0], *data_[2]};
    }
    inline const vec<_T, 4> xyxw() const {
      return vec<_T, 4>{*data_[0], *data_[1], *data_[0], *data_[3]};
    }
    inline const vec<_T, 4> xyyx() const {
      return vec<_T, 4>{*data_[0], *data_[1], *data_[1], *data_[0]};
    }
    inline const vec<_T, 4> xyyy() const {
      return vec<_T, 4>{*data_[0], *data_[1], *data_[1], *data_[1]};
    }
    inline const vec<_T, 4> xyyz() const {
      return vec<_T, 4>{*data_[0], *data_[1], *data_[1], *data_[2]};
    }
    inline const vec<_T, 4> xyyw() const {
      return vec<_T, 4>{*data_[0], *data_[1], *data_[1], *data_[3]};
    }
    inline const vec<_T, 4> xyzx() const {
      return vec<_T, 4>{*data_[0], *data_[1], *data_[2], *data_[0]};
    }
    inline const vec<_T, 4> xyzy() const {
      return vec<_T, 4>{*data_[0], *data_[1], *data_[2], *data_[1]};
    }
    inline const vec<_T, 4> xyzz() const {
      return vec<_T, 4>{*data_[0], *data_[1], *data_[2], *data_[2]};
    }
    inline const vec<_T, 4> xyzw() const {
      return vec<_T, 4>{*data_[0], *data_[1], *data_[2], *data_[3]};
    }
    inline const vec<_T, 4> xywx() const {
      return vec<_T, 4>{*data_[0], *data_[1], *data_[3], *data_[0]};
    }
    inline const vec<_T, 4> xywy() const {
      return vec<_T, 4>{*data_[0], *data_[1], *data_[3], *data_[1]};
    }
    inline const vec<_T, 4> xywz() const {
      return vec<_T, 4>{*data_[0], *data_[1], *data_[3], *data_[2]};
    }
    inline const vec<_T, 4> xyww() const {
      return vec<_T, 4>{*data_[0], *data_[1], *data_[3], *data_[3]};
    }

    inline const vec<_T, 4> xzxx() const {
      return vec<_T, 4>{*data_[0], *data_[2], *data_[0], *data_[0]};
    }
    inline const vec<_T, 4> xzxy() const {
      return vec<_T, 4>{*data_[0], *data_[2], *data_[0], *data_[1]};
    }
    inline const vec<_T, 4> xzxz() const {
      return vec<_T, 4>{*data_[0], *data_[2], *data_[0], *data_[2]};
    }
    inline const vec<_T, 4> xzxw() const {
      return vec<_T, 4>{*data_[0], *data_[2], *data_[0], *data_[3]};
    }
    inline const vec<_T, 4> xzyx() const {
      return vec<_T, 4>{*data_[0], *data_[2], *data_[1], *data_[0]};
    }
    inline const vec<_T, 4> xzyy() const {
      return vec<_T, 4>{*data_[0], *data_[2], *data_[1], *data_[1]};
    }
    inline const vec<_T, 4> xzyz() const {
      return vec<_T, 4>{*data_[0], *data_[2], *data_[1], *data_[2]};
    }
    inline const vec<_T, 4> xzyw() const {
      return vec<_T, 4>{*data_[0], *data_[2], *data_[1], *data_[3]};
    }
    inline const vec<_T, 4> xzzx() const {
      return vec<_T, 4>{*data_[0], *data_[2], *data_[2], *data_[0]};
    }
    inline const vec<_T, 4> xzzy() const {
      return vec<_T, 4>{*data_[0], *data_[2], *data_[2], *data_[1]};
    }
    inline const vec<_T, 4> xzzz() const {
      return vec<_T, 4>{*data_[0], *data_[2], *data_[2], *data_[2]};
    }
    inline const vec<_T, 4> xzzw() const {
      return vec<_T, 4>{*data_[0], *data_[2], *data_[2], *data_[3]};
    }
    inline const vec<_T, 4> xzwx() const {
      return vec<_T, 4>{*data_[0], *data_[2], *data_[3], *data_[0]};
    }
    inline const vec<_T, 4> xzwy() const {
      return vec<_T, 4>{*data_[0], *data_[2], *data_[3], *data_[1]};
    }
    inline const vec<_T, 4> xzwz() const {
      return vec<_T, 4>{*data_[0], *data_[2], *data_[3], *data_[2]};
    }
    inline const vec<_T, 4> xzww() const {
      return vec<_T, 4>{*data_[0], *data_[2], *data_[3], *data_[3]};
    }

    inline const vec<_T, 4> xwxx() const {
      return vec<_T, 4>{*data_[0], *data_[3], *data_[0], *data_[0]};
    }
    inline const vec<_T, 4> xwxy() const {
      return vec<_T, 4>{*data_[0], *data_[3], *data_[0], *data_[1]};
    }
    inline const vec<_T, 4> xwxz() const {
      return vec<_T, 4>{*data_[0], *data_[3], *data_[0], *data_[2]};
    }
    inline const vec<_T, 4> xwxw() const {
      return vec<_T, 4>{*data_[0], *data_[3], *data_[0], *data_[3]};
    }
    inline const vec<_T, 4> xwyx() const {
      return vec<_T, 4>{*data_[0], *data_[3], *data_[1], *data_[0]};
    }
    inline const vec<_T, 4> xwyy() const {
      return vec<_T, 4>{*data_[0], *data_[3], *data_[1], *data_[1]};
    }
    inline const vec<_T, 4> xwyz() const {
      return vec<_T, 4>{*data_[0], *data_[3], *data_[1], *data_[2]};
    }
    inline const vec<_T, 4> xwyw() const {
      return vec<_T, 4>{*data_[0], *data_[3], *data_[1], *data_[3]};
    }
    inline const vec<_T, 4> xwzx() const {
      return vec<_T, 4>{*data_[0], *data_[3], *data_[2], *data_[0]};
    }
    inline const vec<_T, 4> xwzy() const {
      return vec<_T, 4>{*data_[0], *data_[3], *data_[2], *data_[1]};
    }
    inline const vec<_T, 4> xwzz() const {
      return vec<_T, 4>{*data_[0], *data_[3], *data_[2], *data_[2]};
    }
    inline const vec<_T, 4> xwzw() const {
      return vec<_T, 4>{*data_[0], *data_[3], *data_[2], *data_[3]};
    }
    inline const vec<_T, 4> xwwx() const {
      return vec<_T, 4>{*data_[0], *data_[3], *data_[3], *data_[0]};
    }
    inline const vec<_T, 4> xwwy() const {
      return vec<_T, 4>{*data_[0], *data_[3], *data_[3], *data_[1]};
    }
    inline const vec<_T, 4> xwwz() const {
      return vec<_T, 4>{*data_[0], *data_[3], *data_[3], *data_[2]};
    }
    inline const vec<_T, 4> xwww() const {
      return vec<_T, 4>{*data_[0], *data_[3], *data_[3], *data_[3]};
    }

    inline const vec<_T, 4> yxxx() const {
      return vec<_T, 4>{*data_[1], *data_[0], *data_[0], *data_[0]};
    }
    inline const vec<_T, 4> yxxy() const {
      return vec<_T, 4>{*data_[1], *data_[0], *data_[0], *data_[1]};
    }
    inline const vec<_T, 4> yxxz() const {
      return vec<_T, 4>{*data_[1], *data_[0], *data_[0], *data_[2]};
    }
    inline const vec<_T, 4> yxxw() const {
      return vec<_T, 4>{*data_[1], *data_[0], *data_[0], *data_[3]};
    }
    inline const vec<_T, 4> yxyx() const {
      return vec<_T, 4>{*data_[1], *data_[0], *data_[1], *data_[0]};
    }
    inline const vec<_T, 4> yxyy() const {
      return vec<_T, 4>{*data_[1], *data_[0], *data_[1], *data_[1]};
    }
    inline const vec<_T, 4> yxyz() const {
      return vec<_T, 4>{*data_[1], *data_[0], *data_[1], *data_[2]};
    }
    inline const vec<_T, 4> yxyw() const {
      return vec<_T, 4>{*data_[1], *data_[0], *data_[1], *data_[3]};
    }
    inline const vec<_T, 4> yxzx() const {
      return vec<_T, 4>{*data_[1], *data_[0], *data_[2], *data_[0]};
    }
    inline const vec<_T, 4> yxzy() const {
      return vec<_T, 4>{*data_[1], *data_[0], *data_[2], *data_[1]};
    }
    inline const vec<_T, 4> yxzz() const {
      return vec<_T, 4>{*data_[1], *data_[0], *data_[2], *data_[2]};
    }
    inline const vec<_T, 4> yxzw() const {
      return vec<_T, 4>{*data_[1], *data_[0], *data_[2], *data_[3]};
    }
    inline const vec<_T, 4> yxwx() const {
      return vec<_T, 4>{*data_[1], *data_[0], *data_[3], *data_[0]};
    }
    inline const vec<_T, 4> yxwy() const {
      return vec<_T, 4>{*data_[1], *data_[0], *data_[3], *data_[1]};
    }
    inline const vec<_T, 4> yxwz() const {
      return vec<_T, 4>{*data_[1], *data_[0], *data_[3], *data_[2]};
    }
    inline const vec<_T, 4> yxww() const {
      return vec<_T, 4>{*data_[1], *data_[0], *data_[3], *data_[3]};
    }

    inline const vec<_T, 4> yyxx() const {
      return vec<_T, 4>{*data_[1], *data_[1], *data_[0], *data_[0]};
    }
    inline const vec<_T, 4> yyxy() const {
      return vec<_T, 4>{*data_[1], *data_[1], *data_[0], *data_[1]};
    }
    inline const vec<_T, 4> yyxz() const {
      return vec<_T, 4>{*data_[1], *data_[1], *data_[0], *data_[2]};
    }
    inline const vec<_T, 4> yyxw() const {
      return vec<_T, 4>{*data_[1], *data_[1], *data_[0], *data_[3]};
    }
    inline const vec<_T, 4> yyyx() const {
      return vec<_T, 4>{*data_[1], *data_[1], *data_[1], *data_[0]};
    }
    inline const vec<_T, 4> yyyy() const {
      return vec<_T, 4>{*data_[1], *data_[1], *data_[1], *data_[1]};
    }
    inline const vec<_T, 4> yyyz() const {
      return vec<_T, 4>{*data_[1], *data_[1], *data_[1], *data_[2]};
    }
    inline const vec<_T, 4> yyyw() const {
      return vec<_T, 4>{*data_[1], *data_[1], *data_[1], *data_[3]};
    }
    inline const vec<_T, 4> yyzx() const {
      return vec<_T, 4>{*data_[1], *data_[1], *data_[2], *data_[0]};
    }
    inline const vec<_T, 4> yyzy() const {
      return vec<_T, 4>{*data_[1], *data_[1], *data_[2], *data_[1]};
    }
    inline const vec<_T, 4> yyzz() const {
      return vec<_T, 4>{*data_[1], *data_[1], *data_[2], *data_[2]};
    }
    inline const vec<_T, 4> yyzw() const {
      return vec<_T, 4>{*data_[1], *data_[1], *data_[2], *data_[3]};
    }
    inline const vec<_T, 4> yywx() const {
      return vec<_T, 4>{*data_[1], *data_[1], *data_[3], *data_[0]};
    }
    inline const vec<_T, 4> yywy() const {
      return vec<_T, 4>{*data_[1], *data_[1], *data_[3], *data_[1]};
    }
    inline const vec<_T, 4> yywz() const {
      return vec<_T, 4>{*data_[1], *data_[1], *data_[3], *data_[2]};
    }
    inline const vec<_T, 4> yyww() const {
      return vec<_T, 4>{*data_[1], *data_[1], *data_[3], *data_[3]};
    }

    inline const vec<_T, 4> yzxx() const {
      return vec<_T, 4>{*data_[1], *data_[2], *data_[0], *data_[0]};
    }
    inline const vec<_T, 4> yzxy() const {
      return vec<_T, 4>{*data_[1], *data_[2], *data_[0], *data_[1]};
    }
    inline const vec<_T, 4> yzxz() const {
      return vec<_T, 4>{*data_[1], *data_[2], *data_[0], *data_[2]};
    }
    inline const vec<_T, 4> yzxw() const {
      return vec<_T, 4>{*data_[1], *data_[2], *data_[0], *data_[3]};
    }
    inline const vec<_T, 4> yzyx() const {
      return vec<_T, 4>{*data_[1], *data_[2], *data_[1], *data_[0]};
    }
    inline const vec<_T, 4> yzyy() const {
      return vec<_T, 4>{*data_[1], *data_[2], *data_[1], *data_[1]};
    }
    inline const vec<_T, 4> yzyz() const {
      return vec<_T, 4>{*data_[1], *data_[2], *data_[1], *data_[2]};
    }
    inline const vec<_T, 4> yzyw() const {
      return vec<_T, 4>{*data_[1], *data_[2], *data_[1], *data_[3]};
    }
    inline const vec<_T, 4> yzzx() const {
      return vec<_T, 4>{*data_[1], *data_[2], *data_[2], *data_[0]};
    }
    inline const vec<_T, 4> yzzy() const {
      return vec<_T, 4>{*data_[1], *data_[2], *data_[2], *data_[1]};
    }
    inline const vec<_T, 4> yzzz() const {
      return vec<_T, 4>{*data_[1], *data_[2], *data_[2], *data_[2]};
    }
    inline const vec<_T, 4> yzzw() const {
      return vec<_T, 4>{*data_[1], *data_[2], *data_[2], *data_[3]};
    }
    inline const vec<_T, 4> yzwx() const {
      return vec<_T, 4>{*data_[1], *data_[2], *data_[3], *data_[0]};
    }
    inline const vec<_T, 4> yzwy() const {
      return vec<_T, 4>{*data_[1], *data_[2], *data_[3], *data_[1]};
    }
    inline const vec<_T, 4> yzwz() const {
      return vec<_T, 4>{*data_[1], *data_[2], *data_[3], *data_[2]};
    }
    inline const vec<_T, 4> yzww() const {
      return vec<_T, 4>{*data_[1], *data_[2], *data_[3], *data_[3]};
    }

    inline const vec<_T, 4> ywxx() const {
      return vec<_T, 4>{*data_[1], *data_[3], *data_[0], *data_[0]};
    }
    inline const vec<_T, 4> ywxy() const {
      return vec<_T, 4>{*data_[1], *data_[3], *data_[0], *data_[1]};
    }
    inline const vec<_T, 4> ywxz() const {
      return vec<_T, 4>{*data_[1], *data_[3], *data_[0], *data_[2]};
    }
    inline const vec<_T, 4> ywxw() const {
      return vec<_T, 4>{*data_[1], *data_[3], *data_[0], *data_[3]};
    }
    inline const vec<_T, 4> ywyx() const {
      return vec<_T, 4>{*data_[1], *data_[3], *data_[1], *data_[0]};
    }
    inline const vec<_T, 4> ywyy() const {
      return vec<_T, 4>{*data_[1], *data_[3], *data_[1], *data_[1]};
    }
    inline const vec<_T, 4> ywyz() const {
      return vec<_T, 4>{*data_[1], *data_[3], *data_[1], *data_[2]};
    }
    inline const vec<_T, 4> ywyw() const {
      return vec<_T, 4>{*data_[1], *data_[3], *data_[1], *data_[3]};
    }
    inline const vec<_T, 4> ywzx() const {
      return vec<_T, 4>{*data_[1], *data_[3], *data_[2], *data_[0]};
    }
    inline const vec<_T, 4> ywzy() const {
      return vec<_T, 4>{*data_[1], *data_[3], *data_[2], *data_[1]};
    }
    inline const vec<_T, 4> ywzz() const {
      return vec<_T, 4>{*data_[1], *data_[3], *data_[2], *data_[2]};
    }
    inline const vec<_T, 4> ywzw() const {
      return vec<_T, 4>{*data_[1], *data_[3], *data_[2], *data_[3]};
    }
    inline const vec<_T, 4> ywwx() const {
      return vec<_T, 4>{*data_[1], *data_[3], *data_[3], *data_[0]};
    }
    inline const vec<_T, 4> ywwy() const {
      return vec<_T, 4>{*data_[1], *data_[3], *data_[3], *data_[1]};
    }
    inline const vec<_T, 4> ywwz() const {
      return vec<_T, 4>{*data_[1], *data_[3], *data_[3], *data_[2]};
    }
    inline const vec<_T, 4> ywww() const {
      return vec<_T, 4>{*data_[1], *data_[3], *data_[3], *data_[3]};
    }

    inline const vec<_T, 4> zxxx() const {
      return vec<_T, 4>{*data_[2], *data_[0], *data_[0], *data_[0]};
    }
    inline const vec<_T, 4> zxxy() const {
      return vec<_T, 4>{*data_[2], *data_[0], *data_[0], *data_[1]};
    }
    inline const vec<_T, 4> zxxz() const {
      return vec<_T, 4>{*data_[2], *data_[0], *data_[0], *data_[2]};
    }
    inline const vec<_T, 4> zxxw() const {
      return vec<_T, 4>{*data_[2], *data_[0], *data_[0], *data_[3]};
    }
    inline const vec<_T, 4> zxyx() const {
      return vec<_T, 4>{*data_[2], *data_[0], *data_[1], *data_[0]};
    }
    inline const vec<_T, 4> zxyy() const {
      return vec<_T, 4>{*data_[2], *data_[0], *data_[1], *data_[1]};
    }
    inline const vec<_T, 4> zxyz() const {
      return vec<_T, 4>{*data_[2], *data_[0], *data_[1], *data_[2]};
    }
    inline const vec<_T, 4> zxyw() const {
      return vec<_T, 4>{*data_[2], *data_[0], *data_[1], *data_[3]};
    }
    inline const vec<_T, 4> zxzx() const {
      return vec<_T, 4>{*data_[2], *data_[0], *data_[2], *data_[0]};
    }
    inline const vec<_T, 4> zxzy() const {
      return vec<_T, 4>{*data_[2], *data_[0], *data_[2], *data_[1]};
    }
    inline const vec<_T, 4> zxzz() const {
      return vec<_T, 4>{*data_[2], *data_[0], *data_[2], *data_[2]};
    }
    inline const vec<_T, 4> zxzw() const {
      return vec<_T, 4>{*data_[2], *data_[0], *data_[2], *data_[3]};
    }
    inline const vec<_T, 4> zxwx() const {
      return vec<_T, 4>{*data_[2], *data_[0], *data_[3], *data_[0]};
    }
    inline const vec<_T, 4> zxwy() const {
      return vec<_T, 4>{*data_[2], *data_[0], *data_[3], *data_[1]};
    }
    inline const vec<_T, 4> zxwz() const {
      return vec<_T, 4>{*data_[2], *data_[0], *data_[3], *data_[2]};
    }
    inline const vec<_T, 4> zxww() const {
      return vec<_T, 4>{*data_[2], *data_[0], *data_[3], *data_[3]};
    }

    inline const vec<_T, 4> zyxx() const {
      return vec<_T, 4>{*data_[2], *data_[1], *data_[0], *data_[0]};
    }
    inline const vec<_T, 4> zyxy() const {
      return vec<_T, 4>{*data_[2], *data_[1], *data_[0], *data_[1]};
    }
    inline const vec<_T, 4> zyxz() const {
      return vec<_T, 4>{*data_[2], *data_[1], *data_[0], *data_[2]};
    }
    inline const vec<_T, 4> zyxw() const {
      return vec<_T, 4>{*data_[2], *data_[1], *data_[0], *data_[3]};
    }
    inline const vec<_T, 4> zyyx() const {
      return vec<_T, 4>{*data_[2], *data_[1], *data_[1], *data_[0]};
    }
    inline const vec<_T, 4> zyyy() const {
      return vec<_T, 4>{*data_[2], *data_[1], *data_[1], *data_[1]};
    }
    inline const vec<_T, 4> zyyz() const {
      return vec<_T, 4>{*data_[2], *data_[1], *data_[1], *data_[2]};
    }
    inline const vec<_T, 4> zyyw() const {
      return vec<_T, 4>{*data_[2], *data_[1], *data_[1], *data_[3]};
    }
    inline const vec<_T, 4> zyzx() const {
      return vec<_T, 4>{*data_[2], *data_[1], *data_[2], *data_[0]};
    }
    inline const vec<_T, 4> zyzy() const {
      return vec<_T, 4>{*data_[2], *data_[1], *data_[2], *data_[1]};
    }
    inline const vec<_T, 4> zyzz() const {
      return vec<_T, 4>{*data_[2], *data_[1], *data_[2], *data_[2]};
    }
    inline const vec<_T, 4> zyzw() const {
      return vec<_T, 4>{*data_[2], *data_[1], *data_[2], *data_[3]};
    }
    inline const vec<_T, 4> zywx() const {
      return vec<_T, 4>{*data_[2], *data_[1], *data_[3], *data_[0]};
    }
    inline const vec<_T, 4> zywy() const {
      return vec<_T, 4>{*data_[2], *data_[1], *data_[3], *data_[1]};
    }
    inline const vec<_T, 4> zywz() const {
      return vec<_T, 4>{*data_[2], *data_[1], *data_[3], *data_[2]};
    }
    inline const vec<_T, 4> zyww() const {
      return vec<_T, 4>{*data_[2], *data_[1], *data_[3], *data_[3]};
    }

    inline const vec<_T, 4> zzxx() const {
      return vec<_T, 4>{*data_[2], *data_[2], *data_[0], *data_[0]};
    }
    inline const vec<_T, 4> zzxy() const {
      return vec<_T, 4>{*data_[2], *data_[2], *data_[0], *data_[1]};
    }
    inline const vec<_T, 4> zzxz() const {
      return vec<_T, 4>{*data_[2], *data_[2], *data_[0], *data_[2]};
    }
    inline const vec<_T, 4> zzxw() const {
      return vec<_T, 4>{*data_[2], *data_[2], *data_[0], *data_[3]};
    }
    inline const vec<_T, 4> zzyx() const {
      return vec<_T, 4>{*data_[2], *data_[2], *data_[1], *data_[0]};
    }
    inline const vec<_T, 4> zzyy() const {
      return vec<_T, 4>{*data_[2], *data_[2], *data_[1], *data_[1]};
    }
    inline const vec<_T, 4> zzyz() const {
      return vec<_T, 4>{*data_[2], *data_[2], *data_[1], *data_[2]};
    }
    inline const vec<_T, 4> zzyw() const {
      return vec<_T, 4>{*data_[2], *data_[2], *data_[1], *data_[3]};
    }
    inline const vec<_T, 4> zzzx() const {
      return vec<_T, 4>{*data_[2], *data_[2], *data_[2], *data_[0]};
    }
    inline const vec<_T, 4> zzzy() const {
      return vec<_T, 4>{*data_[2], *data_[2], *data_[2], *data_[1]};
    }
    inline const vec<_T, 4> zzzz() const {
      return vec<_T, 4>{*data_[2], *data_[2], *data_[2], *data_[2]};
    }
    inline const vec<_T, 4> zzzw() const {
      return vec<_T, 4>{*data_[2], *data_[2], *data_[2], *data_[3]};
    }
    inline const vec<_T, 4> zzwx() const {
      return vec<_T, 4>{*data_[2], *data_[2], *data_[3], *data_[0]};
    }
    inline const vec<_T, 4> zzwy() const {
      return vec<_T, 4>{*data_[2], *data_[2], *data_[3], *data_[1]};
    }
    inline const vec<_T, 4> zzwz() const {
      return vec<_T, 4>{*data_[2], *data_[2], *data_[3], *data_[2]};
    }
    inline const vec<_T, 4> zzww() const {
      return vec<_T, 4>{*data_[2], *data_[2], *data_[3], *data_[3]};
    }

    inline const vec<_T, 4> zwxx() const {
      return vec<_T, 4>{*data_[2], *data_[3], *data_[0], *data_[0]};
    }
    inline const vec<_T, 4> zwxy() const {
      return vec<_T, 4>{*data_[2], *data_[3], *data_[0], *data_[1]};
    }
    inline const vec<_T, 4> zwxz() const {
      return vec<_T, 4>{*data_[2], *data_[3], *data_[0], *data_[2]};
    }
    inline const vec<_T, 4> zwxw() const {
      return vec<_T, 4>{*data_[2], *data_[3], *data_[0], *data_[3]};
    }
    inline const vec<_T, 4> zwyx() const {
      return vec<_T, 4>{*data_[2], *data_[3], *data_[1], *data_[0]};
    }
    inline const vec<_T, 4> zwyy() const {
      return vec<_T, 4>{*data_[2], *data_[3], *data_[1], *data_[1]};
    }
    inline const vec<_T, 4> zwyz() const {
      return vec<_T, 4>{*data_[2], *data_[3], *data_[1], *data_[2]};
    }
    inline const vec<_T, 4> zwyw() const {
      return vec<_T, 4>{*data_[2], *data_[3], *data_[1], *data_[3]};
    }
    inline const vec<_T, 4> zwzx() const {
      return vec<_T, 4>{*data_[2], *data_[3], *data_[2], *data_[0]};
    }
    inline const vec<_T, 4> zwzy() const {
      return vec<_T, 4>{*data_[2], *data_[3], *data_[2], *data_[1]};
    }
    inline const vec<_T, 4> zwzz() const {
      return vec<_T, 4>{*data_[2], *data_[3], *data_[2], *data_[2]};
    }
    inline const vec<_T, 4> zwzw() const {
      return vec<_T, 4>{*data_[2], *data_[3], *data_[2], *data_[3]};
    }
    inline const vec<_T, 4> zwwx() const {
      return vec<_T, 4>{*data_[2], *data_[3], *data_[3], *data_[0]};
    }
    inline const vec<_T, 4> zwwy() const {
      return vec<_T, 4>{*data_[2], *data_[3], *data_[3], *data_[1]};
    }
    inline const vec<_T, 4> zwwz() const {
      return vec<_T, 4>{*data_[2], *data_[3], *data_[3], *data_[2]};
    }
    inline const vec<_T, 4> zwww() const {
      return vec<_T, 4>{*data_[2], *data_[3], *data_[3], *data_[3]};
    }

    inline const vec<_T, 4> wxxx() const {
      return vec<_T, 4>{*data_[3], *data_[0], *data_[0], *data_[0]};
    }
    inline const vec<_T, 4> wxxy() const {
      return vec<_T, 4>{*data_[3], *data_[0], *data_[0], *data_[1]};
    }
    inline const vec<_T, 4> wxxz() const {
      return vec<_T, 4>{*data_[3], *data_[0], *data_[0], *data_[2]};
    }
    inline const vec<_T, 4> wxxw() const {
      return vec<_T, 4>{*data_[3], *data_[0], *data_[0], *data_[3]};
    }
    inline const vec<_T, 4> wxyx() const {
      return vec<_T, 4>{*data_[3], *data_[0], *data_[1], *data_[0]};
    }
    inline const vec<_T, 4> wxyy() const {
      return vec<_T, 4>{*data_[3], *data_[0], *data_[1], *data_[1]};
    }
    inline const vec<_T, 4> wxyz() const {
      return vec<_T, 4>{*data_[3], *data_[0], *data_[1], *data_[2]};
    }
    inline const vec<_T, 4> wxyw() const {
      return vec<_T, 4>{*data_[3], *data_[0], *data_[1], *data_[3]};
    }
    inline const vec<_T, 4> wxzx() const {
      return vec<_T, 4>{*data_[3], *data_[0], *data_[2], *data_[0]};
    }
    inline const vec<_T, 4> wxzy() const {
      return vec<_T, 4>{*data_[3], *data_[0], *data_[2], *data_[1]};
    }
    inline const vec<_T, 4> wxzz() const {
      return vec<_T, 4>{*data_[3], *data_[0], *data_[2], *data_[2]};
    }
    inline const vec<_T, 4> wxzw() const {
      return vec<_T, 4>{*data_[3], *data_[0], *data_[2], *data_[3]};
    }
    inline const vec<_T, 4> wxwx() const {
      return vec<_T, 4>{*data_[3], *data_[0], *data_[3], *data_[0]};
    }
    inline const vec<_T, 4> wxwy() const {
      return vec<_T, 4>{*data_[3], *data_[0], *data_[3], *data_[1]};
    }
    inline const vec<_T, 4> wxwz() const {
      return vec<_T, 4>{*data_[3], *data_[0], *data_[3], *data_[2]};
    }
    inline const vec<_T, 4> wxww() const {
      return vec<_T, 4>{*data_[3], *data_[0], *data_[3], *data_[3]};
    }

    inline const vec<_T, 4> wyxx() const {
      return vec<_T, 4>{*data_[3], *data_[1], *data_[0], *data_[0]};
    }
    inline const vec<_T, 4> wyxy() const {
      return vec<_T, 4>{*data_[3], *data_[1], *data_[0], *data_[1]};
    }
    inline const vec<_T, 4> wyxz() const {
      return vec<_T, 4>{*data_[3], *data_[1], *data_[0], *data_[2]};
    }
    inline const vec<_T, 4> wyxw() const {
      return vec<_T, 4>{*data_[3], *data_[1], *data_[0], *data_[3]};
    }
    inline const vec<_T, 4> wyyx() const {
      return vec<_T, 4>{*data_[3], *data_[1], *data_[1], *data_[0]};
    }
    inline const vec<_T, 4> wyyy() const {
      return vec<_T, 4>{*data_[3], *data_[1], *data_[1], *data_[1]};
    }
    inline const vec<_T, 4> wyyz() const {
      return vec<_T, 4>{*data_[3], *data_[1], *data_[1], *data_[2]};
    }
    inline const vec<_T, 4> wyyw() const {
      return vec<_T, 4>{*data_[3], *data_[1], *data_[1], *data_[3]};
    }
    inline const vec<_T, 4> wyzx() const {
      return vec<_T, 4>{*data_[3], *data_[1], *data_[2], *data_[0]};
    }
    inline const vec<_T, 4> wyzy() const {
      return vec<_T, 4>{*data_[3], *data_[1], *data_[2], *data_[1]};
    }
    inline const vec<_T, 4> wyzz() const {
      return vec<_T, 4>{*data_[3], *data_[1], *data_[2], *data_[2]};
    }
    inline const vec<_T, 4> wyzw() const {
      return vec<_T, 4>{*data_[3], *data_[1], *data_[2], *data_[3]};
    }
    inline const vec<_T, 4> wywx() const {
      return vec<_T, 4>{*data_[3], *data_[1], *data_[3], *data_[0]};
    }
    inline const vec<_T, 4> wywy() const {
      return vec<_T, 4>{*data_[3], *data_[1], *data_[3], *data_[1]};
    }
    inline const vec<_T, 4> wywz() const {
      return vec<_T, 4>{*data_[3], *data_[1], *data_[3], *data_[2]};
    }
    inline const vec<_T, 4> wyww() const {
      return vec<_T, 4>{*data_[3], *data_[1], *data_[3], *data_[3]};
    }

    inline const vec<_T, 4> wzxx() const {
      return vec<_T, 4>{*data_[3], *data_[2], *data_[0], *data_[0]};
    }
    inline const vec<_T, 4> wzxy() const {
      return vec<_T, 4>{*data_[3], *data_[2], *data_[0], *data_[1]};
    }
    inline const vec<_T, 4> wzxz() const {
      return vec<_T, 4>{*data_[3], *data_[2], *data_[0], *data_[2]};
    }
    inline const vec<_T, 4> wzxw() const {
      return vec<_T, 4>{*data_[3], *data_[2], *data_[0], *data_[3]};
    }
    inline const vec<_T, 4> wzyx() const {
      return vec<_T, 4>{*data_[3], *data_[2], *data_[1], *data_[0]};
    }
    inline const vec<_T, 4> wzyy() const {
      return vec<_T, 4>{*data_[3], *data_[2], *data_[1], *data_[1]};
    }
    inline const vec<_T, 4> wzyz() const {
      return vec<_T, 4>{*data_[3], *data_[2], *data_[1], *data_[2]};
    }
    inline const vec<_T, 4> wzyw() const {
      return vec<_T, 4>{*data_[3], *data_[2], *data_[1], *data_[3]};
    }
    inline const vec<_T, 4> wzzx() const {
      return vec<_T, 4>{*data_[3], *data_[2], *data_[2], *data_[0]};
    }
    inline const vec<_T, 4> wzzy() const {
      return vec<_T, 4>{*data_[3], *data_[2], *data_[2], *data_[1]};
    }
    inline const vec<_T, 4> wzzz() const {
      return vec<_T, 4>{*data_[3], *data_[2], *data_[2], *data_[2]};
    }
    inline const vec<_T, 4> wzzw() const {
      return vec<_T, 4>{*data_[3], *data_[2], *data_[2], *data_[3]};
    }
    inline const vec<_T, 4> wzwx() const {
      return vec<_T, 4>{*data_[3], *data_[2], *data_[3], *data_[0]};
    }
    inline const vec<_T, 4> wzwy() const {
      return vec<_T, 4>{*data_[3], *data_[2], *data_[3], *data_[1]};
    }
    inline const vec<_T, 4> wzwz() const {
      return vec<_T, 4>{*data_[3], *data_[2], *data_[3], *data_[2]};
    }
    inline const vec<_T, 4> wzww() const {
      return vec<_T, 4>{*data_[3], *data_[2], *data_[3], *data_[3]};
    }

    inline const vec<_T, 4> wwxx() const {
      return vec<_T, 4>{*data_[3], *data_[3], *data_[0], *data_[0]};
    }
    inline const vec<_T, 4> wwxy() const {
      return vec<_T, 4>{*data_[3], *data_[3], *data_[0], *data_[1]};
    }
    inline const vec<_T, 4> wwxz() const {
      return vec<_T, 4>{*data_[3], *data_[3], *data_[0], *data_[2]};
    }
    inline const vec<_T, 4> wwxw() const {
      return vec<_T, 4>{*data_[3], *data_[3], *data_[0], *data_[3]};
    }
    inline const vec<_T, 4> wwyx() const {
      return vec<_T, 4>{*data_[3], *data_[3], *data_[1], *data_[0]};
    }
    inline const vec<_T, 4> wwyy() const {
      return vec<_T, 4>{*data_[3], *data_[3], *data_[1], *data_[1]};
    }
    inline const vec<_T, 4> wwyz() const {
      return vec<_T, 4>{*data_[3], *data_[3], *data_[1], *data_[2]};
    }
    inline const vec<_T, 4> wwyw() const {
      return vec<_T, 4>{*data_[3], *data_[3], *data_[1], *data_[3]};
    }
    inline const vec<_T, 4> wwzx() const {
      return vec<_T, 4>{*data_[3], *data_[3], *data_[2], *data_[0]};
    }
    inline const vec<_T, 4> wwzy() const {
      return vec<_T, 4>{*data_[3], *data_[3], *data_[2], *data_[1]};
    }
    inline const vec<_T, 4> wwzz() const {
      return vec<_T, 4>{*data_[3], *data_[3], *data_[2], *data_[2]};
    }
    inline const vec<_T, 4> wwzw() const {
      return vec<_T, 4>{*data_[3], *data_[3], *data_[2], *data_[3]};
    }
    inline const vec<_T, 4> wwwx() const {
      return vec<_T, 4>{*data_[3], *data_[3], *data_[3], *data_[0]};
    }
    inline const vec<_T, 4> wwwy() const {
      return vec<_T, 4>{*data_[3], *data_[3], *data_[3], *data_[1]};
    }
    inline const vec<_T, 4> wwwz() const {
      return vec<_T, 4>{*data_[3], *data_[3], *data_[3], *data_[2]};
    }
    inline const vec<_T, 4> wwww() const {
      return vec<_T, 4>{*data_[3], *data_[3], *data_[3], *data_[3]};
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
    explicit swizzel(const std::array<std::shared_ptr<_T>, _N>& arr)
        : vec_base<_T, _N>() {
      for (std::size_t i = 0; i < _N; ++i) {
        this->data_[i] = arr[i];
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
    vec() : vec_base<_T, _N>() {}

    template <typename _U, std::size_t _M>
    vec(const vec_base<_U, _M>& copy) : vec_base<_T, _N>() {
      for (std::size_t i = 0; i < std::min(_N, _M); ++i) {
        *this->data_[i] = copy[i];
      }
    }
    template <typename _U, std::size_t _M>
    vec(const vec<_U, _M>& copy) : vec_base<_T, _N>() {
      for (std::size_t i = 0; i < std::min(_N, _M); ++i) {
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
    template <std::size_t _I, std::size_t _J, typename... _ARGS>
        typename std::enable_if <
        _I<_N, void>::type constructor(const vec<_T, _J>& t,
                                       const _ARGS&... args) {
      for (std::size_t i = 0; i < std::min(_N, _J); ++i) {
        *this->data_[_I + i] = t[i];
      }
      constructor<_I + _J>(args...);
    }
    template <std::size_t _I, typename... _ARGS>
        typename std::enable_if <
        _I<_N && _I != 0, void>::type constructor(const _T& t) {
      *this->data_[_I] = t;
    }
    template <std::size_t _I, std::size_t _J, typename... _ARGS>
        typename std::enable_if <
        _I<_N, void>::type constructor(const vec<_T, _J>& t) {
      for (std::size_t i = 0; i < std::min(_N, _J); ++i) {
        *this->data_[_I + i] = t[i];
      }
    }
    template <std::size_t _I, typename... _ARGS>
    typename std::enable_if<_I == 0, void>::type constructor(const _T& t) {
      for (std::size_t i = 0; i < _N; ++i) {
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
    for (std::size_t i = 0; i < _N; ++i) {
      res[i] = lhs[i] + rhs;
    }
    return res;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> operator+(const vec<_T, _N>& lhs, const vec<_T, _N>& rhs) {
    vec<_T, _N> res;
    for (std::size_t i = 0; i < _N; ++i) {
      res[i] = lhs[i] + rhs[i];
    }
    return res;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> operator-(const vec<_T, _N>& lhs, const _T& rhs) {
    vec<_T, _N> res;
    for (std::size_t i = 0; i < _N; ++i) {
      res[i] = lhs[i] - rhs;
    }
    return res;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> operator-(const vec<_T, _N>& lhs, const vec<_T, _N>& rhs) {
    vec<_T, _N> res;
    for (std::size_t i = 0; i < _N; ++i) {
      res[i] = lhs[i] - rhs[i];
    }
    return res;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> operator*(const vec<_T, _N>& lhs, const _T& rhs) {
    vec<_T, _N> res;
    for (std::size_t i = 0; i < _N; ++i) {
      res[i] = lhs[i] * rhs;
    }
    return res;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> operator*(const _T& lhs, const vec<_T, _N>& rhs) {
    vec<_T, _N> res;
    for (std::size_t i = 0; i < _N; ++i) {
      res[i] = lhs * rhs[i];
    }
    return res;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> operator*(const vec<_T, _N>& lhs, const vec<_T, _N>& rhs) {
    vec<_T, _N> res;
    for (std::size_t i = 0; i < _N; ++i) {
      res[i] = lhs[i] * rhs[i];
    }
    return res;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> operator/(const vec<_T, _N>& lhs, const _T& rhs) {
    vec<_T, _N> res;
    for (std::size_t i = 0; i < _N; ++i) {
      res[i] = lhs[i] / rhs;
    }
    return res;
  }
  template <typename _T, std::size_t _N>
  inline vec<_T, _N> operator/(const vec<_T, _N>& lhs, const vec<_T, _N>& rhs) {
    vec<_T, _N> res;
    for (std::size_t i = 0; i < _N; ++i) {
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
  typedef vec<double, 2> vec2;
  typedef vec<double, 3> vec3;
  typedef vec<double, 4> vec4;
  typedef vec<double, 8> vec8;
  typedef vec<double, 16> vec16;
}  // namespace math
}  // namespace specula

#endif  // SPECULA_MATH_VECTOR_HPP_
