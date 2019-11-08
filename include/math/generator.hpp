#define FUNC100(func, src)                                                     \
  template <typename _T> inline _T func(const _T &a) { return src(a); }
#define FUNC200(func, src)                                                     \
  template <typename _T> inline vec2<_T> func(const vec2<_T> &a) {             \
    return vec2<_T>{src(a.x), src(a.y)};                                       \
  }
#define FUNC300(func, src)                                                     \
  template <typename _T> inline vec3<_T> func(const vec3<_T> &a) {             \
    return vec3<_T>{src(a.x), src(a.y), src(a.z)};                             \
  }
#define FUNC400(func, src)                                                     \
  template <typename _T> inline vec4<_T> func(const vec4<_T> &a) {             \
    return vec4<_T>{src(a.x), src(a.y), src(a.z), src(a.w)};                   \
  }

#define FUNC110(func, src)                                                     \
  template <typename _T> inline _T func(const _T &a, const _T &b) {            \
    return src(a, b);                                                          \
  }
#define FUNC120(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec2<_T> func(const _T &a, const vec2<_T> &b) {                       \
    return vec2<_T>{src(a, b.x), src(a, b.y)};                                 \
  }
#define FUNC130(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec3<_T> func(const _T &a, const vec3<_T> &b) {                       \
    return vec3<_T>{src(a, b.x), src(a, b.y), src(a, b.z)};                    \
  }
#define FUNC140(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec4<_T> func(const _T &a, const vec4<_T> &b) {                       \
    return vec4<_T>{src(a, b.x), src(a, b.y), src(a, b.z), src(a, b.w)};       \
  }
#define FUNC210(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec2<_T> func(const vec2<_T> &a, const _T &b) {                       \
    return vec2<_T>{src(a.x, b), src(a.y, b)};                                 \
  }
#define FUNC220(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec2<_T> func(const vec2<_T> &a, const vec2<_T> &b) {                 \
    return vec2<_T>{src(a.x, b.x), src(a.y, b.y)};                             \
  }
#define FUNC310(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec3<_T> func(const vec3<_T> &a, const _T &b) {                       \
    return vec3<_T>{src(a.x, b), src(a.y, b), src(a.z, b)};                    \
  }
#define FUNC330(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec3<_T> func(const vec3<_T> &a, const vec3<_T> &b) {                 \
    return vec3<_T>{src(a.x, b.x), src(a.y, b.y), src(a.z, b.z)};              \
  }
#define FUNC410(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec4<_T> func(const vec4<_T> &a, const _T &b) {                       \
    return vec4<_T>{src(a.x, b), src(a.y, b), src(a.z, b), src(a.w, b)};       \
  }
#define FUNC440(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec4<_T> func(const vec4<_T> &a, const vec4<_T> &b) {                 \
    return vec4<_T>{src(a.x, b.x), src(a.y, b.y), src(a.z, b.z),               \
                    src(a.w, b.w)};                                            \
  }

#define FUNC111(func, src)                                                     \
  template <typename _T>                                                       \
  inline _T func(const _T &a, const _T &b, const _T &c) {                      \
    return src(a, b, c);                                                       \
  }
#define FUNC112(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec2<_T> func(const _T &a, const _T &b, const vec2<_T> &c) {          \
    return vec2<_T>{src(a, b, c.x), src(a, b, c.y)};                           \
  }
#define FUNC121(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec2<_T> func(const _T &a, const vec2<_T> &b, const _T &c) {          \
    return vec2<_T>{src(a, b.x, c), src(a, b.y, c)};                           \
  }
#define FUNC122(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec2<_T> func(const _T &a, const vec2<_T> &b, const vec2<_T> &c) {    \
    return vec2<_T>{src(a, b.x, c.x), src(a, b.y, c.y)};                       \
  }
#define FUNC211(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec2<_T> func(const vec2<_T> &a, const _T &b, const _T &c) {          \
    return vec2<_T>{src(a.x, b, c), src(a.y, b, c)};                           \
  }
#define FUNC212(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec2<_T> func(const vec2<_T> &a, const _T &b, const vec2<_T> &c) {    \
    return vec2<_T>{src(a.x, b, c.x), src(a.y, b, c.y)};                       \
  }
#define FUNC221(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec2<_T> func(const vec2<_T> &a, const vec2<_T> &b, const _T &c) {    \
    return vec2<_T>{src(a.x, b.x, c), src(a.y, b.y, c)};                       \
  }
#define FUNC222(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec2<_T> func(const vec2<_T> &a, const vec2<_T> &b,                   \
                       const vec2<_T> &c) {                                    \
    return vec2<_T>{src(a.x, b.x, c.x), src(a.y, b.y, c.y)};                   \
  }
#define FUNC113(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec3<_T> func(const _T &a, const _T &b, const vec3<_T> &c) {          \
    return vec3<_T>{src(a, b, c.x), src(a, b, c.y), src(a, b, c.z)};           \
  }
#define FUNC131(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec3<_T> func(const _T &a, const vec3<_T> &b, const _T &c) {          \
    return vec3<_T>{src(a, b.x, c), src(a, b.y, c), src(a, b.z, c)};           \
  }
#define FUNC133(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec3<_T> func(const _T &a, const vec3<_T> &b, const vec3<_T> &c) {    \
    return vec3<_T>{src(a, b.x, c.x), src(a, b.y, c.y), src(a, b.z, c.z)};     \
  }
#define FUNC311(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec3<_T> func(const vec3<_T> &a, const _T &b, const _T &c) {          \
    return vec3<_T>{src(a.x, b, c), src(a.y, b, c), src(a.z, b, c)};           \
  }
#define FUNC313(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec3<_T> func(const vec3<_T> &a, const _T &b, const vec3<_T> &c) {    \
    return vec3<_T>{src(a.x, b, c.x), src(a.y, b, c.y), src(a.z, b, c.z)};     \
  }
#define FUNC331(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec3<_T> func(const vec3<_T> &a, const vec3<_T> &b, const _T &c) {    \
    return vec3<_T>{src(a.x, b.x, c), src(a.y, b.y, c), src(a.z, b.z, c)};     \
  }
#define FUNC333(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec3<_T> func(const vec3<_T> &a, const vec3<_T> &b,                   \
                       const vec3<_T> &c) {                                    \
    return vec3<_T>{src(a.x, b.x, c.x), src(a.y, b.y, c.y),                    \
                    src(a.z, b.z, c.z)};                                       \
  }
#define FUNC114(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec4<_T> func(const _T &a, const _T &b, const vec4<_T> &c) {          \
    return vec4<_T>{src(a, b, c.x), src(a, b, c.y), src(a, b, c.z),            \
                    src(a, b, c.w)};                                           \
  }
#define FUNC141(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec4<_T> func(const _T &a, const vec4<_T> &b, const _T &c) {          \
    return vec4<_T>{src(a, b.x, c), src(a, b.y, c), src(a, b.z, c),            \
                    src(a, b.w, c)};                                           \
  }
#define FUNC144(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec4<_T> func(const _T &a, const vec4<_T> &b, const vec4<_T> &c) {    \
    return vec4<_T>{src(a, b.x, c.x), src(a, b.y, c.y), src(a, b.z, c.z),      \
                    src(a, b.w, c.w)};                                         \
  }
#define FUNC411(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec4<_T> func(const vec4<_T> &a, const _T &b, const _T &c) {          \
    return vec4<_T>{src(a.x, b, c), src(a.y, b, c), src(a.z, b, c),            \
                    src(a.w, b, c)};                                           \
  }
#define FUNC414(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec4<_T> func(const vec4<_T> &a, const _T &b, const vec4<_T> &c) {    \
    return vec4<_T>{src(a.x, b, c.x), src(a.y, b, c.y), src(a.z, b, c.z),      \
                    src(a.w, b, c.w)};                                         \
  }
#define FUNC441(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec4<_T> func(const vec4<_T> &a, const vec4<_T> &b, const _T &c) {    \
    return vec4<_T>{src(a.x, b.x, c), src(a.y, b.y, c), src(a.z, b.z, c),      \
                    src(a.w, b.w, c)};                                         \
  }
#define FUNC444(func, src)                                                     \
  template <typename _T>                                                       \
  inline vec4<_T> func(const vec4<_T> &a, const vec4<_T> &b,                   \
                       const vec4<_T> &c) {                                    \
    return vec4<_T>{src(a.x, b.x, c.x), src(a.y, b.y, c.y),                    \
                    src(a.z, b.z, c.z), src(a.w, b.w, c.w)};                   \
  }

#define FUNC1(func, src)                                                       \
  FUNC100(func, src)                                                           \
  FUNC200(func, src)                                                           \
  FUNC300(func, src)                                                           \
  FUNC400(func, src)

#define FUNC2(func, src)                                                       \
  FUNC110(func, src)                                                           \
  FUNC120(func, src)                                                           \
  FUNC130(func, src)                                                           \
  FUNC140(func, src)                                                           \
  FUNC210(func, src)                                                           \
  FUNC220(func, src)                                                           \
  FUNC310(func, src)                                                           \
  FUNC330(func, src)                                                           \
  FUNC410(func, src)                                                           \
  FUNC440(func, src)

#define FUNC2V(func, src)                                                      \
  FUNC110(func, src)                                                           \
  FUNC220(func, src)                                                           \
  FUNC330(func, src)                                                           \
  FUNC440(func, src)

#define FUNC3(func, src)                                                       \
  FUNC111(func, src)                                                           \
  FUNC112(func, src)                                                           \
  FUNC121(func, src)                                                           \
  FUNC122(func, src)                                                           \
  FUNC211(func, src)                                                           \
  FUNC212(func, src)                                                           \
  FUNC221(func, src)                                                           \
  FUNC222(func, src)                                                           \
  FUNC113(func, src)                                                           \
  FUNC131(func, src)                                                           \
  FUNC133(func, src)                                                           \
  FUNC311(func, src)                                                           \
  FUNC313(func, src)                                                           \
  FUNC331(func, src)                                                           \
  FUNC333(func, src)                                                           \
  FUNC114(func, src)                                                           \
  FUNC141(func, src)                                                           \
  FUNC144(func, src)                                                           \
  FUNC411(func, src)                                                           \
  FUNC414(func, src)                                                           \
  FUNC441(func, src)                                                           \
  FUNC444(func, src)

#define FUNC3V(func, src)                                                      \
  FUNC111(func, src)                                                           \
  FUNC222(func, src)                                                           \
  FUNC333(func, src)                                                           \
  FUNC444(func, src)
