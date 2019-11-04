#ifndef SPECULA_UTIL_PARIS_HPP_
#define SPECULA_UTIL_PARIS_HPP_

#include <cstdlib>
#include <stdexcept>
#include <iostream>

namespace specula {
template <typename _T> struct Size { _T w, h; };
template <typename _T> struct Pos { _T x, y; };

template <typename _T>
std::ostream& operator<<(std::ostream& out, const Size<_T>& rhs){
  out << '(' << rhs.w << ',' << rhs.h << ')';
  return out;
}
template <typename _T>
std::ostream& operator<<(std::ostream& out, const Pos<_T>& rhs){
  out << '(' << rhs.x << ',' << rhs.y << ')';
  return out;
}
} // namespace specula

#endif // SPECULA_UTIL_PARIS_HPP_
