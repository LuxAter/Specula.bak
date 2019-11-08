#ifndef SPECULA_MATH_VEC3_HPP_
#define SPECULA_MATH_VEC3_HPP_

#include <cmath>
#include <ostream>

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
template <typename _T> class vec4;
template <typename _T> class vec3 {
public:
  vec3(const _T &v) : x(v), y(v), z(v) {}
  vec3(const _T &x, const _T &y, const _T &z) : x(x), y(y), z(z) {}
  vec3(const vec2<_T> &copy) : x(copy.x), y(copy.y), z(static_cast<_T>(0)) {}
  vec3(const vec3<_T> &copy) : x(copy.x), y(copy.y), z(copy.z) {}
  vec3(const vec4<_T> &copy) : x(copy.x), y(copy.y), z(copy.z) {}

  inline vec3<_T> &operator=(const vec2<_T> &other) {
    x = other.x;
    y = other.y;
    return *this;
  }
  inline vec3<_T> &operator=(const vec3<_T> &other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
  }
  inline vec3<_T> &operator=(const vec4<_T> &other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
  }

  inline vec3<_T> &operator+=(const _T &v) {
    x += v;
    y += v;
    z += v;
    return *this;
  }
  inline vec3<_T> &operator+=(const vec2<_T> &other) {
    x += other.x;
    y += other.y;
    return *this;
  }
  inline vec3<_T> &operator+=(const vec3<_T> &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }
  inline vec3<_T> &operator+=(const vec4<_T> &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }
  inline vec3<_T> &operator-=(const _T &v) {
    x -= v;
    y -= v;
    z -= v;
    return *this;
  }
  inline vec3<_T> &operator-=(const vec2<_T> &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }
  inline vec3<_T> &operator-=(const vec3<_T> &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }
  inline vec3<_T> &operator-=(const vec4<_T> &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }
  inline vec3<_T> &operator*=(const _T &v) {
    x *= v;
    y *= v;
    z *= v;
    return *this;
  }
  inline vec3<_T> &operator*=(const vec2<_T> &other) {
    x *= other.x;
    y *= other.y;
    return *this;
  }
  inline vec3<_T> &operator*=(const vec3<_T> &other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
  }
  inline vec3<_T> &operator*=(const vec4<_T> &other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
  }
  inline vec3<_T> &operator/=(const _T &v) {
    x /= v;
    y /= v;
    z /= v;
    return *this;
  }
  inline vec3<_T> &operator/=(const vec2<_T> &other) {
    x /= other.x;
    y /= other.y;
    return *this;
  }
  inline vec3<_T> &operator/=(const vec3<_T> &other) {
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
  }
  inline vec3<_T> &operator/=(const vec4<_T> &other) {
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
  }

  SWIZZLE(x, x)
  SWIZZLE(x, y)
  SWIZZLE(x, z)
  SWIZZLE(y, x)
  SWIZZLE(y, y)
  SWIZZLE(y, z)
  SWIZZLE(z, x)
  SWIZZLE(z, y)
  SWIZZLE(z, z)

  SWIZZLE(x, x, x)
  SWIZZLE(x, x, y)
  SWIZZLE(x, x, z)
  SWIZZLE(x, y, x)
  SWIZZLE(x, y, y)
  SWIZZLE(x, y, z)
  SWIZZLE(x, z, x)
  SWIZZLE(x, z, y)
  SWIZZLE(x, z, z)
  SWIZZLE(y, x, x)
  SWIZZLE(y, x, y)
  SWIZZLE(y, x, z)
  SWIZZLE(y, y, x)
  SWIZZLE(y, y, y)
  SWIZZLE(y, y, z)
  SWIZZLE(y, z, x)
  SWIZZLE(y, z, y)
  SWIZZLE(y, z, z)
  SWIZZLE(z, x, x)
  SWIZZLE(z, x, y)
  SWIZZLE(z, x, z)
  SWIZZLE(z, y, x)
  SWIZZLE(z, y, y)
  SWIZZLE(z, y, z)
  SWIZZLE(z, z, x)
  SWIZZLE(z, z, y)
  SWIZZLE(z, z, z)

  SWIZZLE(x, x, x, x)
  SWIZZLE(x, x, x, y)
  SWIZZLE(x, x, x, z)
  SWIZZLE(x, x, y, x)
  SWIZZLE(x, x, y, y)
  SWIZZLE(x, x, y, z)
  SWIZZLE(x, x, z, x)
  SWIZZLE(x, x, z, y)
  SWIZZLE(x, x, z, z)
  SWIZZLE(x, y, x, x)
  SWIZZLE(x, y, x, y)
  SWIZZLE(x, y, x, z)
  SWIZZLE(x, y, y, x)
  SWIZZLE(x, y, y, y)
  SWIZZLE(x, y, y, z)
  SWIZZLE(x, y, z, x)
  SWIZZLE(x, y, z, y)
  SWIZZLE(x, y, z, z)
  SWIZZLE(x, z, x, x)
  SWIZZLE(x, z, x, y)
  SWIZZLE(x, z, x, z)
  SWIZZLE(x, z, y, x)
  SWIZZLE(x, z, y, y)
  SWIZZLE(x, z, y, z)
  SWIZZLE(x, z, z, x)
  SWIZZLE(x, z, z, y)
  SWIZZLE(x, z, z, z)
  SWIZZLE(y, x, x, x)
  SWIZZLE(y, x, x, y)
  SWIZZLE(y, x, x, z)
  SWIZZLE(y, x, y, x)
  SWIZZLE(y, x, y, y)
  SWIZZLE(y, x, y, z)
  SWIZZLE(y, x, z, x)
  SWIZZLE(y, x, z, y)
  SWIZZLE(y, x, z, z)
  SWIZZLE(y, y, x, x)
  SWIZZLE(y, y, x, y)
  SWIZZLE(y, y, x, z)
  SWIZZLE(y, y, y, x)
  SWIZZLE(y, y, y, y)
  SWIZZLE(y, y, y, z)
  SWIZZLE(y, y, z, x)
  SWIZZLE(y, y, z, y)
  SWIZZLE(y, y, z, z)
  SWIZZLE(y, z, x, x)
  SWIZZLE(y, z, x, y)
  SWIZZLE(y, z, x, z)
  SWIZZLE(y, z, y, x)
  SWIZZLE(y, z, y, y)
  SWIZZLE(y, z, y, z)
  SWIZZLE(y, z, z, x)
  SWIZZLE(y, z, z, y)
  SWIZZLE(y, z, z, z)
  SWIZZLE(z, x, x, x)
  SWIZZLE(z, x, x, y)
  SWIZZLE(z, x, x, z)
  SWIZZLE(z, x, y, x)
  SWIZZLE(z, x, y, y)
  SWIZZLE(z, x, y, z)
  SWIZZLE(z, x, z, x)
  SWIZZLE(z, x, z, y)
  SWIZZLE(z, x, z, z)
  SWIZZLE(z, y, x, x)
  SWIZZLE(z, y, x, y)
  SWIZZLE(z, y, x, z)
  SWIZZLE(z, y, y, x)
  SWIZZLE(z, y, y, y)
  SWIZZLE(z, y, y, z)
  SWIZZLE(z, y, z, x)
  SWIZZLE(z, y, z, y)
  SWIZZLE(z, y, z, z)
  SWIZZLE(z, z, x, x)
  SWIZZLE(z, z, x, y)
  SWIZZLE(z, z, x, z)
  SWIZZLE(z, z, y, x)
  SWIZZLE(z, z, y, y)
  SWIZZLE(z, z, y, z)
  SWIZZLE(z, z, z, x)
  SWIZZLE(z, z, z, y)
  SWIZZLE(z, z, z, z)

  _T x, y, z;
};

template <typename _T>
inline vec3<_T> operator+(const vec3<_T> &a, const _T &b) {
  return vec3<_T>{a.x + b, a.y + b, a.z + b};
}
template <typename _T>
inline vec3<_T> operator+(const vec3<_T> &a, const vec2<_T> &b) {
  return vec3<_T>{a.x + b.x, a.y + b.y, a.z};
}
template <typename _T>
inline vec3<_T> operator+(const vec3<_T> &a, const vec3<_T> &b) {
  return vec3<_T>{a.x + b.x, a.y + b.y, a.z + b.z};
}
template <typename _T>
inline vec3<_T> operator+(const vec3<_T> &a, const vec4<_T> &b) {
  return vec3<_T>{a.x + b.x, a.y + b.y, a.z + b.z};
}
template <typename _T>
inline vec3<_T> operator-(const vec3<_T> &a, const _T &b) {
  return vec3<_T>{a.x - b, a.y - b, a.z - b};
}
template <typename _T>
inline vec3<_T> operator-(const vec3<_T> &a, const vec2<_T> &b) {
  return vec3<_T>{a.x - b.x, a.y - b.y, a.z};
}
template <typename _T>
inline vec3<_T> operator-(const vec3<_T> &a, const vec3<_T> &b) {
  return vec3<_T>{a.x - b.x, a.y - b.y, a.z - b.z};
}
template <typename _T>
inline vec3<_T> operator-(const vec3<_T> &a, const vec4<_T> &b) {
  return vec3<_T>{a.x - b.x, a.y - b.y, a.z - b.z};
}
template <typename _T>
inline vec3<_T> operator*(const _T &a, const vec3<_T> &b) {
  return vec3<_T>{a * b.x, a * b.y, a * b.z};
}
template <typename _T>
inline vec3<_T> operator*(const vec3<_T> &a, const _T &b) {
  return vec3<_T>{a.x * b, a.y * b, a.z * b};
}
template <typename _T>
inline vec3<_T> operator*(const vec3<_T> &a, const vec2<_T> &b) {
  return vec3<_T>{a.x * b.x, a.y * b.y, a.z};
}
template <typename _T>
inline vec3<_T> operator*(const vec3<_T> &a, const vec3<_T> &b) {
  return vec3<_T>{a.x * b.x, a.y * b.y, a.z * b.z};
}
template <typename _T>
inline vec3<_T> operator*(const vec3<_T> &a, const vec4<_T> &b) {
  return vec3<_T>{a.x * b.x, a.y * b.y, a.z * b.z};
}
template <typename _T>
inline vec3<_T> operator/(const vec3<_T> &a, const _T &b) {
  return vec3<_T>{a.x / b, a.y / b, a.z / b};
}
template <typename _T>
inline vec3<_T> operator/(const vec3<_T> &a, const vec2<_T> &b) {
  return vec3<_T>{a.x / b.x, a.y / b.y, a.z};
}
template <typename _T>
inline vec3<_T> operator/(const vec3<_T> &a, const vec3<_T> &b) {
  return vec3<_T>{a.x / b.x, a.y / b.y, a.z / b.z};
}
template <typename _T>
inline vec3<_T> operator/(const vec3<_T> &a, const vec4<_T> &b) {
  return vec3<_T>{a.x / b.x, a.y / b.y, a.z / b.z};
}

template <typename _T>
inline std::ostream &operator<<(std::ostream &out, const vec3<_T> &v) {
  return out << '<' << v.x << ',' << v.y << ',' << v.z << '>';
}

typedef vec3<float> float3;

} // namespace specula

#endif // SPECULA_MATH_VEC4_HPP_
