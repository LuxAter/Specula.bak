#ifndef SPECULA_CLI_COLOR_HPP_
#define SPECULA_CLI_COLOR_HPP_

#include <string>

namespace specula {
namespace cli {
inline std::string black(const std::string &msg) {
  return "\033[30m" + msg + "\033[39m";
}
inline std::string red(const std::string &msg) {
  return "\033[31m" + msg + "\033[39m";
}
inline std::string green(const std::string &msg) {
  return "\033[32m" + msg + "\033[39m";
}
inline std::string yellow(const std::string &msg) {
  return "\033[33m" + msg + "\033[39m";
}
inline std::string blue(const std::string &msg) {
  return "\033[34m" + msg + "\033[39m";
}
inline std::string magenta(const std::string &msg) {
  return "\033[35m" + msg + "\033[39m";
}
inline std::string cyan(const std::string &msg) {
  return "\033[36m" + msg + "\033[39m";
}
inline std::string bold(const std::string &msg) {
  return "\033[1m" + msg + "\033[22m";
}
} // namespace cli
} // namespace specula

#endif // SPECULA_CLI_COLOR_HPP_
