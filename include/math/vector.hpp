#ifndef SPECULA_MATH_VECTOR_HPP_
#define SPECULA_MATH_VECTOR_HPP_

#include <cmath>
#include <iostream>

namespace specula {
namespace math {
  template <typename _T = double>
  struct Vec2;
  template <typename _T = double>
  struct Vec3;
  template <typename _T = double>
  struct Vec4;

  template <typename _T>
  struct Vec2 {
    Vec2() : x(_T()), y(_T()) {}
    Vec2(const _T& v) : x(v), y(v) {}
    Vec2(const Vec3<_T>& v) : x(v.x), y(v.y) {}
    Vec2(const Vec4<_T>& v) : x(v.x), y(v.y) {}
    Vec2(const _T& a, const _T& b) : x(a), y(b) {}
    Vec2(const Vec2<_T>& copy) : x(copy.x), y(copy.y) {}

    inline Vec2<_T>& operator=(const Vec2<_T>& vec) {
      x = vec.x;
      y = vec.y;
      return *this;
    }
    inline Vec2<_T>& operator=(const _T& val) {
      x = val;
      y = val;
      return *this;
    }

    inline _T& operator[](const std::size_t& i) {
      if (i == 0)
        return x;
      else if (i == 1)
        return y;
      else
        std::__throw_out_of_range_fmt(
            __N("operator[] (which is %zu) >= __Ne (which is 2)"), i);
    }

    template <typename _U>
    inline Vec2<_T>& operator+=(const _U& rhs) {
      *this = *this + rhs;
      return *this;
    }
    template <typename _U>
    inline Vec2<_T>& operator-=(const _U& rhs) {
      *this = *this - rhs;
      return *this;
    }
    template <typename _U>
    inline Vec2<_T>& operator*=(const _U& rhs) {
      *this = *this * rhs;
      return *this;
    }
    template <typename _U>
    inline Vec2<_T>& operator/=(const _U& rhs) {
      *this = *this / rhs;
      return *this;
    }

    inline Vec2<_T> xx() const noexcept { return Vec2<_T>{x, x}; }
    inline Vec2<_T> xy() const noexcept { return Vec2<_T>{x, y}; }
    inline Vec2<_T> yx() const noexcept { return Vec2<_T>{y, x}; }
    inline Vec2<_T> yy() const noexcept { return Vec2<_T>{y, y}; }

    inline Vec3<_T> xxx() const noexcept { return Vec3<_T>{x, x, x}; }
    inline Vec3<_T> xxy() const noexcept { return Vec3<_T>{x, x, y}; }
    inline Vec3<_T> xyx() const noexcept { return Vec3<_T>{x, y, x}; }
    inline Vec3<_T> xyy() const noexcept { return Vec3<_T>{x, y, y}; }

    inline Vec3<_T> yxx() const noexcept { return Vec3<_T>{y, x, x}; }
    inline Vec3<_T> yxy() const noexcept { return Vec3<_T>{y, x, y}; }
    inline Vec3<_T> yyx() const noexcept { return Vec3<_T>{y, y, x}; }
    inline Vec3<_T> yyy() const noexcept { return Vec3<_T>{y, y, y}; }

    inline Vec4<_T> xxxx() const noexcept { return Vec4<_T>{x, x, x, x}; }
    inline Vec4<_T> xxxy() const noexcept { return Vec4<_T>{x, x, x, y}; }
    inline Vec4<_T> xxyx() const noexcept { return Vec4<_T>{x, x, y, x}; }
    inline Vec4<_T> xxyy() const noexcept { return Vec4<_T>{x, x, y, y}; }

    inline Vec4<_T> xyxx() const noexcept { return Vec4<_T>{x, y, x, x}; }
    inline Vec4<_T> xyxy() const noexcept { return Vec4<_T>{x, y, x, y}; }
    inline Vec4<_T> xyyx() const noexcept { return Vec4<_T>{x, y, y, x}; }
    inline Vec4<_T> xyyy() const noexcept { return Vec4<_T>{x, y, y, y}; }

    inline Vec4<_T> yxxx() const noexcept { return Vec4<_T>{y, y, y, y}; }
    inline Vec4<_T> yxxy() const noexcept { return Vec4<_T>{y, y, y, y}; }
    inline Vec4<_T> yxyx() const noexcept { return Vec4<_T>{y, y, y, y}; }
    inline Vec4<_T> yxyy() const noexcept { return Vec4<_T>{y, y, y, y}; }

    inline Vec4<_T> yyxx() const noexcept { return Vec4<_T>{y, y, y, y}; }
    inline Vec4<_T> yyxy() const noexcept { return Vec4<_T>{y, y, y, y}; }
    inline Vec4<_T> yyyx() const noexcept { return Vec4<_T>{y, y, y, y}; }
    inline Vec4<_T> yyyy() const noexcept { return Vec4<_T>{y, y, y, y}; }

    _T x, y;
  };

  template <typename _T>
  struct Vec3 {
    Vec3() : x(_T()), y(_T()), z(_T()) {}
    Vec3(const _T& v) : x(v), y(v), z(v) {}
    Vec3(const Vec4<_T>& v) : x(v.x), y(v.y), z(v.z) {}
    Vec3(const _T& a, const _T& b, const _T& c) : x(a), y(b), z(c) {}
    Vec3(const Vec2<_T>& ab, const _T& c) : x(ab.x), y(ab.y), z(c) {}
    Vec3(const _T& a, const Vec2<_T>& bc) : x(a), y(bc.x), z(bc.y) {}
    Vec3(const Vec3<_T>& copy) : x(copy.x), y(copy.y), z(copy.z) {}

    inline Vec3<_T>& operator=(const Vec3<_T>& vec) {
      x = vec.x;
      y = vec.y;
      z = vec.z;
      return *this;
    }
    inline Vec3<_T>& operator=(const _T& val) {
      x = val;
      y = val;
      z = val;
      return *this;
    }

    inline _T& operator[](const std::size_t& i) {
      if (i == 0)
        return x;
      else if (i == 1)
        return y;
      else if (i == 2)
        return z;
      else
        std::__throw_out_of_range_fmt(
            __N("operator[] (which is %zu) >= __Ne (which is 3)"), i);
    }

    template <typename _U>
    inline Vec3<_T>& operator+=(const _U& rhs) {
      *this = *this + rhs;
      return *this;
    }
    template <typename _U>
    inline Vec3<_T>& operator-=(const _U& rhs) {
      *this = *this - rhs;
      return *this;
    }
    template <typename _U>
    inline Vec3<_T>& operator*=(const _U& rhs) {
      *this = *this * rhs;
      return *this;
    }
    template <typename _U>
    inline Vec3<_T>& operator/=(const _U& rhs) {
      *this = *this / rhs;
      return *this;
    }

    inline Vec2<_T> xx() const noexcept { return Vec2<_T>{x, x}; }
    inline Vec2<_T> xy() const noexcept { return Vec2<_T>{x, y}; }
    inline Vec2<_T> xz() const noexcept { return Vec2<_T>{x, z}; }
    inline Vec2<_T> yx() const noexcept { return Vec2<_T>{y, x}; }
    inline Vec2<_T> yy() const noexcept { return Vec2<_T>{y, y}; }
    inline Vec2<_T> yz() const noexcept { return Vec2<_T>{y, z}; }
    inline Vec2<_T> zx() const noexcept { return Vec2<_T>{z, x}; }
    inline Vec2<_T> zy() const noexcept { return Vec2<_T>{z, y}; }
    inline Vec2<_T> zz() const noexcept { return Vec2<_T>{z, z}; }

    inline Vec3<_T> xxx() const noexcept { return Vec3<_T>{x, x, x}; }
    inline Vec3<_T> xxy() const noexcept { return Vec3<_T>{x, x, y}; }
    inline Vec3<_T> xxz() const noexcept { return Vec3<_T>{x, x, z}; }
    inline Vec3<_T> xyx() const noexcept { return Vec3<_T>{x, y, x}; }
    inline Vec3<_T> xyy() const noexcept { return Vec3<_T>{x, y, y}; }
    inline Vec3<_T> xyz() const noexcept { return Vec3<_T>{x, y, z}; }
    inline Vec3<_T> xzx() const noexcept { return Vec3<_T>{x, z, x}; }
    inline Vec3<_T> xzy() const noexcept { return Vec3<_T>{x, z, y}; }
    inline Vec3<_T> xzz() const noexcept { return Vec3<_T>{x, z, z}; }

    inline Vec3<_T> yxx() const noexcept { return Vec3<_T>{y, x, x}; }
    inline Vec3<_T> yxy() const noexcept { return Vec3<_T>{y, x, y}; }
    inline Vec3<_T> yxz() const noexcept { return Vec3<_T>{y, x, z}; }
    inline Vec3<_T> yyx() const noexcept { return Vec3<_T>{y, y, x}; }
    inline Vec3<_T> yyy() const noexcept { return Vec3<_T>{y, y, y}; }
    inline Vec3<_T> yyz() const noexcept { return Vec3<_T>{y, y, z}; }
    inline Vec3<_T> yzx() const noexcept { return Vec3<_T>{y, z, x}; }
    inline Vec3<_T> yzy() const noexcept { return Vec3<_T>{y, z, y}; }
    inline Vec3<_T> yzz() const noexcept { return Vec3<_T>{y, z, z}; }

    inline Vec3<_T> zxx() const noexcept { return Vec3<_T>{z, x, x}; }
    inline Vec3<_T> zxy() const noexcept { return Vec3<_T>{z, x, y}; }
    inline Vec3<_T> zxz() const noexcept { return Vec3<_T>{z, x, z}; }
    inline Vec3<_T> zyx() const noexcept { return Vec3<_T>{z, y, x}; }
    inline Vec3<_T> zyy() const noexcept { return Vec3<_T>{z, y, y}; }
    inline Vec3<_T> zyz() const noexcept { return Vec3<_T>{z, y, z}; }
    inline Vec3<_T> zzx() const noexcept { return Vec3<_T>{z, z, x}; }
    inline Vec3<_T> zzy() const noexcept { return Vec3<_T>{z, z, y}; }
    inline Vec3<_T> zzz() const noexcept { return Vec3<_T>{z, z, z}; }

    inline Vec4<_T> xxxx() const noexcept { return Vec4<_T>{x, x, x, x}; }
    inline Vec4<_T> xxxy() const noexcept { return Vec4<_T>{x, x, x, y}; }
    inline Vec4<_T> xxxz() const noexcept { return Vec4<_T>{x, x, x, z}; }
    inline Vec4<_T> xxyx() const noexcept { return Vec4<_T>{x, x, y, x}; }
    inline Vec4<_T> xxyy() const noexcept { return Vec4<_T>{x, x, y, y}; }
    inline Vec4<_T> xxyz() const noexcept { return Vec4<_T>{x, x, y, z}; }
    inline Vec4<_T> xxzx() const noexcept { return Vec4<_T>{x, x, z, x}; }
    inline Vec4<_T> xxzy() const noexcept { return Vec4<_T>{x, x, z, y}; }
    inline Vec4<_T> xxzz() const noexcept { return Vec4<_T>{x, x, z, z}; }

    inline Vec4<_T> xyxx() const noexcept { return Vec4<_T>{x, y, x, x}; }
    inline Vec4<_T> xyxy() const noexcept { return Vec4<_T>{x, y, x, y}; }
    inline Vec4<_T> xyxz() const noexcept { return Vec4<_T>{x, y, x, z}; }
    inline Vec4<_T> xyyx() const noexcept { return Vec4<_T>{x, y, y, x}; }
    inline Vec4<_T> xyyy() const noexcept { return Vec4<_T>{x, y, y, y}; }
    inline Vec4<_T> xyyz() const noexcept { return Vec4<_T>{x, y, y, z}; }
    inline Vec4<_T> xyzx() const noexcept { return Vec4<_T>{x, y, z, x}; }
    inline Vec4<_T> xyzy() const noexcept { return Vec4<_T>{x, y, z, y}; }
    inline Vec4<_T> xyzz() const noexcept { return Vec4<_T>{x, y, z, z}; }

    inline Vec4<_T> xzxx() const noexcept { return Vec4<_T>{x, z, x, x}; }
    inline Vec4<_T> xzxy() const noexcept { return Vec4<_T>{x, z, x, y}; }
    inline Vec4<_T> xzxz() const noexcept { return Vec4<_T>{x, z, x, z}; }
    inline Vec4<_T> xzyx() const noexcept { return Vec4<_T>{x, z, y, x}; }
    inline Vec4<_T> xzyy() const noexcept { return Vec4<_T>{x, z, y, y}; }
    inline Vec4<_T> xzyz() const noexcept { return Vec4<_T>{x, z, y, z}; }
    inline Vec4<_T> xzzx() const noexcept { return Vec4<_T>{x, z, z, x}; }
    inline Vec4<_T> xzzy() const noexcept { return Vec4<_T>{x, z, z, y}; }
    inline Vec4<_T> xzzz() const noexcept { return Vec4<_T>{x, z, z, z}; }

    inline Vec4<_T> yxxx() const noexcept { return Vec4<_T>{y, y, y, y}; }
    inline Vec4<_T> yxxy() const noexcept { return Vec4<_T>{y, y, y, y}; }
    inline Vec4<_T> yxxz() const noexcept { return Vec4<_T>{y, y, y, z}; }
    inline Vec4<_T> yxyx() const noexcept { return Vec4<_T>{y, y, y, y}; }
    inline Vec4<_T> yxyy() const noexcept { return Vec4<_T>{y, y, y, y}; }
    inline Vec4<_T> yxyz() const noexcept { return Vec4<_T>{y, y, y, z}; }
    inline Vec4<_T> yxzx() const noexcept { return Vec4<_T>{y, y, z, y}; }
    inline Vec4<_T> yxzy() const noexcept { return Vec4<_T>{y, y, z, y}; }
    inline Vec4<_T> yxzz() const noexcept { return Vec4<_T>{y, y, z, z}; }

    inline Vec4<_T> yyxx() const noexcept { return Vec4<_T>{y, y, y, y}; }
    inline Vec4<_T> yyxy() const noexcept { return Vec4<_T>{y, y, y, y}; }
    inline Vec4<_T> yyxz() const noexcept { return Vec4<_T>{y, y, y, z}; }
    inline Vec4<_T> yyyx() const noexcept { return Vec4<_T>{y, y, y, y}; }
    inline Vec4<_T> yyyy() const noexcept { return Vec4<_T>{y, y, y, y}; }
    inline Vec4<_T> yyyz() const noexcept { return Vec4<_T>{y, y, y, z}; }
    inline Vec4<_T> yyzx() const noexcept { return Vec4<_T>{y, y, z, y}; }
    inline Vec4<_T> yyzy() const noexcept { return Vec4<_T>{y, y, z, y}; }
    inline Vec4<_T> yyzz() const noexcept { return Vec4<_T>{y, y, z, z}; }

    inline Vec4<_T> yzxx() const noexcept { return Vec4<_T>{y, z, y, y}; }
    inline Vec4<_T> yzxy() const noexcept { return Vec4<_T>{y, z, y, y}; }
    inline Vec4<_T> yzxz() const noexcept { return Vec4<_T>{y, z, y, z}; }
    inline Vec4<_T> yzyx() const noexcept { return Vec4<_T>{y, z, y, y}; }
    inline Vec4<_T> yzyy() const noexcept { return Vec4<_T>{y, z, y, y}; }
    inline Vec4<_T> yzyz() const noexcept { return Vec4<_T>{y, z, y, z}; }
    inline Vec4<_T> yzzx() const noexcept { return Vec4<_T>{y, z, z, y}; }
    inline Vec4<_T> yzzy() const noexcept { return Vec4<_T>{y, z, z, y}; }
    inline Vec4<_T> yzzz() const noexcept { return Vec4<_T>{y, z, z, z}; }

    inline Vec4<_T> zxxx() const noexcept { return Vec4<_T>{z, z, z, z}; }
    inline Vec4<_T> zxxy() const noexcept { return Vec4<_T>{z, z, z, y}; }
    inline Vec4<_T> zxxz() const noexcept { return Vec4<_T>{z, z, z, z}; }
    inline Vec4<_T> zxyx() const noexcept { return Vec4<_T>{z, z, y, z}; }
    inline Vec4<_T> zxyy() const noexcept { return Vec4<_T>{z, z, y, y}; }
    inline Vec4<_T> zxyz() const noexcept { return Vec4<_T>{z, z, y, z}; }
    inline Vec4<_T> zxzx() const noexcept { return Vec4<_T>{z, z, z, z}; }
    inline Vec4<_T> zxzy() const noexcept { return Vec4<_T>{z, z, z, y}; }
    inline Vec4<_T> zxzz() const noexcept { return Vec4<_T>{z, z, z, z}; }

    inline Vec4<_T> zyxx() const noexcept { return Vec4<_T>{z, y, z, z}; }
    inline Vec4<_T> zyxy() const noexcept { return Vec4<_T>{z, y, z, y}; }
    inline Vec4<_T> zyxz() const noexcept { return Vec4<_T>{z, y, z, z}; }
    inline Vec4<_T> zyyx() const noexcept { return Vec4<_T>{z, y, y, z}; }
    inline Vec4<_T> zyyy() const noexcept { return Vec4<_T>{z, y, y, y}; }
    inline Vec4<_T> zyyz() const noexcept { return Vec4<_T>{z, y, y, z}; }
    inline Vec4<_T> zyzx() const noexcept { return Vec4<_T>{z, y, z, z}; }
    inline Vec4<_T> zyzy() const noexcept { return Vec4<_T>{z, y, z, y}; }
    inline Vec4<_T> zyzz() const noexcept { return Vec4<_T>{z, y, z, z}; }

    inline Vec4<_T> zzxx() const noexcept { return Vec4<_T>{z, z, z, z}; }
    inline Vec4<_T> zzxy() const noexcept { return Vec4<_T>{z, z, z, y}; }
    inline Vec4<_T> zzxz() const noexcept { return Vec4<_T>{z, z, z, z}; }
    inline Vec4<_T> zzyx() const noexcept { return Vec4<_T>{z, z, y, z}; }
    inline Vec4<_T> zzyy() const noexcept { return Vec4<_T>{z, z, y, y}; }
    inline Vec4<_T> zzyz() const noexcept { return Vec4<_T>{z, z, y, z}; }
    inline Vec4<_T> zzzx() const noexcept { return Vec4<_T>{z, z, z, z}; }
    inline Vec4<_T> zzzy() const noexcept { return Vec4<_T>{z, z, z, y}; }
    inline Vec4<_T> zzzz() const noexcept { return Vec4<_T>{z, z, z, z}; }

    _T x, y, z;
  };

  template <typename _T>
  struct Vec4 {
    Vec4() : x(_T()), y(_T()), z(_T()), w(_T()) {}
    explicit Vec4(const _T& v) : x(v), y(v), z(v), w(v) {}
    Vec4(const _T& a, const _T& b, const _T& c, const _T& d)
        : x(a), y(b), z(c), w(d) {}
    Vec4(const Vec3<_T>& abc, const _T& d)
        : x(abc.x), y(abc.y), z(abc.z), w(d) {}
    Vec4(const _T& a, const Vec3<_T>& bcd)
        : x(a), y(bcd.x), z(bcd.y), w(bcd.z) {}
    Vec4(const Vec2<_T>& ab, const _T& c, const _T& d)
        : x(ab.x), y(ab.y), z(c), w(d) {}
    Vec4(const _T& a, const Vec2<_T>& bc, const _T& d)
        : x(a), y(bc.x), z(bc.y), w(d) {}
    Vec4(const _T& a, const _T& b, const Vec2<_T>& cd)
        : x(a), y(b), z(cd.x), w(cd.y) {}
    Vec4(const Vec2<_T>& ab, const Vec2<_T>& cd)
        : x(ab.x), y(ab.y), z(cd.x), w(cd.y) {}
    Vec4(const Vec4<_T>& copy) : x(copy.x), y(copy.y), z(copy.z), w(copy.w) {}

    inline Vec4<_T>& operator=(const Vec4<_T>& vec) {
      x = vec.x;
      y = vec.y;
      z = vec.z;
      w = vec.w;
      return *this;
    }
    inline Vec4<_T>& operator=(const _T& val) {
      x = val;
      y = val;
      z = val;
      w = val;
      return *this;
    }

    inline _T& operator[](const std::size_t& i) {
      if (i == 0)
        return x;
      else if (i == 1)
        return y;
      else if (i == 2)
        return z;
      else if (i == 3)
        return w;
      else
        std::__throw_out_of_range_fmt(
            __N("operator[] (which is %zu) >= __Ne (which is 4)"), i);
    }

    template <typename _U>
    inline Vec4<_T>& operator+=(const _U& rhs) {
      *this = *this + rhs;
      return *this;
    }
    template <typename _U>
    inline Vec4<_T>& operator-=(const _U& rhs) {
      *this = *this - rhs;
      return *this;
    }
    template <typename _U>
    inline Vec4<_T>& operator*=(const _U& rhs) {
      *this = *this * rhs;
      return *this;
    }
    template <typename _U>
    inline Vec4<_T>& operator/=(const _U& rhs) {
      *this = *this / rhs;
      return *this;
    }

    inline Vec2<_T> xx() const noexcept { return Vec2<_T>{x, x}; }
    inline Vec2<_T> xy() const noexcept { return Vec2<_T>{x, y}; }
    inline Vec2<_T> xz() const noexcept { return Vec2<_T>{x, z}; }
    inline Vec2<_T> xw() const noexcept { return Vec2<_T>{x, w}; }
    inline Vec2<_T> yx() const noexcept { return Vec2<_T>{y, x}; }
    inline Vec2<_T> yy() const noexcept { return Vec2<_T>{y, y}; }
    inline Vec2<_T> yz() const noexcept { return Vec2<_T>{y, z}; }
    inline Vec2<_T> yw() const noexcept { return Vec2<_T>{y, w}; }
    inline Vec2<_T> zx() const noexcept { return Vec2<_T>{z, x}; }
    inline Vec2<_T> zy() const noexcept { return Vec2<_T>{z, y}; }
    inline Vec2<_T> zz() const noexcept { return Vec2<_T>{z, z}; }
    inline Vec2<_T> zw() const noexcept { return Vec2<_T>{z, w}; }
    inline Vec2<_T> wx() const noexcept { return Vec2<_T>{w, x}; }
    inline Vec2<_T> wy() const noexcept { return Vec2<_T>{w, y}; }
    inline Vec2<_T> wz() const noexcept { return Vec2<_T>{w, z}; }
    inline Vec2<_T> ww() const noexcept { return Vec2<_T>{w, w}; }

    inline Vec3<_T> xxx() const noexcept { return Vec3<_T>{x, x, x}; }
    inline Vec3<_T> xxy() const noexcept { return Vec3<_T>{x, x, y}; }
    inline Vec3<_T> xxz() const noexcept { return Vec3<_T>{x, x, z}; }
    inline Vec3<_T> xxw() const noexcept { return Vec3<_T>{x, x, w}; }
    inline Vec3<_T> xyx() const noexcept { return Vec3<_T>{x, y, x}; }
    inline Vec3<_T> xyy() const noexcept { return Vec3<_T>{x, y, y}; }
    inline Vec3<_T> xyz() const noexcept { return Vec3<_T>{x, y, z}; }
    inline Vec3<_T> xyw() const noexcept { return Vec3<_T>{x, y, w}; }
    inline Vec3<_T> xzx() const noexcept { return Vec3<_T>{x, z, x}; }
    inline Vec3<_T> xzy() const noexcept { return Vec3<_T>{x, z, y}; }
    inline Vec3<_T> xzz() const noexcept { return Vec3<_T>{x, z, z}; }
    inline Vec3<_T> xzw() const noexcept { return Vec3<_T>{x, z, w}; }
    inline Vec3<_T> xwx() const noexcept { return Vec3<_T>{x, w, x}; }
    inline Vec3<_T> xwy() const noexcept { return Vec3<_T>{x, w, y}; }
    inline Vec3<_T> xwz() const noexcept { return Vec3<_T>{x, w, z}; }
    inline Vec3<_T> xww() const noexcept { return Vec3<_T>{x, w, w}; }

    inline Vec3<_T> yxx() const noexcept { return Vec3<_T>{y, x, x}; }
    inline Vec3<_T> yxy() const noexcept { return Vec3<_T>{y, x, y}; }
    inline Vec3<_T> yxz() const noexcept { return Vec3<_T>{y, x, z}; }
    inline Vec3<_T> yxw() const noexcept { return Vec3<_T>{y, x, w}; }
    inline Vec3<_T> yyx() const noexcept { return Vec3<_T>{y, y, x}; }
    inline Vec3<_T> yyy() const noexcept { return Vec3<_T>{y, y, y}; }
    inline Vec3<_T> yyz() const noexcept { return Vec3<_T>{y, y, z}; }
    inline Vec3<_T> yyw() const noexcept { return Vec3<_T>{y, y, w}; }
    inline Vec3<_T> yzx() const noexcept { return Vec3<_T>{y, z, x}; }
    inline Vec3<_T> yzy() const noexcept { return Vec3<_T>{y, z, y}; }
    inline Vec3<_T> yzz() const noexcept { return Vec3<_T>{y, z, z}; }
    inline Vec3<_T> yzw() const noexcept { return Vec3<_T>{y, z, w}; }
    inline Vec3<_T> ywx() const noexcept { return Vec3<_T>{y, w, x}; }
    inline Vec3<_T> ywy() const noexcept { return Vec3<_T>{y, w, y}; }
    inline Vec3<_T> ywz() const noexcept { return Vec3<_T>{y, w, z}; }
    inline Vec3<_T> yww() const noexcept { return Vec3<_T>{y, w, w}; }

    inline Vec3<_T> zxx() const noexcept { return Vec3<_T>{z, x, x}; }
    inline Vec3<_T> zxy() const noexcept { return Vec3<_T>{z, x, y}; }
    inline Vec3<_T> zxz() const noexcept { return Vec3<_T>{z, x, z}; }
    inline Vec3<_T> zxw() const noexcept { return Vec3<_T>{z, x, w}; }
    inline Vec3<_T> zyx() const noexcept { return Vec3<_T>{z, y, x}; }
    inline Vec3<_T> zyy() const noexcept { return Vec3<_T>{z, y, y}; }
    inline Vec3<_T> zyz() const noexcept { return Vec3<_T>{z, y, z}; }
    inline Vec3<_T> zyw() const noexcept { return Vec3<_T>{z, y, w}; }
    inline Vec3<_T> zzx() const noexcept { return Vec3<_T>{z, z, x}; }
    inline Vec3<_T> zzy() const noexcept { return Vec3<_T>{z, z, y}; }
    inline Vec3<_T> zzz() const noexcept { return Vec3<_T>{z, z, z}; }
    inline Vec3<_T> zzw() const noexcept { return Vec3<_T>{z, z, w}; }
    inline Vec3<_T> zwx() const noexcept { return Vec3<_T>{z, w, x}; }
    inline Vec3<_T> zwy() const noexcept { return Vec3<_T>{z, w, y}; }
    inline Vec3<_T> zwz() const noexcept { return Vec3<_T>{z, w, z}; }
    inline Vec3<_T> zww() const noexcept { return Vec3<_T>{z, w, w}; }

    inline Vec3<_T> wxx() const noexcept { return Vec3<_T>{w, x, x}; }
    inline Vec3<_T> wxy() const noexcept { return Vec3<_T>{w, x, y}; }
    inline Vec3<_T> wxz() const noexcept { return Vec3<_T>{w, x, z}; }
    inline Vec3<_T> wxw() const noexcept { return Vec3<_T>{w, x, w}; }
    inline Vec3<_T> wyx() const noexcept { return Vec3<_T>{w, y, x}; }
    inline Vec3<_T> wyy() const noexcept { return Vec3<_T>{w, y, y}; }
    inline Vec3<_T> wyz() const noexcept { return Vec3<_T>{w, y, z}; }
    inline Vec3<_T> wyw() const noexcept { return Vec3<_T>{w, y, w}; }
    inline Vec3<_T> wzx() const noexcept { return Vec3<_T>{w, z, x}; }
    inline Vec3<_T> wzy() const noexcept { return Vec3<_T>{w, z, y}; }
    inline Vec3<_T> wzz() const noexcept { return Vec3<_T>{w, z, z}; }
    inline Vec3<_T> wzw() const noexcept { return Vec3<_T>{w, z, w}; }
    inline Vec3<_T> wwx() const noexcept { return Vec3<_T>{w, w, x}; }
    inline Vec3<_T> wwy() const noexcept { return Vec3<_T>{w, w, y}; }
    inline Vec3<_T> wwz() const noexcept { return Vec3<_T>{w, w, z}; }
    inline Vec3<_T> www() const noexcept { return Vec3<_T>{w, w, w}; }

    inline Vec4<_T> xxxx() const noexcept { return Vec4<_T>{x, x, x, x}; }
    inline Vec4<_T> xxxy() const noexcept { return Vec4<_T>{x, x, x, y}; }
    inline Vec4<_T> xxxz() const noexcept { return Vec4<_T>{x, x, x, z}; }
    inline Vec4<_T> xxxw() const noexcept { return Vec4<_T>{x, x, x, w}; }
    inline Vec4<_T> xxyx() const noexcept { return Vec4<_T>{x, x, y, x}; }
    inline Vec4<_T> xxyy() const noexcept { return Vec4<_T>{x, x, y, y}; }
    inline Vec4<_T> xxyz() const noexcept { return Vec4<_T>{x, x, y, z}; }
    inline Vec4<_T> xxyw() const noexcept { return Vec4<_T>{x, x, y, w}; }
    inline Vec4<_T> xxzx() const noexcept { return Vec4<_T>{x, x, z, x}; }
    inline Vec4<_T> xxzy() const noexcept { return Vec4<_T>{x, x, z, y}; }
    inline Vec4<_T> xxzz() const noexcept { return Vec4<_T>{x, x, z, z}; }
    inline Vec4<_T> xxzw() const noexcept { return Vec4<_T>{x, x, z, w}; }
    inline Vec4<_T> xxwx() const noexcept { return Vec4<_T>{x, x, w, x}; }
    inline Vec4<_T> xxwy() const noexcept { return Vec4<_T>{x, x, w, y}; }
    inline Vec4<_T> xxwz() const noexcept { return Vec4<_T>{x, x, w, z}; }
    inline Vec4<_T> xxww() const noexcept { return Vec4<_T>{x, x, w, w}; }

    inline Vec4<_T> xyxx() const noexcept { return Vec4<_T>{x, y, x, x}; }
    inline Vec4<_T> xyxy() const noexcept { return Vec4<_T>{x, y, x, y}; }
    inline Vec4<_T> xyxz() const noexcept { return Vec4<_T>{x, y, x, z}; }
    inline Vec4<_T> xyxw() const noexcept { return Vec4<_T>{x, y, x, w}; }
    inline Vec4<_T> xyyx() const noexcept { return Vec4<_T>{x, y, y, x}; }
    inline Vec4<_T> xyyy() const noexcept { return Vec4<_T>{x, y, y, y}; }
    inline Vec4<_T> xyyz() const noexcept { return Vec4<_T>{x, y, y, z}; }
    inline Vec4<_T> xyyw() const noexcept { return Vec4<_T>{x, y, y, w}; }
    inline Vec4<_T> xyzx() const noexcept { return Vec4<_T>{x, y, z, x}; }
    inline Vec4<_T> xyzy() const noexcept { return Vec4<_T>{x, y, z, y}; }
    inline Vec4<_T> xyzz() const noexcept { return Vec4<_T>{x, y, z, z}; }
    inline Vec4<_T> xyzw() const noexcept { return Vec4<_T>{x, y, z, w}; }
    inline Vec4<_T> xywx() const noexcept { return Vec4<_T>{x, y, w, x}; }
    inline Vec4<_T> xywy() const noexcept { return Vec4<_T>{x, y, w, y}; }
    inline Vec4<_T> xywz() const noexcept { return Vec4<_T>{x, y, w, z}; }
    inline Vec4<_T> xyww() const noexcept { return Vec4<_T>{x, y, w, w}; }

    inline Vec4<_T> xzxx() const noexcept { return Vec4<_T>{x, z, x, x}; }
    inline Vec4<_T> xzxy() const noexcept { return Vec4<_T>{x, z, x, y}; }
    inline Vec4<_T> xzxz() const noexcept { return Vec4<_T>{x, z, x, z}; }
    inline Vec4<_T> xzxw() const noexcept { return Vec4<_T>{x, z, x, w}; }
    inline Vec4<_T> xzyx() const noexcept { return Vec4<_T>{x, z, y, x}; }
    inline Vec4<_T> xzyy() const noexcept { return Vec4<_T>{x, z, y, y}; }
    inline Vec4<_T> xzyz() const noexcept { return Vec4<_T>{x, z, y, z}; }
    inline Vec4<_T> xzyw() const noexcept { return Vec4<_T>{x, z, y, w}; }
    inline Vec4<_T> xzzx() const noexcept { return Vec4<_T>{x, z, z, x}; }
    inline Vec4<_T> xzzy() const noexcept { return Vec4<_T>{x, z, z, y}; }
    inline Vec4<_T> xzzz() const noexcept { return Vec4<_T>{x, z, z, z}; }
    inline Vec4<_T> xzzw() const noexcept { return Vec4<_T>{x, z, z, w}; }
    inline Vec4<_T> xzwx() const noexcept { return Vec4<_T>{x, z, w, x}; }
    inline Vec4<_T> xzwy() const noexcept { return Vec4<_T>{x, z, w, y}; }
    inline Vec4<_T> xzwz() const noexcept { return Vec4<_T>{x, z, w, z}; }
    inline Vec4<_T> xzww() const noexcept { return Vec4<_T>{x, z, w, w}; }

    inline Vec4<_T> xwxx() const noexcept { return Vec4<_T>{x, w, x, x}; }
    inline Vec4<_T> xwxy() const noexcept { return Vec4<_T>{x, w, x, y}; }
    inline Vec4<_T> xwxz() const noexcept { return Vec4<_T>{x, w, x, z}; }
    inline Vec4<_T> xwxw() const noexcept { return Vec4<_T>{x, w, x, w}; }
    inline Vec4<_T> xwyx() const noexcept { return Vec4<_T>{x, w, y, x}; }
    inline Vec4<_T> xwyy() const noexcept { return Vec4<_T>{x, w, y, y}; }
    inline Vec4<_T> xwyz() const noexcept { return Vec4<_T>{x, w, y, z}; }
    inline Vec4<_T> xwyw() const noexcept { return Vec4<_T>{x, w, y, w}; }
    inline Vec4<_T> xwzx() const noexcept { return Vec4<_T>{x, w, z, x}; }
    inline Vec4<_T> xwzy() const noexcept { return Vec4<_T>{x, w, z, y}; }
    inline Vec4<_T> xwzz() const noexcept { return Vec4<_T>{x, w, z, z}; }
    inline Vec4<_T> xwzw() const noexcept { return Vec4<_T>{x, w, z, w}; }
    inline Vec4<_T> xwwx() const noexcept { return Vec4<_T>{x, w, w, x}; }
    inline Vec4<_T> xwwy() const noexcept { return Vec4<_T>{x, w, w, y}; }
    inline Vec4<_T> xwwz() const noexcept { return Vec4<_T>{x, w, w, z}; }
    inline Vec4<_T> xwww() const noexcept { return Vec4<_T>{x, w, w, w}; }

    inline Vec4<_T> yxxx() const noexcept { return Vec4<_T>{y, y, y, y}; }
    inline Vec4<_T> yxxy() const noexcept { return Vec4<_T>{y, y, y, y}; }
    inline Vec4<_T> yxxz() const noexcept { return Vec4<_T>{y, y, y, z}; }
    inline Vec4<_T> yxxw() const noexcept { return Vec4<_T>{y, y, y, w}; }
    inline Vec4<_T> yxyx() const noexcept { return Vec4<_T>{y, y, y, y}; }
    inline Vec4<_T> yxyy() const noexcept { return Vec4<_T>{y, y, y, y}; }
    inline Vec4<_T> yxyz() const noexcept { return Vec4<_T>{y, y, y, z}; }
    inline Vec4<_T> yxyw() const noexcept { return Vec4<_T>{y, y, y, w}; }
    inline Vec4<_T> yxzx() const noexcept { return Vec4<_T>{y, y, z, y}; }
    inline Vec4<_T> yxzy() const noexcept { return Vec4<_T>{y, y, z, y}; }
    inline Vec4<_T> yxzz() const noexcept { return Vec4<_T>{y, y, z, z}; }
    inline Vec4<_T> yxzw() const noexcept { return Vec4<_T>{y, y, z, w}; }
    inline Vec4<_T> yxwx() const noexcept { return Vec4<_T>{y, y, w, y}; }
    inline Vec4<_T> yxwy() const noexcept { return Vec4<_T>{y, y, w, y}; }
    inline Vec4<_T> yxwz() const noexcept { return Vec4<_T>{y, y, w, z}; }
    inline Vec4<_T> yxww() const noexcept { return Vec4<_T>{y, y, w, w}; }

    inline Vec4<_T> yyxx() const noexcept { return Vec4<_T>{y, y, y, y}; }
    inline Vec4<_T> yyxy() const noexcept { return Vec4<_T>{y, y, y, y}; }
    inline Vec4<_T> yyxz() const noexcept { return Vec4<_T>{y, y, y, z}; }
    inline Vec4<_T> yyxw() const noexcept { return Vec4<_T>{y, y, y, w}; }
    inline Vec4<_T> yyyx() const noexcept { return Vec4<_T>{y, y, y, y}; }
    inline Vec4<_T> yyyy() const noexcept { return Vec4<_T>{y, y, y, y}; }
    inline Vec4<_T> yyyz() const noexcept { return Vec4<_T>{y, y, y, z}; }
    inline Vec4<_T> yyyw() const noexcept { return Vec4<_T>{y, y, y, w}; }
    inline Vec4<_T> yyzx() const noexcept { return Vec4<_T>{y, y, z, y}; }
    inline Vec4<_T> yyzy() const noexcept { return Vec4<_T>{y, y, z, y}; }
    inline Vec4<_T> yyzz() const noexcept { return Vec4<_T>{y, y, z, z}; }
    inline Vec4<_T> yyzw() const noexcept { return Vec4<_T>{y, y, z, w}; }
    inline Vec4<_T> yywx() const noexcept { return Vec4<_T>{y, y, w, y}; }
    inline Vec4<_T> yywy() const noexcept { return Vec4<_T>{y, y, w, y}; }
    inline Vec4<_T> yywz() const noexcept { return Vec4<_T>{y, y, w, z}; }
    inline Vec4<_T> yyww() const noexcept { return Vec4<_T>{y, y, w, w}; }

    inline Vec4<_T> yzxx() const noexcept { return Vec4<_T>{y, z, y, y}; }
    inline Vec4<_T> yzxy() const noexcept { return Vec4<_T>{y, z, y, y}; }
    inline Vec4<_T> yzxz() const noexcept { return Vec4<_T>{y, z, y, z}; }
    inline Vec4<_T> yzxw() const noexcept { return Vec4<_T>{y, z, y, w}; }
    inline Vec4<_T> yzyx() const noexcept { return Vec4<_T>{y, z, y, y}; }
    inline Vec4<_T> yzyy() const noexcept { return Vec4<_T>{y, z, y, y}; }
    inline Vec4<_T> yzyz() const noexcept { return Vec4<_T>{y, z, y, z}; }
    inline Vec4<_T> yzyw() const noexcept { return Vec4<_T>{y, z, y, w}; }
    inline Vec4<_T> yzzx() const noexcept { return Vec4<_T>{y, z, z, y}; }
    inline Vec4<_T> yzzy() const noexcept { return Vec4<_T>{y, z, z, y}; }
    inline Vec4<_T> yzzz() const noexcept { return Vec4<_T>{y, z, z, z}; }
    inline Vec4<_T> yzzw() const noexcept { return Vec4<_T>{y, z, z, w}; }
    inline Vec4<_T> yzwx() const noexcept { return Vec4<_T>{y, z, w, y}; }
    inline Vec4<_T> yzwy() const noexcept { return Vec4<_T>{y, z, w, y}; }
    inline Vec4<_T> yzwz() const noexcept { return Vec4<_T>{y, z, w, z}; }
    inline Vec4<_T> yzww() const noexcept { return Vec4<_T>{y, z, w, w}; }

    inline Vec4<_T> ywxx() const noexcept { return Vec4<_T>{y, w, y, y}; }
    inline Vec4<_T> ywxy() const noexcept { return Vec4<_T>{y, w, y, y}; }
    inline Vec4<_T> ywxz() const noexcept { return Vec4<_T>{y, w, y, z}; }
    inline Vec4<_T> ywxw() const noexcept { return Vec4<_T>{y, w, y, w}; }
    inline Vec4<_T> ywyx() const noexcept { return Vec4<_T>{y, w, y, y}; }
    inline Vec4<_T> ywyy() const noexcept { return Vec4<_T>{y, w, y, y}; }
    inline Vec4<_T> ywyz() const noexcept { return Vec4<_T>{y, w, y, z}; }
    inline Vec4<_T> ywyw() const noexcept { return Vec4<_T>{y, w, y, w}; }
    inline Vec4<_T> ywzx() const noexcept { return Vec4<_T>{y, w, z, y}; }
    inline Vec4<_T> ywzy() const noexcept { return Vec4<_T>{y, w, z, y}; }
    inline Vec4<_T> ywzz() const noexcept { return Vec4<_T>{y, w, z, z}; }
    inline Vec4<_T> ywzw() const noexcept { return Vec4<_T>{y, w, z, w}; }
    inline Vec4<_T> ywwx() const noexcept { return Vec4<_T>{y, w, w, y}; }
    inline Vec4<_T> ywwy() const noexcept { return Vec4<_T>{y, w, w, y}; }
    inline Vec4<_T> ywwz() const noexcept { return Vec4<_T>{y, w, w, z}; }
    inline Vec4<_T> ywww() const noexcept { return Vec4<_T>{y, w, w, w}; }

    inline Vec4<_T> zxxx() const noexcept { return Vec4<_T>{z, z, z, z}; }
    inline Vec4<_T> zxxy() const noexcept { return Vec4<_T>{z, z, z, y}; }
    inline Vec4<_T> zxxz() const noexcept { return Vec4<_T>{z, z, z, z}; }
    inline Vec4<_T> zxxw() const noexcept { return Vec4<_T>{z, z, z, w}; }
    inline Vec4<_T> zxyx() const noexcept { return Vec4<_T>{z, z, y, z}; }
    inline Vec4<_T> zxyy() const noexcept { return Vec4<_T>{z, z, y, y}; }
    inline Vec4<_T> zxyz() const noexcept { return Vec4<_T>{z, z, y, z}; }
    inline Vec4<_T> zxyw() const noexcept { return Vec4<_T>{z, z, y, w}; }
    inline Vec4<_T> zxzx() const noexcept { return Vec4<_T>{z, z, z, z}; }
    inline Vec4<_T> zxzy() const noexcept { return Vec4<_T>{z, z, z, y}; }
    inline Vec4<_T> zxzz() const noexcept { return Vec4<_T>{z, z, z, z}; }
    inline Vec4<_T> zxzw() const noexcept { return Vec4<_T>{z, z, z, w}; }
    inline Vec4<_T> zxwx() const noexcept { return Vec4<_T>{z, z, w, z}; }
    inline Vec4<_T> zxwy() const noexcept { return Vec4<_T>{z, z, w, y}; }
    inline Vec4<_T> zxwz() const noexcept { return Vec4<_T>{z, z, w, z}; }
    inline Vec4<_T> zxww() const noexcept { return Vec4<_T>{z, z, w, w}; }

    inline Vec4<_T> zyxx() const noexcept { return Vec4<_T>{z, y, z, z}; }
    inline Vec4<_T> zyxy() const noexcept { return Vec4<_T>{z, y, z, y}; }
    inline Vec4<_T> zyxz() const noexcept { return Vec4<_T>{z, y, z, z}; }
    inline Vec4<_T> zyxw() const noexcept { return Vec4<_T>{z, y, z, w}; }
    inline Vec4<_T> zyyx() const noexcept { return Vec4<_T>{z, y, y, z}; }
    inline Vec4<_T> zyyy() const noexcept { return Vec4<_T>{z, y, y, y}; }
    inline Vec4<_T> zyyz() const noexcept { return Vec4<_T>{z, y, y, z}; }
    inline Vec4<_T> zyyw() const noexcept { return Vec4<_T>{z, y, y, w}; }
    inline Vec4<_T> zyzx() const noexcept { return Vec4<_T>{z, y, z, z}; }
    inline Vec4<_T> zyzy() const noexcept { return Vec4<_T>{z, y, z, y}; }
    inline Vec4<_T> zyzz() const noexcept { return Vec4<_T>{z, y, z, z}; }
    inline Vec4<_T> zyzw() const noexcept { return Vec4<_T>{z, y, z, w}; }
    inline Vec4<_T> zywx() const noexcept { return Vec4<_T>{z, y, w, z}; }
    inline Vec4<_T> zywy() const noexcept { return Vec4<_T>{z, y, w, y}; }
    inline Vec4<_T> zywz() const noexcept { return Vec4<_T>{z, y, w, z}; }
    inline Vec4<_T> zyww() const noexcept { return Vec4<_T>{z, y, w, w}; }

    inline Vec4<_T> zzxx() const noexcept { return Vec4<_T>{z, z, z, z}; }
    inline Vec4<_T> zzxy() const noexcept { return Vec4<_T>{z, z, z, y}; }
    inline Vec4<_T> zzxz() const noexcept { return Vec4<_T>{z, z, z, z}; }
    inline Vec4<_T> zzxw() const noexcept { return Vec4<_T>{z, z, z, w}; }
    inline Vec4<_T> zzyx() const noexcept { return Vec4<_T>{z, z, y, z}; }
    inline Vec4<_T> zzyy() const noexcept { return Vec4<_T>{z, z, y, y}; }
    inline Vec4<_T> zzyz() const noexcept { return Vec4<_T>{z, z, y, z}; }
    inline Vec4<_T> zzyw() const noexcept { return Vec4<_T>{z, z, y, w}; }
    inline Vec4<_T> zzzx() const noexcept { return Vec4<_T>{z, z, z, z}; }
    inline Vec4<_T> zzzy() const noexcept { return Vec4<_T>{z, z, z, y}; }
    inline Vec4<_T> zzzz() const noexcept { return Vec4<_T>{z, z, z, z}; }
    inline Vec4<_T> zzzw() const noexcept { return Vec4<_T>{z, z, z, w}; }
    inline Vec4<_T> zzwx() const noexcept { return Vec4<_T>{z, z, w, z}; }
    inline Vec4<_T> zzwy() const noexcept { return Vec4<_T>{z, z, w, y}; }
    inline Vec4<_T> zzwz() const noexcept { return Vec4<_T>{z, z, w, z}; }
    inline Vec4<_T> zzww() const noexcept { return Vec4<_T>{z, z, w, w}; }

    inline Vec4<_T> zwxx() const noexcept { return Vec4<_T>{z, w, z, z}; }
    inline Vec4<_T> zwxy() const noexcept { return Vec4<_T>{z, w, z, y}; }
    inline Vec4<_T> zwxz() const noexcept { return Vec4<_T>{z, w, z, z}; }
    inline Vec4<_T> zwxw() const noexcept { return Vec4<_T>{z, w, z, w}; }
    inline Vec4<_T> zwyx() const noexcept { return Vec4<_T>{z, w, y, z}; }
    inline Vec4<_T> zwyy() const noexcept { return Vec4<_T>{z, w, y, y}; }
    inline Vec4<_T> zwyz() const noexcept { return Vec4<_T>{z, w, y, z}; }
    inline Vec4<_T> zwyw() const noexcept { return Vec4<_T>{z, w, y, w}; }
    inline Vec4<_T> zwzx() const noexcept { return Vec4<_T>{z, w, z, z}; }
    inline Vec4<_T> zwzy() const noexcept { return Vec4<_T>{z, w, z, y}; }
    inline Vec4<_T> zwzz() const noexcept { return Vec4<_T>{z, w, z, z}; }
    inline Vec4<_T> zwzw() const noexcept { return Vec4<_T>{z, w, z, w}; }
    inline Vec4<_T> zwwx() const noexcept { return Vec4<_T>{z, w, w, z}; }
    inline Vec4<_T> zwwy() const noexcept { return Vec4<_T>{z, w, w, y}; }
    inline Vec4<_T> zwwz() const noexcept { return Vec4<_T>{z, w, w, z}; }
    inline Vec4<_T> zwww() const noexcept { return Vec4<_T>{z, w, w, w}; }

    inline Vec4<_T> wxxx() const noexcept { return Vec4<_T>{w, w, w, w}; }
    inline Vec4<_T> wxxy() const noexcept { return Vec4<_T>{w, w, w, y}; }
    inline Vec4<_T> wxxz() const noexcept { return Vec4<_T>{w, w, w, z}; }
    inline Vec4<_T> wxxw() const noexcept { return Vec4<_T>{w, w, w, w}; }
    inline Vec4<_T> wxyx() const noexcept { return Vec4<_T>{w, w, y, w}; }
    inline Vec4<_T> wxyy() const noexcept { return Vec4<_T>{w, w, y, y}; }
    inline Vec4<_T> wxyz() const noexcept { return Vec4<_T>{w, w, y, z}; }
    inline Vec4<_T> wxyw() const noexcept { return Vec4<_T>{w, w, y, w}; }
    inline Vec4<_T> wxzx() const noexcept { return Vec4<_T>{w, w, z, w}; }
    inline Vec4<_T> wxzy() const noexcept { return Vec4<_T>{w, w, z, y}; }
    inline Vec4<_T> wxzz() const noexcept { return Vec4<_T>{w, w, z, z}; }
    inline Vec4<_T> wxzw() const noexcept { return Vec4<_T>{w, w, z, w}; }
    inline Vec4<_T> wxwx() const noexcept { return Vec4<_T>{w, w, w, w}; }
    inline Vec4<_T> wxwy() const noexcept { return Vec4<_T>{w, w, w, y}; }
    inline Vec4<_T> wxwz() const noexcept { return Vec4<_T>{w, w, w, z}; }
    inline Vec4<_T> wxww() const noexcept { return Vec4<_T>{w, w, w, w}; }

    inline Vec4<_T> wyxx() const noexcept { return Vec4<_T>{w, y, w, w}; }
    inline Vec4<_T> wyxy() const noexcept { return Vec4<_T>{w, y, w, y}; }
    inline Vec4<_T> wyxz() const noexcept { return Vec4<_T>{w, y, w, z}; }
    inline Vec4<_T> wyxw() const noexcept { return Vec4<_T>{w, y, w, w}; }
    inline Vec4<_T> wyyx() const noexcept { return Vec4<_T>{w, y, y, w}; }
    inline Vec4<_T> wyyy() const noexcept { return Vec4<_T>{w, y, y, y}; }
    inline Vec4<_T> wyyz() const noexcept { return Vec4<_T>{w, y, y, z}; }
    inline Vec4<_T> wyyw() const noexcept { return Vec4<_T>{w, y, y, w}; }
    inline Vec4<_T> wyzx() const noexcept { return Vec4<_T>{w, y, z, w}; }
    inline Vec4<_T> wyzy() const noexcept { return Vec4<_T>{w, y, z, y}; }
    inline Vec4<_T> wyzz() const noexcept { return Vec4<_T>{w, y, z, z}; }
    inline Vec4<_T> wyzw() const noexcept { return Vec4<_T>{w, y, z, w}; }
    inline Vec4<_T> wywx() const noexcept { return Vec4<_T>{w, y, w, w}; }
    inline Vec4<_T> wywy() const noexcept { return Vec4<_T>{w, y, w, y}; }
    inline Vec4<_T> wywz() const noexcept { return Vec4<_T>{w, y, w, z}; }
    inline Vec4<_T> wyww() const noexcept { return Vec4<_T>{w, y, w, w}; }

    inline Vec4<_T> wzxx() const noexcept { return Vec4<_T>{w, z, w, w}; }
    inline Vec4<_T> wzxy() const noexcept { return Vec4<_T>{w, z, w, y}; }
    inline Vec4<_T> wzxz() const noexcept { return Vec4<_T>{w, z, w, z}; }
    inline Vec4<_T> wzxw() const noexcept { return Vec4<_T>{w, z, w, w}; }
    inline Vec4<_T> wzyx() const noexcept { return Vec4<_T>{w, z, y, w}; }
    inline Vec4<_T> wzyy() const noexcept { return Vec4<_T>{w, z, y, y}; }
    inline Vec4<_T> wzyz() const noexcept { return Vec4<_T>{w, z, y, z}; }
    inline Vec4<_T> wzyw() const noexcept { return Vec4<_T>{w, z, y, w}; }
    inline Vec4<_T> wzzx() const noexcept { return Vec4<_T>{w, z, z, w}; }
    inline Vec4<_T> wzzy() const noexcept { return Vec4<_T>{w, z, z, y}; }
    inline Vec4<_T> wzzz() const noexcept { return Vec4<_T>{w, z, z, z}; }
    inline Vec4<_T> wzzw() const noexcept { return Vec4<_T>{w, z, z, w}; }
    inline Vec4<_T> wzwx() const noexcept { return Vec4<_T>{w, z, w, w}; }
    inline Vec4<_T> wzwy() const noexcept { return Vec4<_T>{w, z, w, y}; }
    inline Vec4<_T> wzwz() const noexcept { return Vec4<_T>{w, z, w, z}; }
    inline Vec4<_T> wzww() const noexcept { return Vec4<_T>{w, z, w, w}; }

    inline Vec4<_T> wwxx() const noexcept { return Vec4<_T>{w, w, w, w}; }
    inline Vec4<_T> wwxy() const noexcept { return Vec4<_T>{w, w, w, y}; }
    inline Vec4<_T> wwxz() const noexcept { return Vec4<_T>{w, w, w, z}; }
    inline Vec4<_T> wwxw() const noexcept { return Vec4<_T>{w, w, w, w}; }
    inline Vec4<_T> wwyx() const noexcept { return Vec4<_T>{w, w, y, w}; }
    inline Vec4<_T> wwyy() const noexcept { return Vec4<_T>{w, w, y, y}; }
    inline Vec4<_T> wwyz() const noexcept { return Vec4<_T>{w, w, y, z}; }
    inline Vec4<_T> wwyw() const noexcept { return Vec4<_T>{w, w, y, w}; }
    inline Vec4<_T> wwzx() const noexcept { return Vec4<_T>{w, w, z, w}; }
    inline Vec4<_T> wwzy() const noexcept { return Vec4<_T>{w, w, z, y}; }
    inline Vec4<_T> wwzz() const noexcept { return Vec4<_T>{w, w, z, z}; }
    inline Vec4<_T> wwzw() const noexcept { return Vec4<_T>{w, w, z, w}; }
    inline Vec4<_T> wwwx() const noexcept { return Vec4<_T>{w, w, w, w}; }
    inline Vec4<_T> wwwy() const noexcept { return Vec4<_T>{w, w, w, y}; }
    inline Vec4<_T> wwwz() const noexcept { return Vec4<_T>{w, w, w, z}; }
    inline Vec4<_T> wwww() const noexcept { return Vec4<_T>{w, w, w, w}; }

    _T x, y, z, w;
  };

  template <typename _T>
  inline std::ostream& operator<<(std::ostream& out, const Vec2<_T>& vec) {
    out << '<' << vec.x << ',' << vec.y << '>';
    return out;
  }
  template <typename _T>
  inline std::ostream& operator<<(std::ostream& out, const Vec3<_T>& vec) {
    out << '<' << vec.x << ',' << vec.y << ',' << vec.z << '>';
    return out;
  }
  template <typename _T>
  inline std::ostream& operator<<(std::ostream& out, const Vec4<_T>& vec) {
    out << '<' << vec.x << ',' << vec.y << ',' << vec.z << ',' << vec.w << '>';
    return out;
  }

  template <typename T>
  inline bool operator==(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
  }
  template <typename T>
  inline bool operator!=(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return !(lhs == rhs);
  }
  template <typename T>
  inline bool operator<(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    if (lhs.x < rhs.x) {
      return true;
    } else if (rhs.x < lhs.x) {
      return false;
    } else if (lhs.y < rhs.y) {
      return true;
    } else if (rhs.y < lhs.y) {
      return false;
    } else {
      return false;
    }
  }
  template <typename T>
  inline bool operator>(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return rhs < lhs;
  }
  template <typename T>
  inline bool operator<=(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return !(lhs > rhs);
  }
  template <typename T>
  inline bool operator>=(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return !(lhs < rhs);
  }
  template <typename T>
  inline bool operator==(const Vec3<T>& lhs, const Vec3<T>& rhs) {
    return ((lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z));
  }
  template <typename T>
  inline bool operator!=(const Vec3<T>& lhs, const Vec3<T>& rhs) {
    return !(lhs == rhs);
  }
  template <typename T>
  inline bool operator<(const Vec3<T>& lhs, const Vec3<T>& rhs) {
    if (lhs.x < rhs.x) {
      return true;
    } else if (rhs.x < lhs.x) {
      return false;
    } else if (lhs.y < rhs.y) {
      return true;
    } else if (rhs.y < lhs.y) {
      return false;
    } else if (lhs.z < rhs.z) {
      return true;
    } else if (rhs.z < lhs.z) {
      return false;
    } else {
      return false;
    }
  }
  template <typename T>
  inline bool operator>(const Vec3<T>& lhs, const Vec3<T>& rhs) {
    return rhs < lhs;
  }
  template <typename T>
  inline bool operator<=(const Vec3<T>& lhs, const Vec3<T>& rhs) {
    return !(lhs > rhs);
  }
  template <typename T>
  inline bool operator>=(const Vec3<T>& lhs, const Vec3<T>& rhs) {
    return !(lhs < rhs);
  }
  template <typename T>
  inline bool operator==(const Vec4<T>& lhs, const Vec4<T>& rhs) {
    return ((lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z) &&
            (lhs.w == rhs.w));
  }
  template <typename T>
  inline bool operator!=(const Vec4<T>& lhs, const Vec4<T>& rhs) {
    return !(lhs == rhs);
  }
  template <typename T>
  inline bool operator<(const Vec4<T>& lhs, const Vec4<T>& rhs) {
    if (lhs.x < rhs.x) {
      return true;
    } else if (rhs.x < lhs.x) {
      return false;
    } else if (lhs.y < rhs.y) {
      return true;
    } else if (rhs.y < lhs.y) {
      return false;
    } else if (lhs.z < rhs.z) {
      return true;
    } else if (rhs.z < lhs.z) {
      return false;
    } else if (lhs.w < rhs.w) {
      return true;
    } else if (rhs.w < lhs.w) {
      return false;
    } else {
      return false;
    }
  }
  template <typename T>
  inline bool operator>(const Vec4<T>& lhs, const Vec4<T>& rhs) {
    return rhs < lhs;
  }
  template <typename T>
  inline bool operator<=(const Vec4<T>& lhs, const Vec4<T>& rhs) {
    return !(lhs > rhs);
  }
  template <typename T>
  inline bool operator>=(const Vec4<T>& lhs, const Vec4<T>& rhs) {
    return !(lhs < rhs);
  }

  template <typename _T>
  inline Vec2<_T> operator+(const Vec2<_T>& lhs, const _T& rhs) {
    return Vec2{lhs.x + rhs, lhs.y + rhs};
  }
  template <typename _T>
  inline Vec2<_T> operator+(const Vec2<_T>& lhs, const Vec2<_T>& rhs) {
    return Vec2{lhs.x + rhs.x, lhs.y + rhs.y};
  }
  template <typename _T>
  inline Vec2<_T> operator-(const Vec2<_T>& lhs, const _T& rhs) {
    return Vec2{lhs.x - rhs, lhs.y - rhs};
  }
  template <typename _T>
  inline Vec2<_T> operator-(const Vec2<_T>& lhs, const Vec2<_T>& rhs) {
    return Vec2{lhs.x - rhs.x, lhs.y - rhs.y};
  }
  template <typename _T>
  inline Vec2<_T> operator/(const Vec2<_T>& lhs, const _T& rhs) {
    return Vec2{lhs.x / rhs, lhs.y / rhs};
  }
  template <typename _T>
  inline Vec2<_T> operator/(const Vec2<_T>& lhs, const Vec2<_T>& rhs) {
    return Vec2{lhs.x / rhs.x, lhs.y / rhs.y};
  }
  template <typename _T>
  inline Vec2<_T> operator*(const Vec2<_T>& lhs, const _T& rhs) {
    return Vec2{lhs.x * rhs, lhs.y * rhs};
  }
  template <typename _T>
  inline Vec2<_T> operator*(const Vec2<_T>& lhs, const Vec2<_T>& rhs) {
    return Vec2{lhs.x * rhs.x, lhs.y * rhs.y};
  }

  template <typename _T>
  inline Vec3<_T> operator+(const Vec3<_T>& lhs, const _T& rhs) {
    return Vec3{lhs.x + rhs, lhs.y + rhs, lhs.z + rhs};
  }
  template <typename _T>
  inline Vec3<_T> operator+(const Vec3<_T>& lhs, const Vec3<_T>& rhs) {
    return Vec3{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
  }
  template <typename _T>
  inline Vec3<_T> operator-(const Vec3<_T>& lhs, const _T& rhs) {
    return Vec3{lhs.x - rhs, lhs.y - rhs, lhs.z - rhs};
  }
  template <typename _T>
  inline Vec3<_T> operator-(const Vec3<_T>& lhs, const Vec3<_T>& rhs) {
    return Vec3{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
  }
  template <typename _T>
  inline Vec3<_T> operator/(const Vec3<_T>& lhs, const _T& rhs) {
    return Vec3{lhs.x / rhs, lhs.y / rhs, lhs.z / rhs};
  }
  template <typename _T>
  inline Vec3<_T> operator/(const Vec3<_T>& lhs, const Vec3<_T>& rhs) {
    return Vec3{lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z};
  }
  template <typename _T>
  inline Vec3<_T> operator*(const Vec3<_T>& lhs, const _T& rhs) {
    return Vec3{lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
  }
  template <typename _T>
  inline Vec3<_T> operator*(const Vec3<_T>& lhs, const Vec3<_T>& rhs) {
    return Vec3{lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
  }

  template <typename _T>
  inline Vec4<_T> operator+(const Vec4<_T>& lhs, const _T& rhs) {
    return Vec4{lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs};
  }
  template <typename _T>
  inline Vec4<_T> operator+(const Vec4<_T>& lhs, const Vec4<_T>& rhs) {
    return Vec4{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w};
  }
  template <typename _T>
  inline Vec4<_T> operator-(const Vec4<_T>& lhs, const _T& rhs) {
    return Vec4{lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs};
  }
  template <typename _T>
  inline Vec4<_T> operator-(const Vec4<_T>& lhs, const Vec4<_T>& rhs) {
    return Vec4{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w};
  }
  template <typename _T>
  inline Vec4<_T> operator/(const Vec4<_T>& lhs, const _T& rhs) {
    return Vec4{lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs};
  }
  template <typename _T>
  inline Vec4<_T> operator/(const Vec4<_T>& lhs, const Vec4<_T>& rhs) {
    return Vec4{lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w};
  }
  template <typename _T>
  inline Vec4<_T> operator*(const Vec4<_T>& lhs, const _T& rhs) {
    return Vec4{lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs};
  }
  template <typename _T>
  inline Vec4<_T> operator*(const Vec4<_T>& lhs, const Vec4<_T>& rhs) {
    return Vec4{lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w};
  }

  template <typename _T>
  inline Vec2<bool> lessThan(const Vec2<_T>& x, const Vec2<_T>& y) {
    return Vec2<bool>{x.x < y.x, x.y < y.y};
  }
  template <typename _T>
  inline Vec3<bool> lessThan(const Vec3<_T>& x, const Vec3<_T>& y) {
    return Vec3<bool>{x.x < y.x, x.y < y.y, x.z < y.z};
  }
  template <typename _T>
  inline Vec4<bool> lessThan(const Vec4<_T>& x, const Vec4<_T>& y) {
    return Vec4<bool>{x.x < y.x, x.y < y.y, x.z < y.z, x.w < y.w};
  }

  template <typename _T>
  inline Vec2<bool> lessThanEqual(const Vec2<_T>& x, const Vec2<_T>& y) {
    return Vec2<bool>{x.x <= y.x, x.y <= y.y};
  }
  template <typename _T>
  inline Vec3<bool> lessThanEqual(const Vec3<_T>& x, const Vec3<_T>& y) {
    return Vec3<bool>{x.x <= y.x, x.y <= y.y, x.z <= y.z};
  }
  template <typename _T>
  inline Vec4<bool> lessThanEqual(const Vec4<_T>& x, const Vec4<_T>& y) {
    return Vec4<bool>{x.x <= y.x, x.y <= y.y, x.z <= y.z, x.w <= y.w};
  }

  template <typename _T>
  inline Vec2<bool> greaterThan(const Vec2<_T>& x, const Vec2<_T>& y) {
    return Vec2<bool>{x.x > y.x, x.y > y.y};
  }
  template <typename _T>
  inline Vec3<bool> greaterThan(const Vec3<_T>& x, const Vec3<_T>& y) {
    return Vec3<bool>{x.x > y.x, x.y > y.y, x.z > y.z};
  }
  template <typename _T>
  inline Vec4<bool> greaterThan(const Vec4<_T>& x, const Vec4<_T>& y) {
    return Vec4<bool>{x.x > y.x, x.y > y.y, x.z > y.z, x.w > y.w};
  }

  template <typename _T>
  inline Vec2<bool> greaterThanEqual(const Vec2<_T>& x, const Vec2<_T>& y) {
    return Vec2<bool>{x.x >= y.x, x.y >= y.y};
  }
  template <typename _T>
  inline Vec3<bool> greaterThanEqual(const Vec3<_T>& x, const Vec3<_T>& y) {
    return Vec3<bool>{x.x >= y.x, x.y >= y.y, x.z >= y.z};
  }
  template <typename _T>
  inline Vec4<bool> greaterThanEqual(const Vec4<_T>& x, const Vec4<_T>& y) {
    return Vec4<bool>{x.x >= y.x, x.y >= y.y, x.z >= y.z, x.w >= y.w};
  }

  template <typename _T>
  inline Vec2<bool> equal(const Vec2<_T>& x, const Vec2<_T>& y) {
    return Vec2<bool>{x.x = y.x, x.y = y.y};
  }
  template <typename _T>
  inline Vec3<bool> equal(const Vec3<_T>& x, const Vec3<_T>& y) {
    return Vec3<bool>{x.x = y.x, x.y = y.y, x.z = y.z};
  }
  template <typename _T>
  inline Vec4<bool> equal(const Vec4<_T>& x, const Vec4<_T>& y) {
    return Vec4<bool>{x.x = y.x, x.y = y.y, x.z = y.z, x.w = y.w};
  }

  template <typename _T>
  inline Vec2<bool> notEqual(const Vec2<_T>& x, const Vec2<_T>& y) {
    return Vec2<bool>{x.x != y.x, x.y != y.y};
  }
  template <typename _T>
  inline Vec3<bool> notEqual(const Vec3<_T>& x, const Vec3<_T>& y) {
    return Vec3<bool>{x.x != y.x, x.y != y.y, x.z != y.z};
  }
  template <typename _T>
  inline Vec4<bool> notEqual(const Vec4<_T>& x, const Vec4<_T>& y) {
    return Vec4<bool>{x.x != y.x, x.y != y.y, x.z != y.z, x.w != y.w};
  }

  template <typename _T>
  inline bool any(const Vec2<_T>& x) {
    return x.x || x.y;
  }
  template <typename _T>
  inline bool any(const Vec3<_T>& x) {
    return x.x || x.y || x.z;
  }
  template <typename _T>
  inline bool any(const Vec4<_T>& x) {
    return x.x || x.y || x.z || x.w;
  }

  template <typename _T>
  inline bool all(const Vec2<_T>& x) {
    return x.x && x.y;
  }
  template <typename _T>
  inline bool all(const Vec3<_T>& x) {
    return x.x && x.y && x.z;
  }
  template <typename _T>
  inline bool all(const Vec4<_T>& x) {
    return x.x && x.y && x.z && x.w;
  }

  inline Vec2<bool> notv(const Vec2<bool>& x) { return Vec2<bool>{!x.x, !x.y}; }
  inline Vec3<bool> notv(const Vec3<bool>& x) {
    return Vec3<bool>{!x.x, !x.y, !x.z};
  }
  inline Vec4<bool> notv(const Vec4<bool>& x) {
    return Vec4<bool>{!x.x, !x.y, !x.z, !x.w};
  }

  typedef Vec2<bool> Vec2b;
  typedef Vec2<int> Vec2i;
  typedef Vec2<float> Vec2f;
  typedef Vec2<double> Vec2d;
  typedef Vec3<bool> Vec3b;
  typedef Vec3<int> Vec3i;
  typedef Vec3<float> Vec3f;
  typedef Vec3<double> Vec3d;
  typedef Vec4<bool> Vec4b;
  typedef Vec4<int> Vec4i;
  typedef Vec4<float> Vec4f;
  typedef Vec4<double> Vec4d;

}  // namespace math
}  // namespace specula

#endif  // SPECULA_MATH_VECTOR_HPP_
