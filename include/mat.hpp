#ifndef SPECULA_MAT_HPP_
#define SPECULA_MAT_HPP_

#include <array>
#include <cstdlib>

#include "vec.hpp"

namespace specula {
template <typename T, std::size_t N> struct matn {};
template <typename T> using mat2 = matn<T, 2>;
template <typename T> using mat3 = matn<T, 3>;
template <typename T> using mat4 = matn<T, 4>;
typedef matn<unsigned, 2> umat2;
typedef matn<unsigned, 3> umat3;
typedef matn<unsigned, 4> umat4;
typedef matn<float, 2> fmat2;
typedef matn<float, 3> fmat3;
typedef matn<float, 4> fmat4;

template <typename T> struct matn<T, 2> {
  constexpr inline matn() : x(), y() {}
  template <typename U,
            typename = std::enable_if_t<std::is_convertible<U, T>::value>>
  constexpr inline matn(const U &v)
      : x(v, static_cast<T>(0)), y(static_cast<T>(0), v) {}
  template <
      typename U, std::size_t N,
      typename = std::enable_if_t<std::is_convertible<U, T>::value && N >= 2>>
  constexpr inline matn(const vecn<U, N> &x, const vecn<U, N> &y)
      : x(x), y(y) {}
  template <
      typename U, std::size_t N,
      typename = std::enable_if_t<std::is_convertible<U, T>::value && N >= 2>>
  constexpr inline matn(const matn<U, N> &copy) : x(copy.x), y(copy.y) {}
  vecn<T, 2> x, y;
};
} // namespace specula

#endif // SPECULA_MAT_HPP_
