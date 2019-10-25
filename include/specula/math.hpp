#ifndef SPECULA_MATH_HPP_
#define SPECULA_MATH_HPP_

#include <cmath>
#include <optional>
#include <tuple>

namespace specula {
template <typename _T>
std::optional<std::tuple<_T, _T>> quadratic(const _T &a, const _T &b,
                                            const _T &c) {
  _T disc = (b * b) - (4 * a * c);
  if (disc < 0)
    return std::optional<std::tuple<_T, _T>>();
  else if (disc == 0)
    return std::optional<std::tuple<_T, _T>>(std::make_tuple(b / 2.0, b / 2.0));
  else
    return std::optional<std::tuple<_T, _T>>(std::make_tuple(
        -b + std::sqrt(disc) / (2.0 * a), -b - std::sqrt(disc) / (2.0 * a)));
}
} // namespace specula

#endif // SPECULA_MATH_HPP_
