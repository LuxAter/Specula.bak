#ifndef SPECULA_MATH_VECTOR_HPP_
#define SPECULA_MATH_VECTOR_HPP_

#include <iostream>

namespace specula {
namespace math {
  template <typename _T = double>
  class vec2;
  template <typename _T = double>
  class vec3;
  template <typename _T = double>
  class vec4;

  template <typename _T>
  class vec2 {
   public:
    vec2() : x(_T()), y(_T()) {}
    vec2(const _T& a) : x(a), y(a) {}
    vec2(const _T& a, const _T& b) : x(a), y(b) {}
    vec2(const vec2<_T>& v) : x(v.x), y(v.y) {}
    vec2(const vec3<_T>& v) : x(v.x), y(v.y) {}
    vec2(const vec4<_T>& v) : x(v.x), y(v.y) {}

    template <typename _U>
    inline vec2<_T>& operator+=(const _U& rhs) {
      x += rhs;
      y += rhs;
      return *this;
    }
    template <typename _U>
    inline vec2<_T>& operator+=(const vec2<_U>& rhs) {
      x += rhs.x;
      y += rhs.y;
      return *this;
    }
    template <typename _U>
    inline vec2<_T>& operator+=(const vec3<_U>& rhs) {
      x += rhs.x;
      y += rhs.y;
      return *this;
    }
    template <typename _U>
    inline vec2<_T>& operator+=(const vec4<_U>& rhs) {
      x += rhs.x;
      y += rhs.y;
      return *this;
    }
    template <typename _U>
    inline vec2<_T>& operator-=(const _U& rhs) {
      x -= rhs;
      y -= rhs;
      return *this;
    }
    template <typename _U>
    inline vec2<_T>& operator-=(const vec2<_U>& rhs) {
      x -= rhs.x;
      y -= rhs.y;
      return *this;
    }
    template <typename _U>
    inline vec2<_T>& operator-=(const vec3<_U>& rhs) {
      x -= rhs.x;
      y -= rhs.y;
      return *this;
    }
    template <typename _U>
    inline vec2<_T>& operator-=(const vec4<_U>& rhs) {
      x -= rhs.x;
      y -= rhs.y;
      return *this;
    }
    template <typename _U>
    inline vec2<_T>& operator*=(const _U& rhs) {
      x *= rhs;
      y *= rhs;
      return *this;
    }
    template <typename _U>
    inline vec2<_T>& operator*=(const vec2<_U>& rhs) {
      x *= rhs.x;
      y *= rhs.y;
      return *this;
    }
    template <typename _U>
    inline vec2<_T>& operator*=(const vec3<_U>& rhs) {
      x *= rhs.x;
      y *= rhs.y;
      return *this;
    }
    template <typename _U>
    inline vec2<_T>& operator*=(const vec4<_U>& rhs) {
      x *= rhs.x;
      y *= rhs.y;
      return *this;
    }
    template <typename _U>
    inline vec2<_T>& operator/=(const _U& rhs) {
      x /= rhs;
      y /= rhs;
      return *this;
    }
    template <typename _U>
    inline vec2<_T>& operator/=(const vec2<_U>& rhs) {
      x /= rhs.x;
      y /= rhs.y;
      return *this;
    }
    template <typename _U>
    inline vec2<_T>& operator/=(const vec3<_U>& rhs) {
      x /= rhs.x;
      y /= rhs.y;
      return *this;
    }
    template <typename _U>
    inline vec2<_T>& operator/=(const vec4<_U>& rhs) {
      x /= rhs.x;
      y /= rhs.y;
      return *this;
    }

    _T x, y;
  };
  template <typename _T>
  class vec3 {
   public:
    vec3() : x(_T()), y(_T()), z(_T()) {}
    vec3(const _T& a) : x(a), y(a), z(a) {}
    vec3(const _T& a, const _T& b) : x(a), y(b), z(_T()) {}
    vec3(const _T& a, const _T& b, const _T& c) : x(a), y(b), z(c) {}
    vec3(const vec2<_T>& v) : x(v.x), y(v.y), z(_T()) {}
    vec3(const vec2<_T>& v, const _T& c) : x(v.x), y(v.y), z(c) {}
    vec3(const vec3<_T>& v) : x(v.x), y(v.y), z(v.z) {}
    vec3(const vec4<_T>& v) : x(v.x), y(v.y), z(v.z) {}

    inline vec2<_T> xx() const {return vec2<_T>(x, x);}
    inline vec2<_T> xy() const {return vec2<_T>(x, y);}
    inline vec2<_T> xz() const {return vec2<_T>(x, z);}
    inline vec2<_T> yx() const {return vec2<_T>(y, x);}
    inline vec2<_T> yy() const {return vec2<_T>(y, y);}
    inline vec2<_T> yz() const {return vec2<_T>(y, z);}
    inline vec2<_T> zx() const {return vec2<_T>(z, x);}
    inline vec2<_T> zy() const {return vec2<_T>(z, y);}
    inline vec2<_T> zz() const {return vec2<_T>(z, z);}

    template <typename _U>
    inline vec3<_T>& operator+=(const _U& rhs) {
      x += rhs;
      y += rhs;
      z += rhs;
      return *this;
    }
    template <typename _U>
    inline vec3<_T>& operator+=(const vec3<_U>& rhs) {
      x += rhs.x;
      y += rhs.y;
      z += rhs.z;
      return *this;
    }
    template <typename _U>
    inline vec3<_T>& operator+=(const vec4<_U>& rhs) {
      x += rhs.x;
      y += rhs.y;
      z += rhs.z;
      return *this;
    }
    template <typename _U>
    inline vec3<_T>& operator-=(const _U& rhs) {
      x -= rhs;
      y -= rhs;
      z -= rhs;
      return *this;
    }
    template <typename _U>
    inline vec3<_T>& operator-=(const vec3<_U>& rhs) {
      x -= rhs.x;
      y -= rhs.y;
      z -= rhs.z;
      return *this;
    }
    template <typename _U>
    inline vec3<_T>& operator-=(const vec4<_U>& rhs) {
      x -= rhs.x;
      y -= rhs.y;
      z -= rhs.z;
      return *this;
    }
    template <typename _U>
    inline vec3<_T>& operator*=(const _U& rhs) {
      x *= rhs;
      y *= rhs;
      z *= rhs;
      return *this;
    }
    template <typename _U>
    inline vec3<_T>& operator*=(const vec3<_U>& rhs) {
      x *= rhs.x;
      y *= rhs.y;
      z *= rhs.z;
      return *this;
    }
    template <typename _U>
    inline vec3<_T>& operator*=(const vec4<_U>& rhs) {
      x *= rhs.x;
      y *= rhs.y;
      z *= rhs.z;
      return *this;
    }
    template <typename _U>
    inline vec3<_T>& operator/=(const _U& rhs) {
      x /= rhs;
      y /= rhs;
      z /= rhs;
      return *this;
    }
    template <typename _U>
    inline vec3<_T>& operator/=(const vec3<_U>& rhs) {
      x /= rhs.x;
      y /= rhs.y;
      z /= rhs.z;
      return *this;
    }
    template <typename _U>
    inline vec3<_T>& operator/=(const vec4<_U>& rhs) {
      x /= rhs.x;
      y /= rhs.y;
      z /= rhs.z;
      return *this;
    }

    _T x, y, z;
  };
  template <typename _T>
  class vec4 {
   public:
    vec4() : x(_T()), y(_T()), z(_T()), w(_T()) {}
    vec4(const _T& a) : x(a), y(a), z(a), w(a) {}
    vec4(const _T& a, const _T& b) : x(a), y(b), z(_T()), w(_T()) {}
    vec4(const _T& a, const _T& b, const _T& c) : x(a), y(b), z(c), w(_T()) {}
    vec4(const _T& a, const _T& b, const _T& c, const _T& d)
        : x(a), y(b), z(c), w(d) {}
    vec4(const vec2<_T>& v) : x(v.x), y(v.y), z(_T()), w(_T()) {}
    vec4(const vec3<_T>& v) : x(v.x), y(v.y), z(v.z), w(_T()) {}
    vec4(const vec4<_T>& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

    inline vec3<_T> xxx() const {return vec3<_T>(x,x,x);}
    inline vec3<_T> xxy() const {return vec3<_T>(x,x,y);}
    inline vec3<_T> xxz() const {return vec3<_T>(x,x,z);}
    inline vec3<_T> xxw() const {return vec3<_T>(x,x,w);}
    inline vec3<_T> xyx() const {return vec3<_T>(x,y,x);}
    inline vec3<_T> xyy() const {return vec3<_T>(x,y,y);}
    inline vec3<_T> xyz() const {return vec3<_T>(x,y,z);}
    inline vec3<_T> xyw() const {return vec3<_T>(x,y,w);}
    inline vec3<_T> xzx() const {return vec3<_T>(x,z,x);}
    inline vec3<_T> xzy() const {return vec3<_T>(x,z,y);}
    inline vec3<_T> xzz() const {return vec3<_T>(x,z,z);}
    inline vec3<_T> xzw() const {return vec3<_T>(x,z,w);}
    inline vec3<_T> xwx() const {return vec3<_T>(x,w,x);}
    inline vec3<_T> xwy() const {return vec3<_T>(x,w,y);}
    inline vec3<_T> xwz() const {return vec3<_T>(x,w,z);}
    inline vec3<_T> xww() const {return vec3<_T>(x,w,w);}

    inline vec3<_T> yxx() const {return vec3<_T>(y,x,x);}
    inline vec3<_T> yxy() const {return vec3<_T>(y,x,y);}
    inline vec3<_T> yxz() const {return vec3<_T>(y,x,z);}
    inline vec3<_T> yxw() const {return vec3<_T>(y,x,w);}
    inline vec3<_T> yyx() const {return vec3<_T>(y,y,x);}
    inline vec3<_T> yyy() const {return vec3<_T>(y,y,y);}
    inline vec3<_T> yyz() const {return vec3<_T>(y,y,z);}
    inline vec3<_T> yyw() const {return vec3<_T>(y,y,w);}
    inline vec3<_T> yzx() const {return vec3<_T>(y,z,x);}
    inline vec3<_T> yzy() const {return vec3<_T>(y,z,y);}
    inline vec3<_T> yzz() const {return vec3<_T>(y,z,z);}
    inline vec3<_T> yzw() const {return vec3<_T>(y,z,w);}
    inline vec3<_T> ywx() const {return vec3<_T>(y,w,x);}
    inline vec3<_T> ywy() const {return vec3<_T>(y,w,y);}
    inline vec3<_T> ywz() const {return vec3<_T>(y,w,z);}
    inline vec3<_T> yww() const {return vec3<_T>(y,w,w);}

    inline vec3<_T> zxx() const {return vec3<_T>(z,x,x);}
    inline vec3<_T> zxy() const {return vec3<_T>(z,x,y);}
    inline vec3<_T> zxz() const {return vec3<_T>(z,x,z);}
    inline vec3<_T> zxw() const {return vec3<_T>(z,x,w);}
    inline vec3<_T> zyx() const {return vec3<_T>(z,y,x);}
    inline vec3<_T> zyy() const {return vec3<_T>(z,y,y);}
    inline vec3<_T> zyz() const {return vec3<_T>(z,y,z);}
    inline vec3<_T> zyw() const {return vec3<_T>(z,y,w);}
    inline vec3<_T> zzx() const {return vec3<_T>(z,z,x);}
    inline vec3<_T> zzy() const {return vec3<_T>(z,z,y);}
    inline vec3<_T> zzz() const {return vec3<_T>(z,z,z);}
    inline vec3<_T> zzw() const {return vec3<_T>(z,z,w);}
    inline vec3<_T> zwx() const {return vec3<_T>(z,w,x);}
    inline vec3<_T> zwy() const {return vec3<_T>(z,w,y);}
    inline vec3<_T> zwz() const {return vec3<_T>(z,w,z);}
    inline vec3<_T> zww() const {return vec3<_T>(z,w,w);}

    inline vec3<_T> wxx() const {return vec3<_T>(w,x,x);}
    inline vec3<_T> wxy() const {return vec3<_T>(w,x,y);}
    inline vec3<_T> wxz() const {return vec3<_T>(w,x,z);}
    inline vec3<_T> wxw() const {return vec3<_T>(w,x,w);}
    inline vec3<_T> wyx() const {return vec3<_T>(w,y,x);}
    inline vec3<_T> wyy() const {return vec3<_T>(w,y,y);}
    inline vec3<_T> wyz() const {return vec3<_T>(w,y,z);}
    inline vec3<_T> wyw() const {return vec3<_T>(w,y,w);}
    inline vec3<_T> wzx() const {return vec3<_T>(w,z,x);}
    inline vec3<_T> wzy() const {return vec3<_T>(w,z,y);}
    inline vec3<_T> wzz() const {return vec3<_T>(w,z,z);}
    inline vec3<_T> wzw() const {return vec3<_T>(w,z,w);}
    inline vec3<_T> wwx() const {return vec3<_T>(w,w,x);}
    inline vec3<_T> wwy() const {return vec3<_T>(w,w,y);}
    inline vec3<_T> wwz() const {return vec3<_T>(w,w,z);}
    inline vec3<_T> www() const {return vec3<_T>(w,w,w);}

    template <typename _U>
    inline vec3<_T>& operator+=(const _U& rhs) {
      x += rhs;
      y += rhs;
      z += rhs;
      w += rhs;
      return *this;
    }
    template <typename _U>
    inline vec3<_T>& operator+=(const vec4<_U>& rhs) {
      x += rhs.x;
      y += rhs.y;
      z += rhs.z;
      w += rhs.w;
      return *this;
    }
    template <typename _U>
    inline vec3<_T>& operator-=(const _U& rhs) {
      x -= rhs;
      y -= rhs;
      z -= rhs;
      w -= rhs;
      return *this;
    }
    template <typename _U>
    inline vec3<_T>& operator-=(const vec4<_U>& rhs) {
      x -= rhs.x;
      y -= rhs.y;
      z -= rhs.z;
      w -= rhs.w;
      return *this;
    }
    template <typename _U>
    inline vec3<_T>& operator*=(const _U& rhs) {
      x *= rhs;
      y *= rhs;
      z *= rhs;
      w *= rhs;
      return *this;
    }
    template <typename _U>
    inline vec3<_T>& operator*=(const vec4<_U>& rhs) {
      x *= rhs.x;
      y *= rhs.y;
      z *= rhs.z;
      w *= rhs.w;
      return *this;
    }
    template <typename _U>
    inline vec3<_T>& operator/=(const _U& rhs) {
      x /= rhs;
      y /= rhs;
      z /= rhs;
      w /= rhs;
      return *this;
    }
    template <typename _U>
    inline vec3<_T>& operator/=(const vec4<_U>& rhs) {
      x /= rhs.x;
      y /= rhs.y;
      z /= rhs.z;
      w /= rhs.w;
      return *this;
    }

    _T x, y, z, w;
  };

  template <typename _T>
  inline std::ostream& operator<<(std::ostream& out, const vec2<_T>& rhs) {
    out << '<' << rhs.x << ',' << rhs.y << '>';
    return out;
  }
  template <typename _T>
  inline std::ostream& operator<<(std::ostream& out, const vec3<_T>& rhs) {
    out << '<' << rhs.x << ',' << rhs.y << ',' << rhs.z << '>';
    return out;
  }
  template <typename _T>
  inline std::ostream& operator<<(std::ostream& out, const vec4<_T>& rhs) {
    out << '<' << rhs.x << ',' << rhs.y << ',' << rhs.z << ',' << rhs.w << '>';
    return out;
  }

  template <typename _T, typename _U>
  inline bool operator==(const vec2<_T>& lhs, const vec2<_U>& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }
  template <typename _T, typename _U>
  inline bool operator!=(const vec2<_T>& lhs, const vec2<_U>& rhs) {
    return !(lhs.x == rhs.x && lhs.y == rhs.y);
  }
  template <typename _T, typename _U>
  inline bool operator==(const vec3<_T>& lhs, const vec3<_U>& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
  }
  template <typename _T, typename _U>
  inline bool operator!=(const vec3<_T>& lhs, const vec3<_U>& rhs) {
    return !(lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z);
  }
  template <typename _T, typename _U>
  inline bool operator==(const vec4<_T>& lhs, const vec4<_U>& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
  }
  template <typename _T, typename _U>
  inline bool operator!=(const vec4<_T>& lhs, const vec4<_U>& rhs) {
    return !(lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z &&
             lhs.w == rhs.w);
  }

  template <typename _T, typename _U>
  inline vec2<_T> operator+(const vec2<_T>& lhs, const _U& rhs) {
    return vec2<_T>(lhs.x + rhs, lhs.y + rhs);
  }
  template <typename _T, typename _U>
  inline vec2<_T> operator+(const vec2<_T>& lhs, const vec2<_U>& rhs) {
    return vec2<_T>(lhs.x + rhs.x, lhs.y + rhs.y);
  }
  template <typename _T, typename _U>
  inline vec2<_T> operator-(const vec2<_T>& lhs, const _U& rhs) {
    return vec2<_T>(lhs.x - rhs, lhs.y - rhs);
  }
  template <typename _T, typename _U>
  inline vec2<_T> operator-(const vec2<_T>& lhs, const vec2<_U>& rhs) {
    return vec2<_T>(lhs.x - rhs.x, lhs.y - rhs.y);
  }
  template <typename _T, typename _U>
  inline vec2<_T> operator*(const _U& lhs, const vec2<_T>& rhs) {
    return vec2<_T>(lhs * rhs.x, lhs * rhs.y);
  }
  template <typename _T, typename _U>
  inline vec2<_T> operator*(const vec2<_T>& lhs, const _U& rhs) {
    return vec2<_T>(lhs.x * rhs, lhs.y * rhs);
  }
  template <typename _T, typename _U>
  inline vec2<_T> operator*(const vec2<_T>& lhs, const vec2<_U>& rhs) {
    return vec2<_T>(lhs.x * rhs.x, lhs.y * rhs.y);
  }
  template <typename _T, typename _U>
  inline vec2<_T> operator/(const vec2<_T>& lhs, const _U& rhs) {
    return vec2<_T>(lhs.x / rhs, lhs.y / rhs);
  }
  template <typename _T, typename _U>
  inline vec2<_T> operator/(const vec2<_T>& lhs, const vec2<_U>& rhs) {
    return vec2<_T>(lhs.x / rhs.x, lhs.y / rhs.y);
  }

  template <typename _T, typename _U>
  inline vec3<_T> operator+(const vec3<_T>& lhs, const _U& rhs) {
    return vec3<_T>(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
  }
  template <typename _T, typename _U>
  inline vec3<_T> operator+(const vec3<_T>& lhs, const vec3<_U>& rhs) {
    return vec3<_T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
  }
  template <typename _T, typename _U>
  inline vec3<_T> operator-(const vec3<_T>& lhs, const _U& rhs) {
    return vec3<_T>(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
  }
  template <typename _T, typename _U>
  inline vec3<_T> operator-(const vec3<_T>& lhs, const vec3<_U>& rhs) {
    return vec3<_T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
  }
  template <typename _T, typename _U>
  inline vec3<_T> operator*(const _U& lhs, const vec3<_T>& rhs) {
    return vec3<_T>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
  }
  template <typename _T, typename _U>
  inline vec3<_T> operator*(const vec3<_T>& lhs, const _U& rhs) {
    return vec3<_T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
  }
  template <typename _T, typename _U>
  inline vec3<_T> operator*(const vec3<_T>& lhs, const vec3<_U>& rhs) {
    return vec3<_T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
  }
  template <typename _T, typename _U>
  inline vec3<_T> operator/(const vec3<_T>& lhs, const _U& rhs) {
    return vec3<_T>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
  }
  template <typename _T, typename _U>
  inline vec3<_T> operator/(const vec3<_T>& lhs, const vec3<_U>& rhs) {
    return vec3<_T>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
  }

  template <typename _T, typename _U>
  inline vec4<_T> operator+(const vec4<_T>& lhs, const _U& rhs) {
    return vec4<_T>(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs);
  }
  template <typename _T, typename _U>
  inline vec4<_T> operator+(const vec4<_T>& lhs, const vec4<_U>& rhs) {
    return vec4<_T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
  }
  template <typename _T, typename _U>
  inline vec4<_T> operator-(const vec4<_T>& lhs, const _U& rhs) {
    return vec4<_T>(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs);
  }
  template <typename _T, typename _U>
  inline vec4<_T> operator-(const vec4<_T>& lhs, const vec4<_U>& rhs) {
    return vec4<_T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
  }
  template <typename _T, typename _U>
  inline vec4<_T> operator*(const _U& lhs, const vec4<_T>& rhs) {
    return vec4<_T>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
  }
  template <typename _T, typename _U>
  inline vec4<_T> operator*(const vec4<_T>& lhs, const _U& rhs) {
    return vec4<_T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
  }
  template <typename _T, typename _U>
  inline vec4<_T> operator*(const vec4<_T>& lhs, const vec4<_U>& rhs) {
    return vec4<_T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
  }
  template <typename _T, typename _U>
  inline vec4<_T> operator/(const vec4<_T>& lhs, const _U& rhs) {
    return vec4<_T>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs);
  }
  template <typename _T, typename _U>
  inline vec4<_T> operator/(const vec4<_T>& lhs, const vec4<_U>& rhs) {
    return vec4<_T>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w);
  }

  template <typename _T>
  inline vec2<_T> component_op(const vec2<_T>& lhs, _T (*func)(const _T&)) {
    return vec2<_T>(func(lhs.x), func(lhs.y));
  }
  template <typename _T>
  inline vec3<_T> component_op(const vec3<_T>& lhs, _T (*func)(const _T&)) {
    return vec3<_T>(func(lhs.x), func(lhs.y), func(lhs.z));
  }
  template <typename _T>
  inline vec4<_T> component_op(const vec4<_T>& lhs, _T (*func)(const _T&)) {
    return vec4<_T>(func(lhs.x), func(lhs.y), func(lhs.z), func(lhs.w));
  }

  template <typename _T>
  inline vec2<_T> component_op(const vec2<_T>& lhs, const vec2<_T>& rhs,
                               _T (*func)(const _T&, const _T&)) {
    return vec2<_T>(func(lhs.x, rhs.x), func(lhs.y, rhs.y));
  }
  template <typename _T>
  inline vec2<_T> component_op(const vec2<_T>& lhs, const _T& rhs,
                               _T (*func)(const _T&, const _T&)) {
    return vec2<_T>(func(lhs.x, rhs), func(lhs.y, rhs));
  }
  template <typename _T>
  inline vec2<_T> component_op(const _T& lhs, const vec2<_T>& rhs,
                               _T (*func)(const _T&, const _T&)) {
    return vec2<_T>(func(lhs, rhs.x), func(lhs, rhs.y));
  }

  template <typename _T>
  inline vec3<_T> component_op(const vec3<_T>& lhs, const vec3<_T>& rhs,
                               _T (*func)(const _T&, const _T&)) {
    return vec3<_T>(func(lhs.x, rhs.x), func(lhs.y, rhs.y), func(lhs.z, rhs.z));
  }
  template <typename _T>
  inline vec3<_T> component_op(const vec3<_T>& lhs, const _T& rhs,
                               _T (*func)(const _T&, const _T&)) {
    return vec3<_T>(func(lhs.x, rhs), func(lhs.y, rhs), func(lhs.z, rhs));
  }
  template <typename _T>
  inline vec3<_T> component_op(const _T& lhs, const vec3<_T>& rhs,
                               _T (*func)(const _T&, const _T&)) {
    return vec3<_T>(func(lhs, rhs.x), func(lhs, rhs.y), func(lhs, rhs.z));
  }

  template <typename _T>
  inline vec4<_T> component_op(const vec4<_T>& lhs, const vec4<_T>& rhs,
                               _T (*func)(const _T&, const _T&)) {
    return vec4<_T>(func(lhs.x, rhs.x), func(lhs.y, rhs.y), func(lhs.z, rhs.z),
                    func(lhs.w, rhs.w));
  }
  template <typename _T>
  inline vec4<_T> component_op(const vec4<_T>& lhs, const _T& rhs,
                               _T (*func)(const _T&, const _T&)) {
    return vec4<_T>(func(lhs.x, rhs), func(lhs.y, rhs), func(lhs.z, rhs),
                    func(lhs.w, rhs));
  }
  template <typename _T>
  inline vec4<_T> component_op(const _T& lhs, const vec4<_T>& rhs,
                               _T (*func)(const _T&, const _T&)) {
    return vec4<_T>(func(lhs, rhs.x), func(lhs, rhs.y), func(lhs, rhs.z),
                    func(lhs, rhs.w));
  }

  template <typename _T>
  inline vec2<_T> component_op(const vec2<_T>& x, const vec2<_T>& y,
                               const vec2<_T>& z,
                               _T (*func)(const _T&, const _T&, const _T&)) {
    return vec2<_T>(func(x.x, y.x, z.x), func(x.y, y.y, z.y));
  }
  template <typename _T>
  inline vec2<_T> component_op(const _T& x, const vec2<_T>& y,
                               const vec2<_T>& z,
                               _T (*func)(const _T&, const _T&, const _T&)) {
    return vec2<_T>(func(x, y.x, z.x), func(x, y.y, z.y));
  }
  template <typename _T>
  inline vec2<_T> component_op(const vec2<_T>& x, const _T& y,
                               const vec2<_T>& z,
                               _T (*func)(const _T&, const _T&, const _T&)) {
    return vec2<_T>(func(x.x, y, z.x), func(x.y, y, z.y));
  }
  template <typename _T>
  inline vec2<_T> component_op(const vec2<_T>& x, const vec2<_T>& y,
                               const _T& z,
                               _T (*func)(const _T&, const _T&, const _T&)) {
    return vec2<_T>(func(x.x, y.x, z), func(x.y, y.y, z));
  }
  template <typename _T>
  inline vec2<_T> component_op(const _T& x, const _T& y, const vec2<_T>& z,
                               _T (*func)(const _T&, const _T&, const _T&)) {
    return vec2<_T>(func(x, y, z.x), func(x, y, z.y));
  }
  template <typename _T>
  inline vec2<_T> component_op(const _T& x, const vec2<_T>& y, const _T& z,
                               _T (*func)(const _T&, const _T&, const _T&)) {
    return vec2<_T>(func(x, y.x, z), func(x, y.y, z));
  }
  template <typename _T>
  inline vec2<_T> component_op(const vec2<_T>& x, const _T& y, const _T& z,
                               _T (*func)(const _T&, const _T&, const _T&)) {
    return vec2<_T>(func(x.x, y, z), func(x.y, y, z));
  }

  template <typename _T>
  inline vec3<_T> component_op(const vec3<_T>& x, const vec3<_T>& y,
                               const vec3<_T>& z,
                               _T (*func)(const _T&, const _T&, const _T&)) {
    return vec3<_T>(func(x.x, y.x, z.x), func(x.y, y.y, z.y),
                    func(x.z, y.z, z.z));
  }
  template <typename _T>
  inline vec3<_T> component_op(const _T& x, const vec3<_T>& y,
                               const vec3<_T>& z,
                               _T (*func)(const _T&, const _T&, const _T&)) {
    return vec3<_T>(func(x, y.x, z.x), func(x, y.y, z.y), func(x, y.z, z.z));
  }
  template <typename _T>
  inline vec3<_T> component_op(const vec3<_T>& x, const _T& y,
                               const vec3<_T>& z,
                               _T (*func)(const _T&, const _T&, const _T&)) {
    return vec3<_T>(func(x.x, y, z.x), func(x.y, y, z.y), func(x.z, y, z.z));
  }
  template <typename _T>
  inline vec3<_T> component_op(const vec3<_T>& x, const vec3<_T>& y,
                               const _T& z,
                               _T (*func)(const _T&, const _T&, const _T&)) {
    return vec3<_T>(func(x.x, y.x, z), func(x.y, y.y, z), func(x.z, y.z, z));
  }
  template <typename _T>
  inline vec3<_T> component_op(const _T& x, const _T& y, const vec3<_T>& z,
                               _T (*func)(const _T&, const _T&, const _T&)) {
    return vec3<_T>(func(x, y, z.x), func(x, y, z.y), func(x, y, z.z));
  }
  template <typename _T>
  inline vec3<_T> component_op(const _T& x, const vec3<_T>& y, const _T& z,
                               _T (*func)(const _T&, const _T&, const _T&)) {
    return vec3<_T>(func(x, y.x, z), func(x, y.y, z), func(z, y.z, z));
  }
  template <typename _T>
  inline vec3<_T> component_op(const vec3<_T>& x, const _T& y, const _T& z,
                               _T (*func)(const _T&, const _T&, const _T&)) {
    return vec3<_T>(func(x.x, y, z), func(x.y, y, z), func(x.z, y, z));
  }

  template <typename _T>
  inline vec4<_T> component_op(const vec4<_T>& x, const vec4<_T>& y,
                               const vec4<_T>& z,
                               _T (*func)(const _T&, const _T&, const _T&)) {
    return vec4<_T>(func(x.x, y.x, z.x), func(x.y, y.y, z.y),
                    func(x.z, y.z, z.z), func(x.w, y.w, z.w));
  }
  template <typename _T>
  inline vec4<_T> component_op(const _T& x, const vec4<_T>& y,
                               const vec4<_T>& z,
                               _T (*func)(const _T&, const _T&, const _T&)) {
    return vec4<_T>(func(x, y.x, z.x), func(x, y.y, z.y), func(x, y.z, z.z),
                    func(x, y.w, z.w));
  }
  template <typename _T>
  inline vec4<_T> component_op(const vec4<_T>& x, const _T& y,
                               const vec4<_T>& z,
                               _T (*func)(const _T&, const _T&, const _T&)) {
    return vec4<_T>(func(x.x, y, z.x), func(x.y, y, z.y), func(x.z, y, z.z),
                    func(x.w, y, z.w));
  }
  template <typename _T>
  inline vec4<_T> component_op(const vec4<_T>& x, const vec4<_T>& y,
                               const _T& z,
                               _T (*func)(const _T&, const _T&, const _T&)) {
    return vec4<_T>(func(x.x, y.x, z), func(x.y, y.y, z), func(x.z, y.z, z),
                    func(x.w, y.w, z));
  }
  template <typename _T>
  inline vec4<_T> component_op(const _T& x, const _T& y, const vec4<_T>& z,
                               _T (*func)(const _T&, const _T&, const _T&)) {
    return vec4<_T>(func(x, y, z.x), func(x, y, z.y), func(x, y, z.z),
                    func(x, y, z.w));
  }
  template <typename _T>
  inline vec4<_T> component_op(const _T& x, const vec4<_T>& y, const _T& z,
                               _T (*func)(const _T&, const _T&, const _T&)) {
    return vec4<_T>(func(x, y.x, z), func(x, y.y, z), func(x, y.z, z),
                    func(x, y.w, z));
  }
  template <typename _T>
  inline vec4<_T> component_op(const vec4<_T>& x, const _T& y, const _T& z,
                               _T (*func)(const _T&, const _T&, const _T&)) {
    return vec4<_T>(func(x.x, y, z), func(x.y, y, z), func(x.z, y, z),
                    func(x.w, y, z));
  }

  typedef vec2<bool> bvec2;
  typedef vec2<int> ivec2;
  typedef vec2<float> fvec2;
  typedef vec3<bool> bvec3;
  typedef vec3<int> ivec3;
  typedef vec3<float> fvec3;
  typedef vec4<bool> bvec4;
  typedef vec4<int> ivec4;
  typedef vec4<float> fvec4;

}  // namespace math
}  // namespace specula

#endif  // SPECULA_MATH_VECTOR_HPP_
