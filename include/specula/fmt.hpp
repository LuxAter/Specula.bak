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
  std::size_t size = fmt_str.size() + _N;
  char *buff = (char *)malloc(sizeof(char) * size);
  vsnprintf(buff, size, fmt_str.c_str(), args);
  va_end(args);
  std::string ret(buff);
  free(buff);
  return ret;
}
template <std::size_t _N = 255>
inline std::string format_len(const std::string fmt_str, std::size_t len, ...) {
  va_list args;
  va_start(args, len);
  std::size_t size = fmt_str.size() + _N + len;
  char *buff = (char *)malloc(sizeof(char) * size);
  vsnprintf(buff, size, fmt_str.c_str(), args);
  va_end(args);
  std::string ret(buff);
  free(buff);
  return ret;
}
template <std::size_t _N = 255>
inline std::string format(const std::string fmt_str, va_list args) {
  std::size_t size = fmt_str.size() + _N;
  char *buff = (char *)malloc(sizeof(char) * size);
  vsnprintf(buff, size, fmt_str.c_str(), args);
  std::string ret(buff);
  free(buff);
  return ret;
}
} // namespace fmt
} // namespace specula

#endif // SPECULA_FMT_HPP_
