#ifndef SPECULA_LOG_HPP_
#define SPECULA_LOG_HPP_

#include <cstdio>
#include <ctime>

#define fatal(msg, ...)                                                     \
  specula::log::log(specula::log::FATAL, msg, __FILE__, __func__, __LINE__, \
                    ##__VA_ARGS__)
#define error(msg, ...)                                                     \
  specula::log::log(specula::log::ERROR, msg, __FILE__, __func__, __LINE__, \
                    ##__VA_ARGS__)
#define warning(msg, ...)                                                     \
  specula::log::log(specula::log::WARNING, msg, __FILE__, __func__, __LINE__, \
                    ##__VA_ARGS__)
#define info(msg, ...)                                                     \
  specula::log::log(specula::log::INFO, msg, __FILE__, __func__, __LINE__, \
                    ##__VA_ARGS__)
#define version(msg, ...)                                                     \
  specula::log::log(specula::log::VERSION, msg, __FILE__, __func__, __LINE__, \
                    ##__VA_ARGS__)

namespace specula {
namespace log {
  enum LogType { FATAL, ERROR, WARNING, INFO, VERSION };

  void init();
  void log(const LogType& type, const char* msg, const char* file,
           const char* func, size_t line, ...);
  void term();

  extern FILE* file_;
  extern bool verbose_;
  extern bool color_;
}  // namespace log
}  // namespace specula

#endif  // SPECULA_LOG_HPP_
