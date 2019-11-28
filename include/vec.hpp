#ifndef SPECULA_VEC_HPP_
#define SPECULA_VEC_HPP_

#include <cstdlib>

#define MONFUNC(name, func)                                                    \
  template <typename T> constexpr inline vec2<T> name(const vec2<T> &v) {      \
    return {func(v.x), func(v.y)};                                             \
  }                                                                            \
  template <typename T> constexpr inline vec3<T> name(const vec3<T> &v) {      \
    return {func(v.x), func(v.y), func(v.z)};                                  \
  }                                                                            \
  template <typename T> constexpr inline vec4<T> name(const vec4<T> &v) {      \
    return {func(v.x), func(v.y), func(v.z), func(v.w)};                       \
  }

#define BINFUNC(name, func)                                                    \
  template <typename T>                                                        \
  constexpr inline vec2<T> name(const vec2<T> &v, const T &a) {                \
    return {func(v.x, a), func(v.y, a)};                                       \
  }                                                                            \
  template <typename T>                                                        \
  constexpr inline vec3<T> name(const vec3<T> &v, const T &a) {                \
    return {func(v.x, a), func(v.y, a), func(v.z, a)};                         \
  }                                                                            \
  template <typename T>                                                        \
  constexpr inline vec4<T> name(const vec4<T> &v, const T &a) {                \
    return {func(v.x, a), func(v.y, a), func(v.z, a), func(v.w, a)};           \
  }                                                                            \
  template <typename T>                                                        \
  constexpr inline vec2<T> name(const vec2<T> &v, const vec2<T> &a) {          \
    return {func(v.x, a.x), func(v.y, a.y)};                                   \
  }                                                                            \
  template <typename T>                                                        \
  constexpr inline vec3<T> name(const vec3<T> &v, const vec3<T> &a) {          \
    return {func(v.x, a.x), func(v.y, a.y), func(v.z, a.z)};                   \
  }                                                                            \
  template <typename T>                                                        \
  constexpr inline vec4<T> name(const vec4<T> &v, const vec4<T> &a) {          \
    return {func(v.x, a.x), func(v.y, a.y), func(v.z, a.z), func(v.w, a.w)};   \
  }

#define TRIFUNC(name, func)                                                    \
  template <typename T>                                                        \
  constexpr inline vec2<T> name(const vec2<T> &v, const T &a, const T &b) {    \
    return {func(v.x, a, b), func(v.y, a, b)};                                 \
  }                                                                            \
  template <typename T>                                                        \
  constexpr inline vec3<T> name(const vec3<T> &v, const T &a, const T &b) {    \
    return {func(v.x, a, b), func(v.y, a, b), func(v.z, a, b)};                \
  }                                                                            \
  template <typename T>                                                        \
  constexpr inline vec4<T> name(const vec4<T> &v, const T &a, const T &b) {    \
    return {func(v.x, a, b), func(v.y, a, b), func(v.z, a, b),                 \
            func(v.w, a, b)};                                                  \
  }                                                                            \
  template <typename T>                                                        \
  constexpr inline vec2<T> name(const vec2<T> &v, const vec2<T> &a,            \
                                const vec2<T> &b) {                            \
    return {func(v.x, a.x, b.x), func(v.y, a.y, b.y)};                         \
  }                                                                            \
  template <typename T>                                                        \
  constexpr inline vec3<T> name(const vec3<T> &v, const vec3<T> &a,            \
                                const vec3<T> &b) {                            \
    return {func(v.x, a.x, b.x), func(v.y, a.y, b.y), func(v.z, a.z, b.z)};    \
  }                                                                            \
  template <typename T>                                                        \
  constexpr inline vec4<T> name(const vec4<T> &v, const vec4<T> &a,            \
                                const vec4<T> &b) {                            \
    return {func(v.x, a.x, b.x), func(v.y, a.y, b.y), func(v.z, a.z, b.z),     \
            func(v.w, a.w, b.w)};                                              \
  }

#define ARITHOP(op)                                                            \
  template <typename T>                                                        \
  constexpr inline vec2<T> operator#op(const vec2<T> &lhs, const T &rhs) {    \
    return {lhs.x op rhs, lhs.y op rhs};                                       \
  }                                                                            \
  template <typename T>                                                        \
  constexpr inline vec3<T> operator#op(const vec3<T> &lhs, const T &rhs) {    \
    return {lhs.x op rhs, lhs.y op rhs, lhs.z op rhs};                         \
  }                                                                            \
  template <typename T>                                                        \
  constexpr inline vec4<T> operator#op(const vec4<T> &lhs, const T &rhs) {    \
    return {lhs.x op rhs, lhs.y op rhs, lhs.z op rhs, lhs.w op rhs};           \
  }                                                                            \
  template <typename T>                                                        \
  constexpr inline vec2<T> operator#op(const vec2<T> &lhs,                    \
                                        const vec2<T> &rhs) {                  \
    return {lhs.x op rhs.x, lhs.y op rhs.y};                                   \
  }                                                                            \
  template <typename T>                                                        \
  constexpr inline vec3<T> operator#op(const vec3<T> &lhs,                    \
                                        const vec3<T> &rhs) {                  \
    return {lhs.x op rhs.x, lhs.y op rhs.y, lhs.z op rhs.z};                   \
  }                                                                            \
  template <typename T>                                                        \
  constexpr inline vec4<T> operator#op(const vec4<T> &lhs,                    \
                                        const vec4<T> &rhs) {                  \
    return {lhs.x op rhs.x, lhs.y op rhs.y, lhs.z op rhs.z, lhs.w op rhs.w};   \
  }

namespace specula {
template <typename T, std::size_t N> struct vecn {};
template <typename T> using vec2 = vecn<T, 2>;
template <typename T> using vec3 = vecn<T, 3>;
template <typename T> using vec4 = vecn<T, 4>;
typedef vecn<unsigned, 2> uvec2;
typedef vecn<unsigned, 3> uvec3;
typedef vecn<unsigned, 4> uvec4;
typedef vecn<float, 2> fvec2;
typedef vecn<float, 3> fvec3;
typedef vecn<float, 4> fvec4;

template <typename T> struct vecn<T, 2> {
  constexpr inline vecn() : x(), y() {}
  template <typename U,
            typename = std::enable_if_t<std::is_convertible<U, T>::value>>
  constexpr inline vecn(const U &v) : x(v), y(v) {}
  template <typename U,
            typename = std::enable_if_t<std::is_convertible<U, T>::value>>
  constexpr inline vecn(const U &x, const U &y) : x(x), y(y) {}
  template <
      typename U, std::size_t N,
      typename = std::enable_if_t<std::is_convertible<U, T>::value && N >= 2>>
  constexpr inline vecn(const vecn<U, N> &copy) : x(copy.x), y(copy.y) {}
  template <
      typename U, std::size_t N,
      typename = std::enable_if_t<std::is_convertible<U, T>::value && N >= 1>>
  constexpr inline vecn(const U &x, const vecn<U, N> &copy) : x(x), y(copy.x) {}

  template <typename U> inline vecn<T, 2> &operator+=(const U &v) {
    *this = *this + v;
    return *this;
  }
  template <typename U> inline vecn<T, 2> &operator-=(const U &v) {
    *this = *this - v;
    return *this;
  }
  template <typename U> inline vecn<T, 2> &operator*=(const U &v) {
    *this = *this * v;
    return *this;
  }
  template <typename U> inline vecn<T, 2> &operator/=(const U &v) {
    *this = *this / v;
    return *this;
  }

  union {
    T x, r, w;
  };
  union {
    T y, g, h;
  };
};
template <typename T> struct vecn<T, 3> {
  constexpr inline vecn() : x(), y(), z() {}
  template <typename U,
            typename = std::enable_if_t<std::is_convertible<U, T>::value>>
  constexpr inline vecn(const U &v) : x(v), y(v), z(v) {}
  template <typename U,
            typename = std::enable_if_t<std::is_convertible<U, T>::value>>
  constexpr inline vecn(const U &x, const U &y, const U &z)
      : x(x), y(y), z(z) {}
  template <
      typename U, std::size_t N,
      typename = std::enable_if_t<std::is_convertible<U, T>::value && N >= 3>>
  constexpr inline vecn(const vecn<U, N> &copy)
      : x(copy.x), y(copy.y), z(copy.z) {}
  template <
      typename U, std::size_t N,
      typename = std::enable_if_t<std::is_convertible<U, T>::value && N >= 2>>
  constexpr inline vecn(const U &x, const vecn<U, N> &copy)
      : x(x), y(copy.x), z(copy.y) {}
  template <
      typename U, std::size_t N,
      typename = std::enable_if_t<std::is_convertible<U, T>::value && N >= 1>>
  constexpr inline vecn(const U &x, const U &y, const vecn<U, N> &copy)
      : x(x), y(y), z(copy.x) {}
  template <
      typename U, std::size_t N,
      typename = std::enable_if_t<std::is_convertible<U, T>::value && N == 2>>
  constexpr inline vecn(const vecn<U, N> &copy, const U &z)
      : x(copy.x), y(copy.y), z(z) {}

  template <typename U> inline vecn<T, 3> &operator+=(const U &v) {
    *this = *this + v;
    return *this;
  }
  template <typename U> inline vecn<T, 3> &operator-=(const U &v) {
    *this = *this - v;
    return *this;
  }
  template <typename U> inline vecn<T, 3> &operator*=(const U &v) {
    *this = *this * v;
    return *this;
  }
  template <typename U> inline vecn<T, 3> &operator/=(const U &v) {
    *this = *this / v;
    return *this;
  }

  union {
    T x, r;
  };
  union {
    T y, g;
  };
  union {
    T z, b;
  };
};
template <typename T> struct vecn<T, 4> {
  constexpr inline vecn() : x(), y(), z(), w() {}
  template <typename U,
            typename = std::enable_if_t<std::is_convertible<U, T>::value>>
  constexpr inline vecn(const U &v) : x(v), y(v), z(v), w(v) {}
  template <typename U,
            typename = std::enable_if_t<std::is_convertible<U, T>::value>>
  constexpr inline vecn(const U &x, const U &y, const U &z, const U &w)
      : x(x), y(y), z(z), w(w) {}
  template <
      typename U, std::size_t N,
      typename = std::enable_if_t<std::is_convertible<U, T>::value && N >= 4>>
  constexpr inline vecn(const vecn<U, N> &copy)
      : x(copy.x), y(copy.y), z(copy.z), w(copy.w) {}
  template <
      typename U, std::size_t N,
      typename = std::enable_if_t<std::is_convertible<U, T>::value && N >= 3>>
  constexpr inline vecn(const U &x, const vecn<U, N> &copy)
      : x(x), y(copy.x), z(copy.y), w(copy.z) {}
  template <
      typename U, std::size_t N,
      typename = std::enable_if_t<std::is_convertible<U, T>::value && N >= 2>>
  constexpr inline vecn(const U &x, const U &y, const vecn<U, N> &copy)
      : x(x), y(y), z(copy.x), w(copy.y) {}
  template <
      typename U, std::size_t N,
      typename = std::enable_if_t<std::is_convertible<U, T>::value && N >= 1>>
  constexpr inline vecn(const U &x, const U &y, const U &z,
                        const vecn<U, N> &copy)
      : x(x), y(y), z(z), w(copy.x) {}
  template <typename U, std::size_t N, std::size_t M,
            typename = std::enable_if_t<std::is_convertible<U, T>::value &&
                                        N == 2 && M >= 2>>
  constexpr inline vecn(const vecn<U, N> &xy, const vecn<U, M> &zw)
      : x(xy.x), y(xy.y), z(zw.x), w(xw.y) {}
  template <typename U, std::size_t N, std::size_t M,
            typename = std::enable_if_t<std::is_convertible<U, T>::value &&
                                        N == 2 && M >= 1>>
  constexpr inline vecn(const vecn<U, N> &xy, const U &z, const vecn<U, M> &w)
      : x(xy.x), y(xy.y), z(z), w(w.x) {}
  template <
      typename U, std::size_t N,
      typename = std::enable_if_t<std::is_convertible<U, T>::value && N == 2>>
  constexpr inline vecn(const vecn<U, N> &xy, const U &z, const U &w)
      : x(xy.x), y(xy.y), z(z), w(w) {}
  template <
      typename U, std::size_t N,
      typename = std::enable_if_t<std::is_convertible<U, T>::value && N == 2>>
  constexpr inline vecn(const U &x, const vecn<U, N> &yz, const U &w)
      : x(x), y(yz.x), z(yz.y), w(w) {}
  template <typename U, std::size_t N, std::size_t M,
            typename = std::enable_if_t<std::is_convertible<U, T>::value &&
                                        N == 3 && M >= 1>>
  constexpr inline vecn(const vecn<U, N> &xyz, const vecn<U, M> &w)
      : x(xyz.x), y(xyz.y), z(xyz.z), w(w.x) {}
  template <
      typename U, std::size_t N,
      typename = std::enable_if_t<std::is_convertible<U, T>::value && N == 3>>
  constexpr inline vecn(const vecn<U, N> &xyz, const U &w)
      : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}

  template <typename U> inline vecn<T, 4> &operator+=(const U &v) {
    *this = *this + v;
    return *this;
  }
  template <typename U> inline vecn<T, 4> &operator-=(const U &v) {
    *this = *this - v;
    return *this;
  }
  template <typename U> inline vecn<T, 4> &operator*=(const U &v) {
    *this = *this * v;
    return *this;
  }
  template <typename U> inline vecn<T, 4> &operator/=(const U &v) {
    *this = *this / v;
    return *this;
  }

  union {
    T x, r;
  };
  union {
    T y, g;
  };
  union {
    T z, b, h;
  };
  union {
    T w, a;
  };
};

namespace {
template <typename T> int __sign(T val) { return (T(0) < val) - (val < T(0)); }
} // namespace

template <typename T>
constexpr inline bool operator==(const vec2<T> &lhs, const vec2<T> &rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}
template <typename T>
constexpr inline bool operator==(const vec3<T> &lhs, const vec3<T> &rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
template <typename T>
constexpr inline bool operator==(const vec4<T> &lhs, const vec4<T> &rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}
template <typename T>
constexpr inline bool operator<(const vec2<T> &lhs, const vec2<T> &rhs) {
  return (lhs.x < rhs.x) || (!(rhs.x < lhs.x) && lhs.y < rhs.y);
}
template <typename T>
constexpr inline bool operator<(const vec3<T> &lhs, const vec3<T> &rhs) {
  return (lhs.x < rhs.x) || (!(rhs.x < lhs.x) && lhs.y < rhs.y) ||
         (!(rhs.y < lhs.y) && lhs.z < rhs.z);
}
template <typename T>
constexpr inline bool operator<(const vec4<T> &lhs, const vec4<T> &rhs) {
  return (lhs.x < rhs.x) || (!(rhs.x < lhs.x) && lhs.y < rhs.y) ||
         (!(rhs.y < lhs.y) && lhs.z < rhs.z) ||
         (!(rhs.z < lhs.z) && lhs.w < rhs.w);
}
template <typename T, std::size_t N>
constexpr inline bool operator!=(const vec<T, N> &lhs, const vec<T, N> &rhs) {
  return !(lhs == rhs);
}
template <typename T, std::size_t N>
constexpr inline bool operator<=(const vec<T, N> &lhs, const vec<T, N> &rhs) {
  return !(rhs < lhs);
}
template <typename T, std::size_t N>
constexpr inline bool operator>(const vec<T, N> &lhs, const vec<T, N> &rhs) {
  return rhs < lhs;
}
template <typename T, std::size_t N>
constexpr inline bool operator>=(const vec<T, N> &lhs, const vec<T, N> &rhs) {
  return !(lhs < rhs);
}

ARITHOP(+)
ARITHOP(-)
ARITHOP(*)
ARITHOP(/)

template <typename T>
constexpr inline vec2<T> operator*(const T &lhs, const vec2<T> &rhs) {
  return {lhs * rhs.x, lhs * rhs.y};
}
template <typename T>
constexpr inline vec3<T> operator*(const T &lhs, const vec3<T> &rhs) {
  return {lhs * rhs.x, lhs * rhs.y, lhs * rhs.z};
}
template <typename T>
constexpr inline vec4<T> operator*(const T &lhs, const vec4<T> &rhs) {
  return {lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w};
}

MONFUNC(abs, std::fabs)
MONFUNC(ceil, std::ceil)
MONFUNC(floor, std::floor)
MONFUNC(sign, __sign)
MONFUNC(exp, std::exp)
MONFUNC(exp2, std::exp2)
MONFUNC(log, std::log)
MONFUNC(sqrt, std::sqrt)
MONFUNC(cbrt, std::cbrt)

BINFUNC(max, std::max)
BINFUNC(min, std::min)
BINFUNC(pow, std::pow)

TRIFUNC(clamp, std::clamp)

template <typename T>
constexpr inline vec3<T> cross(const vec3<T> &lhs, const vec3<T> &rhs) {
  return {lhs.y * rhs.z - rhs.y * lhs.z, lhs.z * rhs.x - rhs.z * lhs.x,
          lhs.x * rhs.y - rhs.x * lhs.y};
}

template <typename T, std::size_t N>
constexpr inline T distance(const vec<T, N> &lhs, const vec<T, N> &rhs) {
  return length(lhs - rhs);
}
template <typename T>
constexpr inline T dot(const vec2<T> &lhs, const vec2<T> &rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y;
}
template <typename T>
constexpr inline T dot(const vec3<T> &lhs, const vec3<T> &rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
template <typename T>
constexpr inline T dot(const vec4<T> &lhs, const vec4<T> &rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}
template <typename T> constexpr inline T length(const vec2<T> &v) {
  return std::sqrt(v.x * v.x + v.y * v.y);
}
template <typename T> constexpr inline T length(const vec3<T> &v) {
  return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
template <typename T> constexpr inline T length(const vec4<T> &v) {
  return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}
template <typename T, std::size_t N>
constexpr inline vec<T, N> normalize(const vec<T, N> &v) {
  return v / length(v);
}
template <typename T, std::size_t N>
constexpr inline vec<T, N> reflect(const vec<T, N> &i,
                                   const vec<T, N> &normal) {
  return i - normal * dot(normal, i) * static_cast<T>(2);
}
template <typename T, std::size_t N>
constexpr inline vec<T, N> refract(const vec<T, N> &i, const vec<T, N> &normal,
                                   const T &eta) {
  T const dot_value = dot(normal, i);
  T const k = static_cast<T>(1) -
              eta * eta * (static_cast<T>(1) - dot_value * dot_value);
  return (k >= static_cast<T>(0))
             ? (eta * i - (eta * dot_value + std::sqrt(k)) * normal)
             : vec<T, N>(0);
}

} // namespace specula

#endif // SPECULA_VEC_HPP_
