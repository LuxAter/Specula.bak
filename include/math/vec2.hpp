#ifndef SPECULA_MATH_VEC2_HPP_
#define SPECULA_MATH_VEC2_HPP_

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
template <typename _T> class vec3;
template <typename _T> class vec4;
template <typename _T> class vec2 {
public:
  vec2(const _T &v) : x(v), y(v) {}
  vec2(const _T &x, const _T &y) : x(x), y(y) {}
  vec2(const vec2<_T> &copy) : x(copy.x), y(copy.y) {}
  vec2(const vec3<_T> &copy) : x(copy.x), y(copy.y) {}
  vec2(const vec4<_T> &copy) : x(copy.x), y(copy.y) {}

  inline vec2<_T> &operator=(const vec2<_T> &other) {
    x = other.x;
    y = other.y;
    return *this;
  }
  inline vec2<_T> &operator=(const vec3<_T> &other) {
    x = other.x;
    y = other.y;
    return *this;
  }
  inline vec2<_T> &operator=(const vec4<_T> &other) {
    x = other.x;
    y = other.y;
    return *this;
  }

  inline vec2<_T> &operator+=(const _T &v) {
    x += v;
    y += v;
    return *this;
  }
  inline vec2<_T> &operator+=(const vec2<_T> &other) {
    x += other.x;
    y += other.y;
    return *this;
  }
  inline vec2<_T> &operator+=(const vec3<_T> &other) {
    x += other.x;
    y += other.y;
    return *this;
  }
  inline vec2<_T> &operator+=(const vec4<_T> &other) {
    x += other.x;
    y += other.y;
    return *this;
  }
  inline vec2<_T> &operator-=(const _T &v) {
    x -= v;
    y -= v;
    return *this;
  }
  inline vec2<_T> &operator-=(const vec2<_T> &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }
  inline vec2<_T> &operator-=(const vec3<_T> &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }
  inline vec2<_T> &operator-=(const vec4<_T> &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }
  inline vec2<_T> &operator*=(const _T &v) {
    x *= v;
    y *= v;
    return *this;
  }
  inline vec2<_T> &operator*=(const vec2<_T> &other) {
    x *= other.x;
    y *= other.y;
    return *this;
  }
  inline vec2<_T> &operator*=(const vec3<_T> &other) {
    x *= other.x;
    y *= other.y;
    return *this;
  }
  inline vec2<_T> &operator*=(const vec4<_T> &other) {
    x *= other.x;
    y *= other.y;
    return *this;
  }
  inline vec2<_T> &operator/=(const _T &v) {
    x /= v;
    y /= v;
    return *this;
  }
  inline vec2<_T> &operator/=(const vec2<_T> &other) {
    x /= other.x;
    y /= other.y;
    return *this;
  }
  inline vec2<_T> &operator/=(const vec3<_T> &other) {
    x /= other.x;
    y /= other.y;
    return *this;
  }
  inline vec2<_T> &operator/=(const vec4<_T> &other) {
    x /= other.x;
    y /= other.y;
    return *this;
  }

  SWIZZLE(x, x)
  SWIZZLE(x, y)
  SWIZZLE(y, y)

  SWIZZLE(x, x, x)
  SWIZZLE(x, x, y)
  SWIZZLE(x, y, x)
  SWIZZLE(x, y, y)
  SWIZZLE(y, x, x)
  SWIZZLE(y, x, y)
  SWIZZLE(y, y, x)
  SWIZZLE(y, y, y)

  SWIZZLE(x, x, x, x)
  SWIZZLE(x, x, x, y)
  SWIZZLE(x, x, y, x)
  SWIZZLE(x, x, y, y)
  SWIZZLE(x, y, x, x)
  SWIZZLE(x, y, x, y)
  SWIZZLE(x, y, y, x)
  SWIZZLE(x, y, y, y)
  SWIZZLE(y, x, x, x)
  SWIZZLE(y, x, x, y)
  SWIZZLE(y, x, y, x)
  SWIZZLE(y, x, y, y)
  SWIZZLE(y, y, x, x)
  SWIZZLE(y, y, x, y)
  SWIZZLE(y, y, y, x)
  SWIZZLE(y, y, y, y)

  _T x, y;
};

template <typename _T>
inline vec2<_T> operator+(const vec2<_T> &a, const _T &b) {
  return vec2<_T>{a.x + b, a.y + b};
}
template <typename _T>
inline vec2<_T> operator+(const vec2<_T> &a, const vec2<_T> &b) {
  return vec2<_T>{a.x + b.x, a.y + b.y};
}
template <typename _T>
inline vec2<_T> operator+(const vec2<_T> &a, const vec3<_T> &b) {
  return vec2<_T>{a.x + b.x, a.y + b.y};
}
template <typename _T>
inline vec2<_T> operator+(const vec2<_T> &a, const vec4<_T> &b) {
  return vec2<_T>{a.x + b.x, a.y + b.y};
}
template <typename _T>
inline vec2<_T> operator-(const vec2<_T> &a, const _T &b) {
  return vec2<_T>{a.x - b, a.y - b};
}
template <typename _T>
inline vec2<_T> operator-(const vec2<_T> &a, const vec2<_T> &b) {
  return vec2<_T>{a.x - b.x, a.y - b.y};
}
template <typename _T>
inline vec2<_T> operator-(const vec2<_T> &a, const vec3<_T> &b) {
  return vec2<_T>{a.x - b.x, a.y - b.y};
}
template <typename _T>
inline vec2<_T> operator-(const vec2<_T> &a, const vec4<_T> &b) {
  return vec2<_T>{a.x - b.x, a.y - b.y};
}
template <typename _T>
inline vec2<_T> operator*(const _T &a, const vec2<_T> &b) {
  return vec2<_T>{a * b.x, a * b.y};
}
template <typename _T>
inline vec2<_T> operator*(const vec2<_T> &a, const _T &b) {
  return vec2<_T>{a.x * b, a.y * b};
}
template <typename _T>
inline vec2<_T> operator*(const vec2<_T> &a, const vec2<_T> &b) {
  return vec2<_T>{a.x * b.x, a.y * b.y};
}
template <typename _T>
inline vec2<_T> operator*(const vec2<_T> &a, const vec3<_T> &b) {
  return vec2<_T>{a.x * b.x, a.y * b.y};
}
template <typename _T>
inline vec2<_T> operator*(const vec2<_T> &a, const vec4<_T> &b) {
  return vec2<_T>{a.x * b.x, a.y * b.y};
}
template <typename _T>
inline vec2<_T> operator/(const vec2<_T> &a, const _T &b) {
  return vec2<_T>{a.x / b, a.y / b};
}
template <typename _T>
inline vec2<_T> operator/(const vec2<_T> &a, const vec2<_T> &b) {
  return vec2<_T>{a.x / b.x, a.y / b.y};
}
template <typename _T>
inline vec2<_T> operator/(const vec2<_T> &a, const vec3<_T> &b) {
  return vec2<_T>{a.x / b.x, a.y / b.y};
}
template <typename _T>
inline vec2<_T> operator/(const vec2<_T> &a, const vec4<_T> &b) {
  return vec2<_T>{a.x / b.x, a.y / b.y};
}

template <typename _T>
inline std::ostream &operator<<(std::ostream &out, const vec2<_T> &v) {
  return out << '<' << v.x << ',' << v.y << '>';
}

typedef vec2<bool> bool2;
typedef vec2<int> int2;
typedef vec2<float> float2;

} // namespace specula

#endif // SPECULA_MATH_VEC2_HPP_
