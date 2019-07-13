#ifndef SPECULA_UTIL_FMT_HPP_
#define SPECULA_UTIL_FMT_HPP_

#include <sstream>
#include <string>

#include <iostream>

namespace specula {
namespace fmt {
inline std::string fmt(const std::string &fmt_str) { return fmt_str; }
template <typename _T>
std::string fmt(const std::string &fmt_str, const _T &arg) {
  std::string res = fmt_str;
  std::size_t pos = 0;
  if ((pos = fmt_str.find("{}")) != std::string::npos) {
    std::stringstream ss;
    ss << arg;
    res.replace(pos, 2, ss.str());
  }
  return res;
}
template <typename _T, typename... _ARGS>
std::string fmt(const std::string &fmt_str, const _T &arg,
                const _ARGS &... args) {
  std::string res = fmt_str;
  std::size_t pos = 0;
  if ((pos = fmt_str.find("{}")) != std::string::npos) {
    std::stringstream ss;
    ss << arg;
    res.replace(pos, 2, ss.str());
  }
  return fmt(res, args...);
}

} // namespace fmt
} // namespace specula

#endif // SPECULA_UTIL_FMT_HPP_
