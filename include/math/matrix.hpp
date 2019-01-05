#ifndef SPECULA_MATH_MATRIX_HPP_
#define SPECULA_MATH_MATRIX_HPP_

#include <cmath>
#include <iostream>

#include "vector.hpp"

namespace specula {
namespace math {
  template <typename _T = double>
  struct Mat2;
  template <typename _T = double>
  struct Mat3;
  template <typename _T = double>
  struct Mat4;

  template <typename _T>
  struct Mat2 {
    Mat2() : aa(_T()), ab(_T()), ba(_T()), bb(_T()) {}
    explicit Mat2(const _T& v) : aa(v), ab(_T()), ba(_T()), bb(v) {}
    Mat2(const _T& aa, const _T& ab, const _T& ba, const _T& bb)
        : aa(aa), ab(ab), ba(ba), bb(bb) {}
    Mat2(const Vec2<_T>& r0, const Vec2<_T>& r1)
        : aa(r0.x), ab(r0.y), ba(r1.x), bb(r1.y) {}
    Mat2(const Mat2<_T>& copy)
        : aa(copy.aa), ab(copy.ab), ba(copy.ba), bb(copy.bb) {}

    inline Mat2<_T>& operator=(const Mat2<_T>& mat) {
      aa = mat.aa;
      ab = mat.ab;
      ba = mat.ba;
      bb = mat.bb;
      return *this;
    }

    inline Vec2<_T>& operator[](const std::size_t& r) {
      if (r == 0) {
        return Vec2<_T>{aa, ab};
      } else if (r == 1) {
        return Vec2<_T>{ba, bb};
      } else {
        std::__throw_out_of_range_fmt(
            __N("operator[] (which is %zu) >= __Nr (which is 2)"), r);
      }
    }
    inline _T& operator()(const std::size_t& r, const std::size_t& c) {
      if (r == 0 && c == 0)
        return aa;
      else if (r == 0 && c == 1)
        return ab;
      else if (r == 1 && c == 0)
        return ba;
      else if (r == 1 && c == 1)
        return bb;
      else {
        std::__throw_out_of_range_fmt(
            __N("operator() (which is %zu, %zu) >= __Nr (which is 2)"), r, c);
      }
    }

    Vec2<_T> column(const std::size_t& c) {
      if (c == 0) {
        return Vec2<_T>{aa, ba};
      } else if (c == 1) {
        return Vec2<_T>{ab, bb};
      } else {
        std::__throw_out_of_range_fmt(
            __N("operator[] (which is %zu) >= __Nc (which is 2)"), c);
      }
    }
    Vec2<_T> row(const std::size_t& r) {
      if (r == 0) {
        return Vec2<_T>{aa, ab};
      } else if (r == 1) {
        return Vec2<_T>{ba, bb};
      } else {
        std::__throw_out_of_range_fmt(
            __N("operator[] (which is %zu) >= __Nr (which is 2)"), r);
      }
    }

    void fill(const _T& v) {
      aa = v;
      ab = v;
      ba = v;
      bb = v;
    }
    void diagonal(const _T& v) {
      aa = v;
      bb = v;
    }

    template <typename _U>
    inline Mat2<_T>& operator+=(const _U& rhs) {
      *this = *this + rhs;
      return *this;
    }
    template <typename _U>
    inline Mat2<_T>& operator-=(const _U& rhs) {
      *this = *this - rhs;
      return *this;
    }
    template <typename _U>
    inline Mat2<_T>& operator*=(const _U& rhs) {
      *this = *this * rhs;
      return *this;
    }
    template <typename _U>
    inline Mat2<_T>& operator/=(const _U& rhs) {
      *this = *this / rhs;
      return *this;
    }

    _T aa, ab, ba, bb;
  };

  template <typename _T>
  struct Mat3 {
    Mat3()
        : aa(_T()),
          ab(_T()),
          ac(_T()),
          ba(_T()),
          bb(_T()),
          bc(_T()),
          ca(_T()),
          cb(_T()),
          cc(_T()) {}
    explicit Mat3(const _T& v)
        : aa(v),
          ab(_T()),
          ac(_T()),
          ba(_T()),
          bb(v),
          bc(_T()),
          ca(_T()),
          cb(_T()),
          cc(v) {}
    Mat3(const _T& aa, const _T& ab, const _T& ac, const _T& ba, const _T& bb,
         const _T& bc, const _T& ca, const _T& cb, const _T& cc)
        : aa(aa),
          ab(ab),
          ac(ac),
          ba(ba),
          bb(bb),
          bc(bc),
          ca(ca),
          cb(cb),
          cc(cc) {}
    Mat3(const Vec3<_T>& r0, const Vec3<_T>& r1, const Vec3<_T>& r2)
        : aa(r0.x),
          ab(r0.y),
          ac(r0.z),
          ba(r1.x),
          bb(r1.y),
          bc(r1.z),
          ca(r2.x),
          cb(r2.y),
          cc(r2.z) {}
    Mat3(const Mat3<_T>& copy)
        : aa(copy.aa),
          ab(copy.ab),
          ac(copy.ac),
          ba(copy.ba),
          bb(copy.bb),
          bc(copy.bc),
          ca(copy.ca),
          cb(copy.cb),
          cc(copy.cc) {}

    inline Mat3<_T>& operator=(const Mat3<_T>& mat) {
      aa = mat.aa;
      ab = mat.ab;
      ac = mat.ac;
      ba = mat.ba;
      bb = mat.bb;
      bc = mat.bc;
      ca = mat.ca;
      cb = mat.cb;
      cc = mat.cc;
      return *this;
    }

    inline Vec3<_T>& operator[](const std::size_t& r) {
      if (r == 0) {
        return Vec3<_T>{aa, ab, ac};
      } else if (r == 1) {
        return Vec3<_T>{ba, bb, bc};
      } else if (r == 2) {
        return Vec3<_T>{ca, cb, cc};
      } else {
        std::__throw_out_of_range_fmt(
            __N("operator[] (which is %zu) >= __Nr (which is 3)"), r);
      }
    }
    inline _T& operator()(const std::size_t& r, const std::size_t& c) {
      if (r == 0 && c == 0)
        return aa;
      else if (r == 0 && c == 1)
        return ab;
      else if (r == 0 && c == 2)
        return ac;
      else if (r == 1 && c == 0)
        return ba;
      else if (r == 1 && c == 1)
        return bb;
      else if (r == 1 && c == 2)
        return bc;
      else if (r == 2 && c == 0)
        return ca;
      else if (r == 2 && c == 1)
        return cb;
      else if (r == 2 && c == 2)
        return cc;
      else {
        std::__throw_out_of_range_fmt(
            __N("operator() (which is %zu, %zu) >= __Nr (which is 3)"), r, c);
      }
    }

    inline Vec3<_T> column(const std::size_t& c) {
      if (c == 0) {
        return Vec3<_T>{aa, ba, ca};
      } else if (c == 1) {
        return Vec3<_T>{ab, bb, cb};
      } else if (c == 2) {
        return Vec3<_T>{ac, bc, cc};
      } else {
        std::__throw_out_of_range_fmt(
            __N("operator[] (which is %zu) >= __Nc (which is 3)"), c);
      }
    }
    inline Vec3<_T> row(const std::size_t& r) {
      if (r == 0) {
        return Vec3<_T>{aa, ab, ac};
      } else if (r == 1) {
        return Vec3<_T>{ba, bb, bc};
      } else if (r == 2) {
        return Vec3<_T>{ca, cb, cc};
      } else {
        std::__throw_out_of_range_fmt(
            __N("operator[] (which is %zu) >= __Nr (which is 3)"), r);
      }
    }

    void fill(const _T& v) {
      aa = v;
      ab = v;
      ac = v;
      ba = v;
      bb = v;
      bc = v;
      ca = v;
      cb = v;
      cc = v;
    }
    void diagonal(const _T& v) {
      aa = v;
      bb = v;
      cc = v;
    }

    template <typename _U>
    inline Mat3<_T>& operator+=(const _U& rhs) {
      *this = *this + rhs;
      return *this;
    }
    template <typename _U>
    inline Mat3<_T>& operator-=(const _U& rhs) {
      *this = *this - rhs;
      return *this;
    }
    template <typename _U>
    inline Mat3<_T>& operator*=(const _U& rhs) {
      *this = *this * rhs;
      return *this;
    }
    template <typename _U>
    inline Mat3<_T>& operator/=(const _U& rhs) {
      *this = *this / rhs;
      return *this;
    }

    _T aa, ab, ac, ba, bb, bc, ca, cb, cc;
  };

  template <typename _T>
  struct Mat4 {
    Mat4()
        : aa(_T()),
          ab(_T()),
          ac(_T()),
          ad(_T()),
          ba(_T()),
          bb(_T()),
          bc(_T()),
          bd(_T()),
          ca(_T()),
          cb(_T()),
          cc(_T()),
          cd(_T()),
          da(_T()),
          db(_T()),
          dc(_T()),
          dd(_T()) {}
    explicit Mat4(const _T& v)
        : aa(v),
          ab(_T()),
          ac(_T()),
          ad(_T()),
          ba(_T()),
          bb(v),
          bc(_T()),
          bd(_T()),
          ca(_T()),
          cb(_T()),
          cc(v),
          cd(_T()),
          da(_T()),
          db(_T()),
          dc(_T()),
          dd(v) {}
    Mat4(const _T& aa, const _T& ab, const _T& ac, const _T& ad, const _T& ba,
         const _T& bb, const _T& bc, const _T& bd, const _T& ca, const _T& cb,
         const _T& cc, const _T& cd, const _T& da, const _T& db, const _T& dc,
         const _T& dd)
        : aa(aa),
          ab(ab),
          ac(ac),
          ad(ad),
          ba(ba),
          bb(bb),
          bc(bc),
          bd(bd),
          ca(ca),
          cb(cb),
          cc(cc),
          cd(cd),
          da(da),
          db(db),
          dc(dc),
          dd(dd) {}
    Mat4(const Vec4<_T>& r0, const Vec4<_T>& r1, const Vec4<_T>& r2,
         const Vec4<_T>& r3)
        : aa(r0.x),
          ab(r0.y),
          ac(r0.z),
          ad(r0.w),
          ba(r1.x),
          bb(r1.y),
          bc(r1.z),
          bd(r1.w),
          ca(r2.x),
          cb(r2.y),
          cc(r2.z),
          cd(r2.w),
          da(r3.x),
          db(r3.y),
          dc(r3.z),
          dd(r3.w) {}
    Mat4(const Mat4<_T>& copy)
        : aa(copy.aa),
          ab(copy.ab),
          ac(copy.ac),
          ad(copy.ad),
          ba(copy.ba),
          bb(copy.bb),
          bc(copy.bc),
          bd(copy.bd),
          ca(copy.ca),
          cb(copy.cb),
          cc(copy.cc),
          cd(copy.cd),
          da(copy.da),
          db(copy.db),
          dc(copy.dc),
          dd(copy.dd) {}

    inline Mat4<_T>& operator=(const Mat4<_T>& mat) {
      aa = mat.aa;
      ab = mat.ab;
      ac = mat.ac;
      ad = mat.ad;
      ba = mat.ba;
      bb = mat.bb;
      bc = mat.bc;
      bd = mat.bd;
      ca = mat.ca;
      cb = mat.cb;
      cc = mat.cc;
      cd = mat.cd;
      da = mat.da;
      db = mat.db;
      dc = mat.dc;
      dd = mat.dd;
      return *this;
    }

    inline Vec4<_T>& operator[](const std::size_t& r) {
      if (r == 0) {
        return Vec4<_T>{aa, ab, ac, ad};
      } else if (r == 1) {
        return Vec4<_T>{ba, bb, bc, bd};
      } else if (r == 2) {
        return Vec4<_T>{ca, cb, cc, cd};
      } else if (r == 3) {
        return Vec4<_T>{da, db, dc, dd};
      } else {
        std::__throw_out_of_range_fmt(
            __N("operator[] (which is %zu) >= __Nr (which is 4)"), r);
      }
    }
    inline _T& operator()(const std::size_t& r, const std::size_t& c) {
      if (r == 0 && c == 0)
        return aa;
      else if (r == 0 && c == 1)
        return ab;
      else if (r == 0 && c == 2)
        return ac;
      else if (r == 0 && c == 3)
        return ad;
      else if (r == 1 && c == 0)
        return ba;
      else if (r == 1 && c == 1)
        return bb;
      else if (r == 1 && c == 2)
        return bc;
      else if (r == 1 && c == 3)
        return bd;
      else if (r == 2 && c == 0)
        return ca;
      else if (r == 2 && c == 1)
        return cb;
      else if (r == 2 && c == 2)
        return cc;
      else if (r == 2 && c == 3)
        return cd;
      else if (r == 3 && c == 0)
        return da;
      else if (r == 3 && c == 1)
        return db;
      else if (r == 3 && c == 2)
        return dc;
      else if (r == 3 && c == 3)
        return dd;
      else {
        std::__throw_out_of_range_fmt(
            __N("operator() (which is %zu, %zu) >= __Nr (which is 4)"), r, c);
      }
    }

    inline Vec4<_T> column(const std::size_t& c) {
      if (c == 0) {
        return Vec4<_T>{aa, ba, ca, da};
      } else if (c == 1) {
        return Vec4<_T>{ab, bb, cb, db};
      } else if (c == 2) {
        return Vec4<_T>{ac, bc, cc, dc};
      } else if (c == 3) {
        return Vec4<_T>{ad, bd, cd, dd};
      } else {
        std::__throw_out_of_range_fmt(
            __N("operator[] (which is %zu) >= __Nc (which is 4)"), c);
      }
    }
    inline Vec4<_T> row(const std::size_t& r) {
      if (r == 0) {
        return Vec4<_T>{aa, ab, ac, ad};
      } else if (r == 1) {
        return Vec4<_T>{ba, bb, bc, bd};
      } else if (r == 2) {
        return Vec4<_T>{ca, cb, cc, cd};
      } else if (r == 3) {
        return Vec4<_T>{da, db, dc, dd};
      } else {
        std::__throw_out_of_range_fmt(
            __N("operator[] (which is %zu) >= __Nr (which is 4)"), r);
      }
    }

    void fill(const _T& v) {
      aa = v;
      ab = v;
      ac = v;
      ad = v;
      ba = v;
      bb = v;
      bc = v;
      bd = v;
      ca = v;
      cb = v;
      cc = v;
      cd = v;
      da = v;
      db = v;
      dc = v;
      dd = v;
    }
    void diagonal(const _T& v) {
      aa = v;
      bb = v;
      cc = v;
      dd = v;
    }

    template <typename _U>
    inline Mat4<_T>& operator+=(const _U& rhs) {
      *this = *this + rhs;
      return *this;
    }
    template <typename _U>
    inline Mat4<_T>& operator-=(const _U& rhs) {
      *this = *this - rhs;
      return *this;
    }
    template <typename _U>
    inline Mat4<_T>& operator*=(const _U& rhs) {
      *this = *this * rhs;
      return *this;
    }
    template <typename _U>
    inline Mat4<_T>& operator/=(const _U& rhs) {
      *this = *this / rhs;
      return *this;
    }

    _T aa, ab, ac, ad, ba, bb, bc, bd, ca, cb, cc, cd, da, db, dc, dd;
  };

  template <typename _T>
  inline std::ostream& operator<<(std::ostream& out, const Mat2<_T>& mat) {
    out << "[[" << mat.aa << ',' << mat.ab << "][" << mat.ba << ',' << mat.bb
        << "]]";
    return out;
  }
  template <typename _T>
  inline std::ostream& operator<<(std::ostream& out, const Mat3<_T>& mat) {
    out << "[[" << mat.aa << ',' << mat.ab << ',' << mat.ac << "][" << mat.ba
        << ',' << mat.bb << ',' << mat.bc << "][" << mat.ca << ',' << mat.cb
        << ',' << mat.cc << "]]";
    return out;
  }
  template <typename _T>
  inline std::ostream& operator<<(std::ostream& out, const Mat4<_T>& mat) {
    out << "[[" << mat.aa << ',' << mat.ab << ',' << mat.ac << ',' << mat.ad
        << "][" << mat.ba << ',' << mat.bb << ',' << mat.bc << ',' << mat.bd
        << "][" << mat.ca << ',' << mat.cb << ',' << mat.cc << ',' << mat.cd
        << "][" << mat.da << ',' << mat.db << ',' << mat.dc << ',' << mat.dd
        << "]]";
    return out;
  }

  template <typename _T>
  inline bool operator==(const Mat2<_T>& lhs, const Mat2<_T>& rhs) {
    return lhs.aa == rhs.aa && lhs.ab == rhs.ab && lhs.ba == rhs.ba &&
           lhs.bb == rhs.bb;
  }
  template <typename _T>
  inline bool operator!=(const Mat2<_T>& lhs, const Mat2<_T>& rhs) {
    return !(lhs == rhs);
  }

  template <typename _T>
  inline bool operator==(const Mat3<_T>& lhs, const Mat3<_T>& rhs) {
    return lhs.aa == rhs.aa && lhs.ab == rhs.ab && lhs.ac == rhs.ac &&
           lhs.ba == rhs.ba && lhs.bb == rhs.bb && lhs.bc == rhs.bc &&
           lhs.ca == rhs.ca && lhs.cb == rhs.cb && lhs.cc == rhs.cc;
  }
  template <typename _T>
  inline bool operator!=(const Mat3<_T>& lhs, const Mat3<_T>& rhs) {
    return !(lhs == rhs);
  }

  template <typename _T>
  inline bool operator==(const Mat4<_T>& lhs, const Mat4<_T>& rhs) {
    return lhs.aa == rhs.aa && lhs.ab == rhs.ab && lhs.ac == rhs.ac &&
           lhs.ad == rhs.ad && lhs.ba == rhs.ba && lhs.bb == rhs.bb &&
           lhs.bc == rhs.bc && lhs.bd == rhs.bd && lhs.ca == rhs.ca &&
           lhs.cb == rhs.cb && lhs.cc == rhs.cc && lhs.cd == rhs.cd &&
           lhs.da == rhs.da && lhs.db == rhs.db && lhs.dc == rhs.dc &&
           lhs.dd == rhs.dd;
  }
  template <typename _T>
  inline bool operator!=(const Mat4<_T>& lhs, const Mat4<_T>& rhs) {
    return !(lhs == rhs);
  }

  template <typename _T>
  inline Mat2<_T> operator+(const Mat2<_T>& lhs, const _T& rhs) {
    return Mat2{lhs.aa + rhs, lhs.ab + rhs, lhs.ba + rhs, lhs.bb + rhs};
  }
  template <typename _T>
  inline Mat2<_T> operator+(const Mat2<_T>& lhs, const Mat2<_T>& rhs) {
    return Mat2{lhs.aa + rhs.aa, lhs.ab + rhs.ab, lhs.ba + rhs.ba,
                lhs.bb + rhs.bb};
  }
  template <typename _T>
  inline Mat2<_T> operator-(const Mat2<_T>& lhs, const _T& rhs) {
    return Mat2{lhs.aa - rhs, lhs.ab - rhs, lhs.ba - rhs, lhs.bb - rhs};
  }
  template <typename _T>
  inline Mat2<_T> operator-(const Mat2<_T>& lhs, const Mat2<_T>& rhs) {
    return Mat2{lhs.aa - rhs.aa, lhs.ab - rhs.ab, lhs.ba - rhs.ba,
                lhs.bb - rhs.bb};
  }
  template <typename _T>
  inline Mat2<_T> operator*(const Mat2<_T>& lhs, const _T& rhs) {
    return Mat2{lhs.aa * rhs, lhs.ab * rhs, lhs.ba * rhs, lhs.bb * rhs};
  }
  template <typename _T>
  inline Mat2<_T> operator*(const Mat2<_T>& lhs, const Mat2<_T>& rhs) {
    return Mat2<_T>{
        lhs.aa * rhs.aa + lhs.ab * rhs.ba, lhs.aa * rhs.ab + lhs.ab * rhs.bb,
        lhs.ba * rhs.aa + lhs.bb * rhs.ba, lhs.ba * rhs.ab + lhs.bb * rhs.bb};
  }
  template <typename _T>
  inline Vec2<_T> operator*(const Mat2<_T>& lhs, const Vec2<_T>& rhs) {
    return Vec2<_T>{lhs.aa * rhs.x + lhs.ab * rhs.y,
                    lhs.ba * rhs.x + lhs.bb * rhs.y};
  }
  template <typename _T>
  inline Mat2<_T> operator/(const Mat2<_T>& lhs, const _T& rhs) {
    return Mat2{lhs.aa / rhs, lhs.ab / rhs, lhs.ba / rhs, lhs.bb / rhs};
  }
  template <typename _T>
  inline Mat2<_T> operator/(const Mat2<_T>& lhs, const Mat2<_T>& rhs) {
    return Mat2{lhs.aa / rhs.aa, lhs.ab / rhs.ab, lhs.ba / rhs.ba,
                lhs.bb / rhs.bb};
  }

  template <typename _T>
  inline Mat3<_T> operator+(const Mat3<_T>& lhs, const _T& rhs) {
    return Mat3{lhs.aa + rhs, lhs.ab + rhs, lhs.ac + rhs,
                lhs.ba + rhs, lhs.bb + rhs, lhs.bc + rhs,
                lhs.ca + rhs, lhs.cb + rhs, lhs.cc + rhs};
  }
  template <typename _T>
  inline Mat3<_T> operator+(const Mat3<_T>& lhs, const Mat3<_T>& rhs) {
    return Mat3{lhs.aa + rhs.aa, lhs.ab + rhs.ab, lhs.ac + rhs.ac,
                lhs.ba + rhs.ba, lhs.bb + rhs.bb, lhs.bc + rhs.bc,
                lhs.ca + rhs.ca, lhs.cb + rhs.cb, lhs.cc + rhs.cc};
  }
  template <typename _T>
  inline Mat3<_T> operator-(const Mat3<_T>& lhs, const _T& rhs) {
    return Mat3{lhs.aa - rhs, lhs.ab - rhs, lhs.ac - rhs,
                lhs.ba - rhs, lhs.bb - rhs, lhs.bc - rhs,
                lhs.ca - rhs, lhs.cb - rhs, lhs.cc - rhs};
  }
  template <typename _T>
  inline Mat3<_T> operator-(const Mat3<_T>& lhs, const Mat3<_T>& rhs) {
    return Mat3{lhs.aa - rhs.aa, lhs.ab - rhs.ab, lhs.ac - rhs.ac,
                lhs.ba - rhs.ba, lhs.bb - rhs.bb, lhs.bc - rhs.bc,
                lhs.ca - rhs.ca, lhs.cb - rhs.cb, lhs.cc - rhs.cc};
  }
  template <typename _T>
  inline Mat3<_T> operator*(const Mat3<_T>& lhs, const _T& rhs) {
    return Mat3{lhs.aa * rhs, lhs.ab * rhs, lhs.ac * rhs,
                lhs.ba * rhs, lhs.bb * rhs, lhs.bc * rhs,
                lhs.ca * rhs, lhs.cb * rhs, lhs.cc * rhs};
  }
  template <typename _T>
  inline Mat3<_T> operator*(const Mat3<_T>& lhs, const Mat3<_T>& rhs) {
    return Mat3<_T>{
        lhs.aa * rhs.aa + lhs.ab * rhs.ba + lhs.ac * rhs.ca,
        lhs.aa * rhs.ab + lhs.ab * rhs.bb + lhs.ac * rhs.cb,
        lhs.aa * rhs.ac + lhs.ab * rhs.bc + lhs.ac * rhs.cc,
        lhs.ba * rhs.aa + lhs.bb * rhs.ba + lhs.bc * rhs.ca,
        lhs.ba * rhs.ab + lhs.bb * rhs.bb + lhs.bc * rhs.cb,
        lhs.ba * rhs.ac + lhs.bb * rhs.bc + lhs.bc * rhs.cc,
        lhs.ca * rhs.aa + lhs.cb * rhs.ba + lhs.cc * rhs.ca,
        lhs.ca * rhs.ab + lhs.cb * rhs.bb + lhs.cc * rhs.cb,
        lhs.ca * rhs.ac + lhs.cb * rhs.bc + lhs.cc * rhs.cc,
    };
  }
  template <typename _T>
  inline Vec3<_T> operator*(const Mat3<_T>& lhs, const Vec2<_T>& rhs) {
    return Vec3<_T>{lhs.aa * rhs.x + lhs.ab * rhs.y,
                    lhs.ba * rhs.x + lhs.bb * rhs.y,
                    lhs.ca * rhs.x + lhs.cb * rhs.y};
  }
  template <typename _T>
  inline Vec3<_T> operator*(const Mat3<_T>& lhs, const Vec3<_T>& rhs) {
    return Vec3<_T>{lhs.aa * rhs.x + lhs.ab * rhs.y + lhs.ac * rhs.z,
                    lhs.ba * rhs.x + lhs.bb * rhs.y + lhs.bc * rhs.z,
                    lhs.ca * rhs.x + lhs.cb * rhs.y + lhs.cc * rhs.z};
  }
  template <typename _T>
  inline Mat3<_T> operator/(const Mat3<_T>& lhs, const _T& rhs) {
    return Mat3{lhs.aa / rhs, lhs.ab / rhs, lhs.ac / rhs,
                lhs.ba / rhs, lhs.bb / rhs, lhs.bc / rhs,
                lhs.ca / rhs, lhs.cb / rhs, lhs.cc / rhs};
  }
  template <typename _T>
  inline Mat3<_T> operator/(const Mat3<_T>& lhs, const Mat3<_T>& rhs) {
    return Mat3{lhs.aa / rhs.aa, lhs.ab / rhs.ab, lhs.ac / rhs.ac,
                lhs.ba / rhs.ba, lhs.bb / rhs.bb, lhs.bc / rhs.bc,
                lhs.ca / rhs.ca, lhs.cb / rhs.cb, lhs.cc / rhs.cc};
  }

  template <typename _T>
  inline Mat4<_T> operator+(const Mat4<_T>& lhs, const _T& rhs) {
    return Mat4{lhs.aa + rhs, lhs.ab + rhs, lhs.ac + rhs, lhs.ad + rhs,
                lhs.ba + rhs, lhs.bb + rhs, lhs.bc + rhs, lhs.bd + rhs,
                lhs.ca + rhs, lhs.cb + rhs, lhs.cc + rhs, lhs.cd + rhs,
                lhs.da + rhs, lhs.db + rhs, lhs.dc + rhs, lhs.dd + rhs};
  }
  template <typename _T>
  inline Mat4<_T> operator+(const Mat4<_T>& lhs, const Mat4<_T>& rhs) {
    return Mat4{
        lhs.aa + rhs.aa, lhs.ab + rhs.ab, lhs.ac + rhs.ac, lhs.ad + rhs.ad,
        lhs.ba + rhs.ba, lhs.bb + rhs.bb, lhs.bc + rhs.bc, lhs.bd + rhs.bd,
        lhs.ca + rhs.ca, lhs.cb + rhs.cb, lhs.cc + rhs.cc, lhs.cd + rhs.cd,
        lhs.da + rhs.da, lhs.db + rhs.db, lhs.dc + rhs.dc, lhs.dd + rhs.dd};
  }
  template <typename _T>
  inline Mat4<_T> operator-(const Mat4<_T>& lhs, const _T& rhs) {
    return Mat4{lhs.aa - rhs, lhs.ab - rhs, lhs.ac - rhs, lhs.ad - rhs,
                lhs.ba - rhs, lhs.bb - rhs, lhs.bc - rhs, lhs.bd - rhs,
                lhs.ca - rhs, lhs.cb - rhs, lhs.cc - rhs, lhs.cd - rhs,
                lhs.da - rhs, lhs.db - rhs, lhs.dc - rhs, lhs.dd - rhs};
  }
  template <typename _T>
  inline Mat4<_T> operator-(const Mat4<_T>& lhs, const Mat4<_T>& rhs) {
    return Mat4{
        lhs.aa - rhs.aa, lhs.ab - rhs.ab, lhs.ac - rhs.ac, lhs.ad - rhs.ad,
        lhs.ba - rhs.ba, lhs.bb - rhs.bb, lhs.bc - rhs.bc, lhs.bd - rhs.bd,
        lhs.ca - rhs.ca, lhs.cb - rhs.cb, lhs.cc - rhs.cc, lhs.cd - rhs.cd,
        lhs.da - rhs.da, lhs.db - rhs.db, lhs.dc - rhs.dc, lhs.dd - rhs.dd};
  }
  template <typename _T>
  inline Mat4<_T> operator*(const Mat4<_T>& lhs, const _T& rhs) {
    return Mat4{lhs.aa * rhs, lhs.ab * rhs, lhs.ac * rhs, lhs.ad * rhs,
                lhs.ba * rhs, lhs.bb * rhs, lhs.bc * rhs, lhs.bd * rhs,
                lhs.ca * rhs, lhs.cb * rhs, lhs.cc * rhs, lhs.cd * rhs,
                lhs.da * rhs, lhs.db * rhs, lhs.dc * rhs, lhs.dd * rhs};
  }
  template <typename _T>
  inline Mat4<_T> operator*(const Mat4<_T>& lhs, const Mat4<_T>& rhs) {
    return Mat4<_T>{
        lhs.aa * rhs.aa + lhs.ab * rhs.ba + lhs.ac * rhs.ca + lhs.ad * rhs.da,
        lhs.aa * rhs.ab + lhs.ab * rhs.bb + lhs.ac * rhs.cb + lhs.ad * rhs.db,
        lhs.aa * rhs.ac + lhs.ab * rhs.bc + lhs.ac * rhs.cc + lhs.ad * rhs.dc,
        lhs.aa * rhs.ad + lhs.ab * rhs.bd + lhs.ac * rhs.cd + lhs.ad * rhs.dd,
        lhs.ba * rhs.aa + lhs.bb * rhs.ba + lhs.bc * rhs.ca + lhs.bd * rhs.da,
        lhs.ba * rhs.ab + lhs.bb * rhs.bb + lhs.bc * rhs.cb + lhs.bd * rhs.db,
        lhs.ba * rhs.ac + lhs.bb * rhs.bc + lhs.bc * rhs.cc + lhs.bd * rhs.dc,
        lhs.ba * rhs.ad + lhs.bb * rhs.bd + lhs.bc * rhs.cd + lhs.bd * rhs.dd,
        lhs.ca * rhs.aa + lhs.cb * rhs.ba + lhs.cc * rhs.ca + lhs.cd * rhs.da,
        lhs.ca * rhs.ab + lhs.cb * rhs.bb + lhs.cc * rhs.cb + lhs.cd * rhs.db,
        lhs.ca * rhs.ac + lhs.cb * rhs.bc + lhs.cc * rhs.cc + lhs.cd * rhs.dc,
        lhs.ca * rhs.ad + lhs.cb * rhs.bd + lhs.cc * rhs.cd + lhs.cd * rhs.dd,
        lhs.da * rhs.aa + lhs.db * rhs.ba + lhs.dc * rhs.ca + lhs.dd * rhs.da,
        lhs.da * rhs.ab + lhs.db * rhs.bb + lhs.dc * rhs.cb + lhs.dd * rhs.db,
        lhs.da * rhs.ac + lhs.db * rhs.bc + lhs.dc * rhs.cc + lhs.dd * rhs.dc,
        lhs.da * rhs.ad + lhs.db * rhs.bd + lhs.dc * rhs.cd + lhs.dd * rhs.dd,
    };
  }
  template <typename _T>
  inline Vec4<_T> operator*(const Mat4<_T>& lhs, const Vec2<_T>& rhs) {
    return Vec4<_T>{
        lhs.aa * rhs.x + lhs.ab * rhs.y, lhs.ba * rhs.x + lhs.bb * rhs.y,
        lhs.ca * rhs.x + lhs.cb * rhs.y, lhs.da * rhs.x + lhs.db * rhs.y};
  }
  template <typename _T>
  inline Vec4<_T> operator*(const Mat4<_T>& lhs, const Vec3<_T>& rhs) {
    return Vec4<_T>{lhs.aa * rhs.x + lhs.ab * rhs.y + lhs.ac * rhs.z,
                    lhs.ba * rhs.x + lhs.bb * rhs.y + lhs.bc * rhs.z,
                    lhs.ca * rhs.x + lhs.cb * rhs.y + lhs.cc * rhs.z,
                    lhs.da * rhs.x + lhs.db * rhs.y + lhs.dc * rhs.z};
  }
  template <typename _T>
  inline Vec4<_T> operator*(const Mat4<_T>& lhs, const Vec4<_T>& rhs) {
    return Vec4<_T>{
        lhs.aa * rhs.x + lhs.ab * rhs.y + lhs.ac * rhs.z + lhs.ad * rhs.w,
        lhs.ba * rhs.x + lhs.bb * rhs.y + lhs.bc * rhs.z + lhs.bd * rhs.w,
        lhs.ca * rhs.x + lhs.cb * rhs.y + lhs.cc * rhs.z + lhs.cd * rhs.w,
        lhs.da * rhs.x + lhs.db * rhs.y + lhs.dc * rhs.z + lhs.dd * rhs.w};
  }
  template <typename _T>
  inline Mat4<_T> operator/(const Mat4<_T>& lhs, const _T& rhs) {
    return Mat4{lhs.aa / rhs, lhs.ab / rhs, lhs.ac / rhs, lhs.ad / rhs,
                lhs.ba / rhs, lhs.bb / rhs, lhs.bc / rhs, lhs.bd / rhs,
                lhs.ca / rhs, lhs.cb / rhs, lhs.cc / rhs, lhs.cd / rhs,
                lhs.da / rhs, lhs.db / rhs, lhs.dc / rhs, lhs.dd / rhs};
  }
  template <typename _T>
  inline Mat4<_T> operator/(const Mat4<_T>& lhs, const Mat4<_T>& rhs) {
    return Mat4{
        lhs.aa / rhs.aa, lhs.ab / rhs.ab, lhs.ac / rhs.ac, lhs.ad / rhs.ad,
        lhs.ba / rhs.ba, lhs.bb / rhs.bb, lhs.bc / rhs.bc, lhs.bd / rhs.bd,
        lhs.ca / rhs.ca, lhs.cb / rhs.cb, lhs.cc / rhs.cc, lhs.cd / rhs.cd,
        lhs.da / rhs.da, lhs.db / rhs.db, lhs.dc / rhs.dc, lhs.dd / rhs.dd};
  }

  typedef Mat2<bool> Mat2b;
  typedef Mat2<int> Mat2i;
  typedef Mat2<float> Mat2f;
  typedef Mat2<double> Mat2d;
  typedef Mat3<bool> Mat3b;
  typedef Mat3<int> Mat3i;
  typedef Mat3<float> Mat3f;
  typedef Mat3<double> Mat3d;
  typedef Mat4<bool> Mat4b;
  typedef Mat4<int> Mat4i;
  typedef Mat4<float> Mat4f;
  typedef Mat4<double> Mat4d;
}  // namespace math
}  // namespace specula

#endif  // SPECULA_MATH_MATRIX_HPP_
