#ifndef SPECULA_FMT_HPP_
#define SPECULA_FMT_HPP_

#include <fmt/core.h>

#include <fmt/format.h>
#include <fmt/ostream.h>

namespace specula {
template <typename S, typename... Args, typename Char = fmt::char_t<S>>
inline std::basic_string<Char> format(const S &format, Args &&... args) {
  return fmt::format(format, args...);
}

} // namespace specula

#endif // SPECULA_FMT_HPP_