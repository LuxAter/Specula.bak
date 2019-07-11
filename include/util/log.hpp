#ifndef SPECULA_UTIL_LOG_HPP_
#define SPECULA_UTIL_LOG_HPP_

#include <cstdio>
#include <ctime>

#define fatal(msg, ...)                                                        \
  specula::log::__log(specula::log::FATAL, msg, __FILE__, __func__, __LINE__,  \
                      ##__VA_ARGS__)
#define error(msg, ...)                                                        \
  specula::log::__log(specula::log::ERROR, msg, __FILE__, __func__, __LINE__,  \
                      ##__VA_ARGS__)
#define warning(msg, ...)                                                      \
  specula::log::__log(specula::log::WARNING, msg, __FILE__, __func__,          \
                      __LINE__, ##__VA_ARGS__)
#define info(msg, ...)                                                         \
  specula::log::__log(specula::log::INFO, msg, __FILE__, __func__, __LINE__,   \
                      ##__VA_ARGS__)
#define success(msg, ...)                                                      \
  specula::log::__log(specula::log::SUCCESS, msg, __FILE__, __func__,          \
                      __LINE__, ##__VA_ARGS__)
#define version(msg, ...)                                                      \
  specula::log::__log(specula::log::VERSION, msg, __FILE__, __func__,          \
                      __LINE__, ##__VA_ARGS__)
#define log(type, msg, ...)                                                    \
  specula::log::__log(type, msg, __FILE__, __func__, __LINE__, ##__VA_ARGS__)

namespace specula {
namespace log {
enum LogType { FATAL, ERROR, WARNING, INFO, SUCCESS, VERSION, TIMER };

bool init();
void __log(const LogType &type, const char *msg, const char *file,
           const char *func, size_t line, ...);
void __log(const char *type, const char *type_color, const char *msg,
           const char *file, const char *func, size_t line, ...);
bool term();

extern FILE *file_;
extern unsigned verbose_;
extern bool color_;
} // namespace log
} // namespace specula

#endif // SPECULA_UTIL_LOG_HPP_
