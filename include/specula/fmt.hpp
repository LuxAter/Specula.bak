#ifndef SPECULA_FMT_HPP_
#define SPECULA_FMT_HPP_

#include <cstdarg>
#include <string>

namespace specula {
namespace fmt {
inline std::string format(const std::string fmt_str, ...) {
  va_list args;
  va_start(args, fmt_str);
  char buff[255];
  vsnprintf(buff, 255, fmt_str.c_str(), args);
  va_end(args);
  return std::string(buff);
}
inline std::string format(const std::string fmt_str, va_list args) {
  char buff[255];
  vsnprintf(buff, 255, fmt_str.c_str(), args);
  return std::string(buff);
}
} // namespace fmt
} // namespace specula

#endif // SPECULA_FMT_HPP_
