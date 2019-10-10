#ifndef SPECULA_FMT_HPP_
#define SPECULA_FMT_HPP_

#include <cstdarg>
#include <string>

namespace specula {
namespace fmt {
template <std::size_t _N = 255>
inline std::string format(const std::string fmt_str, ...) {
  va_list args;
  va_start(args, fmt_str);
  char buff[_N];
  vsnprintf(buff, _N, fmt_str.c_str(), args);
  va_end(args);
  return std::string(buff);
}
template <std::size_t _N = 255>
inline std::string format(const std::string fmt_str, va_list args) {
  char buff[_N];
  vsnprintf(buff, _N, fmt_str.c_str(), args);
  return std::string(buff);
}
// inline std::string format(const std::string fmt_str,
// std::map<std::variant<std::shared_ptr<)
} // namespace fmt
} // namespace specula

#endif // SPECULA_FMT_HPP_
