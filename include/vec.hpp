#ifndef SPECULA_VEC_HPP_
#define SPECULA_VEC_HPP_

#define MONOP(name, func)                                                      \
  template <typename T> constexpr inline vec2<T> name(const vec2<T> &v) {      \
    return {func(v.x), func(v.y)};                                             \
  }                                                                            \
  template <typename T> constexpr inline vec3<T> name(const vec3<T> &v) {      \
    return {func(v.x), func(v.y), func(v.z)};                                  \
  }                                                                            \
  template <typename T> constexpr inline vec4<T> name(const vec4<T> &v) {      \
    return {func(v.x), func(v.y), func(v.z), func(v.w)};                       \
  }

#define BINOP(name, func)                                                      \
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

#define TRIOP(name, func)                                                      \
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

namespace specula {
template <typename T, std::size_t N> struct vecn {};
template <typename T> using vec2 = vecn<T, 2>;
template <typename T> using vec3 = vecn<T, 3>;
template <typename T> using vec4 = vecn<T, 4>;
typedef vecn<unsigned, 2> unsigned2;
typedef vecn<unsigned, 3> unsigned3;
typedef vecn<unsigned, 4> unsigned4;
typedef vecn<float, 2> float2;
typedef vecn<float, 3> float3;
typedef vecn<float, 4> float4;

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
  union {
    T x, r, w
  };
  union {
    T y, g, h
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
  union {
    T x, r
  };
  union {
    T y, g
  };
  union {
    T z, b
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
  union {
    T x, r
  };
  union {
    T y, g
  };
  union {
    T z, b, h
  };
  union {
    T w, a
  };
};

namespace {
template <typename T> int __sign(T val) { return (T(0) < val) - (val < T(0)); }
} // namespace

MONOP(abs, std::fabs)
MONOP(ceil, std::ceil)
MONOP(floor, std::floor)
MONOP(sign, __sign)
MONOP(exp, std::exp)
MONOP(exp2, std::exp2)
MONOP(log, std::log)
MONOP(sqrt, std::sqrt)
MONOP(cbrt, std::cbrt)

BINOP(max, std::max)
BINOP(min, std::min)
BINOP(pow, std::pow)

TRIOP(clamp, std::clamp)

} // namespace specula

#endif // SPECULA_VEC_HPP_
