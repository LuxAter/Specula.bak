#ifndef SPECULA_MATH_VEC4_HPP_
#define SPECULA_MATH_VEC4_HPP_

#include <cmath>
#include <iostream>

#define GET_MACRO(_1, _2, _3, _4, NAME, ...) NAME

#define SWIZZLE2(a, b)                                                         \
  inline vec2<_T &> a##b() { return vec2<_T &>{a, b}; }                        \
  inline vec2<_T> a##b() const { return vec2<_T>{a, b}; }
#define SWIZZLE3(a, b, c)                                                      \
  inline vec3<_T &> a##b##c() { return vec3<_T &>{a, b, c}; }                  \
  inline vec3<_T> a##b##c() const { return vec3<_T>{a, b, c}; }
#define SWIZZLE4(a, b, c, d)                                                   \
  inline vec4<_T &> a##b##c##d() { return vec4<_T &>{a, b, c, d}; }            \
  inline vec4<_T> a##b##c##d() const { return vec4<_T>{a, b, c, d}; }
#define SWIZZLE(...)                                                           \
  GET_MACRO(__VA_ARGS__, SWIZZLE4, SWIZZLE3, SWIZZLE2)(__VA_ARGS__)

namespace specula {
template <typename _T> class vec2;
template <typename _T> class vec3;
template <typename _T> class vec4 {
public:
  vec4() : x(), y(), z(), w() {}
  vec4(const _T &v) : x(v), y(v), z(v), w(v) {}
  vec4(const _T &x, const _T &y, const _T &z, const _T &w)
      : x(x), y(y), z(z), w(w) {}
  vec4(const vec2<_T> &copy)
      : x(copy.x), y(copy.y), z(static_cast<_T>(0)), w(static_cast<_T>(0)) {}
  vec4(const vec3<_T> &copy)
      : x(copy.x), y(copy.y), z(copy.z), w(static_cast<_T>(0)) {}
  vec4(const vec4<_T> &copy) : x(copy.x), y(copy.y), z(copy.z), w(copy.w) {}

  inline vec4<_T> &operator=(const vec2<_T> &other) {
    x = other.x;
    y = other.y;
    return *this;
  }
  inline vec4<_T> &operator=(const vec3<_T> &other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
  }
  inline vec4<_T> &operator=(const vec4<_T> &other) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
  }

  inline vec4<_T> &operator+=(const _T &v) {
    x += v;
    y += v;
    z += v;
    w += v;
    return *this;
  }
  inline vec4<_T> &operator+=(const vec2<_T> &other) {
    x += other.x;
    y += other.y;
    return *this;
  }
  inline vec4<_T> &operator+=(const vec3<_T> &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }
  inline vec4<_T> &operator+=(const vec4<_T> &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
  }
  inline vec4<_T> &operator-=(const _T &v) {
    x -= v;
    y -= v;
    z -= v;
    w -= v;
    return *this;
  }
  inline vec4<_T> &operator-=(const vec2<_T> &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }
  inline vec4<_T> &operator-=(const vec3<_T> &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }
  inline vec4<_T> &operator-=(const vec4<_T> &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
  }
  inline vec4<_T> &operator*=(const _T &v) {
    x *= v;
    y *= v;
    z *= v;
    w *= v;
    return *this;
  }
  inline vec4<_T> &operator*=(const vec2<_T> &other) {
    x *= other.x;
    y *= other.y;
    return *this;
  }
  inline vec4<_T> &operator*=(const vec3<_T> &other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
  }
  inline vec4<_T> &operator*=(const vec4<_T> &other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    w *= other.w;
    return *this;
  }
  inline vec4<_T> &operator/=(const _T &v) {
    x /= v;
    y /= v;
    z /= v;
    w /= v;
    return *this;
  }
  inline vec4<_T> &operator/=(const vec2<_T> &other) {
    x /= other.x;
    y /= other.y;
    return *this;
  }
  inline vec4<_T> &operator/=(const vec3<_T> &other) {
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
  }
  inline vec4<_T> &operator/=(const vec4<_T> &other) {
    x /= other.x;
    y /= other.y;
    z /= other.z;
    w /= other.w;
    return *this;
  }

  SWIZZLE(x, x)
  SWIZZLE(x, y)
  SWIZZLE(x, z)
  SWIZZLE(x, w)
  SWIZZLE(y, x)
  SWIZZLE(y, y)
  SWIZZLE(y, z)
  SWIZZLE(y, w)
  SWIZZLE(z, x)
  SWIZZLE(z, y)
  SWIZZLE(z, z)
  SWIZZLE(z, w)
  SWIZZLE(w, x)
  SWIZZLE(w, y)
  SWIZZLE(w, z)
  SWIZZLE(w, w)

  SWIZZLE(x, x, x)
  SWIZZLE(x, x, y)
  SWIZZLE(x, x, z)
  SWIZZLE(x, x, w)
  SWIZZLE(x, y, x)
  SWIZZLE(x, y, y)
  SWIZZLE(x, y, z)
  SWIZZLE(x, y, w)
  SWIZZLE(x, z, x)
  SWIZZLE(x, z, y)
  SWIZZLE(x, z, z)
  SWIZZLE(x, z, w)
  SWIZZLE(x, w, x)
  SWIZZLE(x, w, y)
  SWIZZLE(x, w, z)
  SWIZZLE(x, w, w)
  SWIZZLE(y, x, x)
  SWIZZLE(y, x, y)
  SWIZZLE(y, x, z)
  SWIZZLE(y, x, w)
  SWIZZLE(y, y, x)
  SWIZZLE(y, y, y)
  SWIZZLE(y, y, z)
  SWIZZLE(y, y, w)
  SWIZZLE(y, z, x)
  SWIZZLE(y, z, y)
  SWIZZLE(y, z, z)
  SWIZZLE(y, z, w)
  SWIZZLE(y, w, x)
  SWIZZLE(y, w, y)
  SWIZZLE(y, w, z)
  SWIZZLE(y, w, w)
  SWIZZLE(z, x, x)
  SWIZZLE(z, x, y)
  SWIZZLE(z, x, z)
  SWIZZLE(z, x, w)
  SWIZZLE(z, y, x)
  SWIZZLE(z, y, y)
  SWIZZLE(z, y, z)
  SWIZZLE(z, y, w)
  SWIZZLE(z, z, x)
  SWIZZLE(z, z, y)
  SWIZZLE(z, z, z)
  SWIZZLE(z, z, w)
  SWIZZLE(z, w, x)
  SWIZZLE(z, w, y)
  SWIZZLE(z, w, z)
  SWIZZLE(z, w, w)
  SWIZZLE(w, x, x)
  SWIZZLE(w, x, y)
  SWIZZLE(w, x, z)
  SWIZZLE(w, x, w)
  SWIZZLE(w, y, x)
  SWIZZLE(w, y, y)
  SWIZZLE(w, y, z)
  SWIZZLE(w, y, w)
  SWIZZLE(w, z, x)
  SWIZZLE(w, z, y)
  SWIZZLE(w, z, z)
  SWIZZLE(w, z, w)
  SWIZZLE(w, w, x)
  SWIZZLE(w, w, y)
  SWIZZLE(w, w, z)
  SWIZZLE(w, w, w)

  SWIZZLE(x, x, x, x)
  SWIZZLE(x, x, x, y)
  SWIZZLE(x, x, x, z)
  SWIZZLE(x, x, x, w)
  SWIZZLE(x, x, y, x)
  SWIZZLE(x, x, y, y)
  SWIZZLE(x, x, y, z)
  SWIZZLE(x, x, y, w)
  SWIZZLE(x, x, z, x)
  SWIZZLE(x, x, z, y)
  SWIZZLE(x, x, z, z)
  SWIZZLE(x, x, z, w)
  SWIZZLE(x, x, w, x)
  SWIZZLE(x, x, w, y)
  SWIZZLE(x, x, w, z)
  SWIZZLE(x, x, w, w)
  SWIZZLE(x, y, x, x)
  SWIZZLE(x, y, x, y)
  SWIZZLE(x, y, x, z)
  SWIZZLE(x, y, x, w)
  SWIZZLE(x, y, y, x)
  SWIZZLE(x, y, y, y)
  SWIZZLE(x, y, y, z)
  SWIZZLE(x, y, y, w)
  SWIZZLE(x, y, z, x)
  SWIZZLE(x, y, z, y)
  SWIZZLE(x, y, z, z)
  SWIZZLE(x, y, z, w)
  SWIZZLE(x, y, w, x)
  SWIZZLE(x, y, w, y)
  SWIZZLE(x, y, w, z)
  SWIZZLE(x, y, w, w)
  SWIZZLE(x, z, x, x)
  SWIZZLE(x, z, x, y)
  SWIZZLE(x, z, x, z)
  SWIZZLE(x, z, x, w)
  SWIZZLE(x, z, y, x)
  SWIZZLE(x, z, y, y)
  SWIZZLE(x, z, y, z)
  SWIZZLE(x, z, y, w)
  SWIZZLE(x, z, z, x)
  SWIZZLE(x, z, z, y)
  SWIZZLE(x, z, z, z)
  SWIZZLE(x, z, z, w)
  SWIZZLE(x, z, w, x)
  SWIZZLE(x, z, w, y)
  SWIZZLE(x, z, w, z)
  SWIZZLE(x, z, w, w)
  SWIZZLE(x, w, x, x)
  SWIZZLE(x, w, x, y)
  SWIZZLE(x, w, x, z)
  SWIZZLE(x, w, x, w)
  SWIZZLE(x, w, y, x)
  SWIZZLE(x, w, y, y)
  SWIZZLE(x, w, y, z)
  SWIZZLE(x, w, y, w)
  SWIZZLE(x, w, z, x)
  SWIZZLE(x, w, z, y)
  SWIZZLE(x, w, z, z)
  SWIZZLE(x, w, z, w)
  SWIZZLE(x, w, w, x)
  SWIZZLE(x, w, w, y)
  SWIZZLE(x, w, w, z)
  SWIZZLE(x, w, w, w)
  SWIZZLE(y, x, x, x)
  SWIZZLE(y, x, x, y)
  SWIZZLE(y, x, x, z)
  SWIZZLE(y, x, x, w)
  SWIZZLE(y, x, y, x)
  SWIZZLE(y, x, y, y)
  SWIZZLE(y, x, y, z)
  SWIZZLE(y, x, y, w)
  SWIZZLE(y, x, z, x)
  SWIZZLE(y, x, z, y)
  SWIZZLE(y, x, z, z)
  SWIZZLE(y, x, z, w)
  SWIZZLE(y, x, w, x)
  SWIZZLE(y, x, w, y)
  SWIZZLE(y, x, w, z)
  SWIZZLE(y, x, w, w)
  SWIZZLE(y, y, x, x)
  SWIZZLE(y, y, x, y)
  SWIZZLE(y, y, x, z)
  SWIZZLE(y, y, x, w)
  SWIZZLE(y, y, y, x)
  SWIZZLE(y, y, y, y)
  SWIZZLE(y, y, y, z)
  SWIZZLE(y, y, y, w)
  SWIZZLE(y, y, z, x)
  SWIZZLE(y, y, z, y)
  SWIZZLE(y, y, z, z)
  SWIZZLE(y, y, z, w)
  SWIZZLE(y, y, w, x)
  SWIZZLE(y, y, w, y)
  SWIZZLE(y, y, w, z)
  SWIZZLE(y, y, w, w)
  SWIZZLE(y, z, x, x)
  SWIZZLE(y, z, x, y)
  SWIZZLE(y, z, x, z)
  SWIZZLE(y, z, x, w)
  SWIZZLE(y, z, y, x)
  SWIZZLE(y, z, y, y)
  SWIZZLE(y, z, y, z)
  SWIZZLE(y, z, y, w)
  SWIZZLE(y, z, z, x)
  SWIZZLE(y, z, z, y)
  SWIZZLE(y, z, z, z)
  SWIZZLE(y, z, z, w)
  SWIZZLE(y, z, w, x)
  SWIZZLE(y, z, w, y)
  SWIZZLE(y, z, w, z)
  SWIZZLE(y, z, w, w)
  SWIZZLE(y, w, x, x)
  SWIZZLE(y, w, x, y)
  SWIZZLE(y, w, x, z)
  SWIZZLE(y, w, x, w)
  SWIZZLE(y, w, y, x)
  SWIZZLE(y, w, y, y)
  SWIZZLE(y, w, y, z)
  SWIZZLE(y, w, y, w)
  SWIZZLE(y, w, z, x)
  SWIZZLE(y, w, z, y)
  SWIZZLE(y, w, z, z)
  SWIZZLE(y, w, z, w)
  SWIZZLE(y, w, w, x)
  SWIZZLE(y, w, w, y)
  SWIZZLE(y, w, w, z)
  SWIZZLE(y, w, w, w)
  SWIZZLE(z, x, x, x)
  SWIZZLE(z, x, x, y)
  SWIZZLE(z, x, x, z)
  SWIZZLE(z, x, x, w)
  SWIZZLE(z, x, y, x)
  SWIZZLE(z, x, y, y)
  SWIZZLE(z, x, y, z)
  SWIZZLE(z, x, y, w)
  SWIZZLE(z, x, z, x)
  SWIZZLE(z, x, z, y)
  SWIZZLE(z, x, z, z)
  SWIZZLE(z, x, z, w)
  SWIZZLE(z, x, w, x)
  SWIZZLE(z, x, w, y)
  SWIZZLE(z, x, w, z)
  SWIZZLE(z, x, w, w)
  SWIZZLE(z, y, x, x)
  SWIZZLE(z, y, x, y)
  SWIZZLE(z, y, x, z)
  SWIZZLE(z, y, x, w)
  SWIZZLE(z, y, y, x)
  SWIZZLE(z, y, y, y)
  SWIZZLE(z, y, y, z)
  SWIZZLE(z, y, y, w)
  SWIZZLE(z, y, z, x)
  SWIZZLE(z, y, z, y)
  SWIZZLE(z, y, z, z)
  SWIZZLE(z, y, z, w)
  SWIZZLE(z, y, w, x)
  SWIZZLE(z, y, w, y)
  SWIZZLE(z, y, w, z)
  SWIZZLE(z, y, w, w)
  SWIZZLE(z, z, x, x)
  SWIZZLE(z, z, x, y)
  SWIZZLE(z, z, x, z)
  SWIZZLE(z, z, x, w)
  SWIZZLE(z, z, y, x)
  SWIZZLE(z, z, y, y)
  SWIZZLE(z, z, y, z)
  SWIZZLE(z, z, y, w)
  SWIZZLE(z, z, z, x)
  SWIZZLE(z, z, z, y)
  SWIZZLE(z, z, z, z)
  SWIZZLE(z, z, z, w)
  SWIZZLE(z, z, w, x)
  SWIZZLE(z, z, w, y)
  SWIZZLE(z, z, w, z)
  SWIZZLE(z, z, w, w)
  SWIZZLE(z, w, x, x)
  SWIZZLE(z, w, x, y)
  SWIZZLE(z, w, x, z)
  SWIZZLE(z, w, x, w)
  SWIZZLE(z, w, y, x)
  SWIZZLE(z, w, y, y)
  SWIZZLE(z, w, y, z)
  SWIZZLE(z, w, y, w)
  SWIZZLE(z, w, z, x)
  SWIZZLE(z, w, z, y)
  SWIZZLE(z, w, z, z)
  SWIZZLE(z, w, z, w)
  SWIZZLE(z, w, w, x)
  SWIZZLE(z, w, w, y)
  SWIZZLE(z, w, w, z)
  SWIZZLE(z, w, w, w)
  SWIZZLE(w, x, x, x)
  SWIZZLE(w, x, x, y)
  SWIZZLE(w, x, x, z)
  SWIZZLE(w, x, x, w)
  SWIZZLE(w, x, y, x)
  SWIZZLE(w, x, y, y)
  SWIZZLE(w, x, y, z)
  SWIZZLE(w, x, y, w)
  SWIZZLE(w, x, z, x)
  SWIZZLE(w, x, z, y)
  SWIZZLE(w, x, z, z)
  SWIZZLE(w, x, z, w)
  SWIZZLE(w, x, w, x)
  SWIZZLE(w, x, w, y)
  SWIZZLE(w, x, w, z)
  SWIZZLE(w, x, w, w)
  SWIZZLE(w, y, x, x)
  SWIZZLE(w, y, x, y)
  SWIZZLE(w, y, x, z)
  SWIZZLE(w, y, x, w)
  SWIZZLE(w, y, y, x)
  SWIZZLE(w, y, y, y)
  SWIZZLE(w, y, y, z)
  SWIZZLE(w, y, y, w)
  SWIZZLE(w, y, z, x)
  SWIZZLE(w, y, z, y)
  SWIZZLE(w, y, z, z)
  SWIZZLE(w, y, z, w)
  SWIZZLE(w, y, w, x)
  SWIZZLE(w, y, w, y)
  SWIZZLE(w, y, w, z)
  SWIZZLE(w, y, w, w)
  SWIZZLE(w, z, x, x)
  SWIZZLE(w, z, x, y)
  SWIZZLE(w, z, x, z)
  SWIZZLE(w, z, x, w)
  SWIZZLE(w, z, y, x)
  SWIZZLE(w, z, y, y)
  SWIZZLE(w, z, y, z)
  SWIZZLE(w, z, y, w)
  SWIZZLE(w, z, z, x)
  SWIZZLE(w, z, z, y)
  SWIZZLE(w, z, z, z)
  SWIZZLE(w, z, z, w)
  SWIZZLE(w, z, w, x)
  SWIZZLE(w, z, w, y)
  SWIZZLE(w, z, w, z)
  SWIZZLE(w, z, w, w)
  SWIZZLE(w, w, x, x)
  SWIZZLE(w, w, x, y)
  SWIZZLE(w, w, x, z)
  SWIZZLE(w, w, x, w)
  SWIZZLE(w, w, y, x)
  SWIZZLE(w, w, y, y)
  SWIZZLE(w, w, y, z)
  SWIZZLE(w, w, y, w)
  SWIZZLE(w, w, z, x)
  SWIZZLE(w, w, z, y)
  SWIZZLE(w, w, z, z)
  SWIZZLE(w, w, z, w)
  SWIZZLE(w, w, w, x)
  SWIZZLE(w, w, w, y)
  SWIZZLE(w, w, w, z)
  SWIZZLE(w, w, w, w)

  union {
    _T x, r;
  };
  union {
    _T y, g;
  };
  union {
    _T z, b, h;
  };
  union {
    _T w, a;
  };
};

template <typename _T>
inline vec4<_T> operator+(const vec4<_T> &a, const _T &b) {
  return vec4<_T>{a.x + b, a.y + b, a.z + b, a.w + b};
}
template <typename _T>
inline vec4<_T> operator+(const vec4<_T> &a, const vec2<_T> &b) {
  return vec4<_T>{a.x + b.x, a.y + b.y, a.z, a.w};
}
template <typename _T>
inline vec4<_T> operator+(const vec4<_T> &a, const vec3<_T> &b) {
  return vec4<_T>{a.x + b.x, a.y + b.y, a.z + b.z, a.w};
}
template <typename _T>
inline vec4<_T> operator+(const vec4<_T> &a, const vec4<_T> &b) {
  return vec4<_T>{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}
template <typename _T>
inline vec4<_T> operator-(const vec4<_T> &a, const _T &b) {
  return vec4<_T>{a.x - b, a.y - b, a.z - b, a.w - b};
}
template <typename _T>
inline vec4<_T> operator-(const vec4<_T> &a, const vec2<_T> &b) {
  return vec4<_T>{a.x - b.x, a.y - b.y, a.z, a.w};
}
template <typename _T>
inline vec4<_T> operator-(const vec4<_T> &a, const vec3<_T> &b) {
  return vec4<_T>{a.x - b.x, a.y - b.y, a.z - b.z, a.w};
}
template <typename _T>
inline vec4<_T> operator-(const vec4<_T> &a, const vec4<_T> &b) {
  return vec4<_T>{a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}
template <typename _T>
inline vec4<_T> operator*(const _T &a, const vec4<_T> &b) {
  return vec4<_T>{a * b.x, a * b.y, a * b.z, a * b.w};
}
template <typename _T>
inline vec4<_T> operator*(const vec4<_T> &a, const _T &b) {
  return vec4<_T>{a.x * b, a.y * b, a.z * b, a.w * b};
}
template <typename _T>
inline vec4<_T> operator*(const vec4<_T> &a, const vec2<_T> &b) {
  return vec4<_T>{a.x * b.x, a.y * b.y, a.z, a.w};
}
template <typename _T>
inline vec4<_T> operator*(const vec4<_T> &a, const vec3<_T> &b) {
  return vec4<_T>{a.x * b.x, a.y * b.y, a.z * b.z, a.w};
}
template <typename _T>
inline vec4<_T> operator*(const vec4<_T> &a, const vec4<_T> &b) {
  return vec4<_T>{a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
}
template <typename _T>
inline vec4<_T> operator/(const vec4<_T> &a, const _T &b) {
  return vec4<_T>{a.x / b, a.y / b, a.z / b, a.w / b};
}
template <typename _T>
inline vec4<_T> operator/(const vec4<_T> &a, const vec2<_T> &b) {
  return vec4<_T>{a.x / b.x, a.y / b.y, a.z, a.w};
}
template <typename _T>
inline vec4<_T> operator/(const vec4<_T> &a, const vec3<_T> &b) {
  return vec4<_T>{a.x / b.x, a.y / b.y, a.z / b.z, a.w};
}
template <typename _T>
inline vec4<_T> operator/(const vec4<_T> &a, const vec4<_T> &b) {
  return vec4<_T>{a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w};
}

template <typename _T>
inline std::ostream &operator<<(std::ostream &out, const vec4<_T> &v) {
  return out << '<' << v.x << ',' << v.y << ',' << v.z << ',' << v.w << '>';
}

typedef vec4<double> float4;

} // namespace specula

#endif // SPECULA_MATH_VEC4_HPP_
