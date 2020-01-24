#ifndef SPECULA_LOG_HPP_
#define SPECULA_LOG_HPP_

#include <cstdlib>
#include <iostream>

#ifdef __DEBUG__
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif

#include <spdlog/spdlog.h>
#define SPECULA_LOGGER_CALL(logger, level, ...)                                \
  (logger)->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION},       \
                level, __VA_ARGS__)
#define SPECULA_LOGGER_CALL_SOURCE(logger, level, file, line, function, ...)   \
  (logger)->log(spdlog::source_loc(file, line, function), level, __VA_ARGS__)

#define SPECULA_LOGGER_TRACE(logger, ...)                                      \
  SPECULA_LOGGER_CALL(logger, spdlog::level::trace, __VA_ARGS__)
#define SPECULA_LOGGER_DEBUG(logger, ...)                                      \
  SPECULA_LOGGER_CALL(logger, spdlog::level::debug, __VA_ARGS__)
#define SPECULA_LOGGER_INFO(logger, ...)                                       \
  SPECULA_LOGGER_CALL(logger, spdlog::level::info, __VA_ARGS__)
#define SPECULA_LOGGER_WARN(logger, ...)                                       \
  SPECULA_LOGGER_CALL(logger, spdlog::level::warn, __VA_ARGS__)
#define SPECULA_LOGGER_ERROR(logger, ...)                                      \
  SPECULA_LOGGER_CALL(logger, spdlog::level::err, __VA_ARGS__)
#define SPECULA_LOGGER_CRITICAL(logger, ...)                                   \
  SPECULA_LOGGER_CALL(logger, spdlog::level::critical, __VA_ARGS__)
#define SPECULA_LOGGER_FATAL(logger, ...)                                      \
  SPECULA_LOGGER_CALL(logger, spdlog::level::critical, __VA_ARGS__)

#define SPECULA_LOGGER_SOURCE_TRACE(logger, file, line, function, ...)         \
  SPECULA_LOGGER_SOURCE_CALL(logger, spdlog::level::trace, __VA_ARGS__)
#define SPECULA_LOGGER_SOURCE_DEBUG(logger, file, line, function, ...)         \
  SPECULA_LOGGER_SOURCE_CALL(logger, spdlog::level::debug, __VA_ARGS__)
#define SPECULA_LOGGER_SOURCE_INFO(logger, file, line, function, ...)          \
  SPECULA_LOGGER_SOURCE_CALL(logger, spdlog::level::info, __VA_ARGS__)
#define SPECULA_LOGGER_SOURCE_WARN(logger, file, line, function, ...)          \
  SPECULA_LOGGER_SOURCE_CALL(logger, spdlog::level::warn, __VA_ARGS__)
#define SPECULA_LOGGER_SOURCE_ERROR(logger, file, line, function, ...)         \
  SPECULA_LOGGER_SOURCE_CALL(logger, spdlog::level::err, __VA_ARGS__)
#define SPECULA_LOGGER_SOURCE_CRITICAL(logger, file, line, function, ...)      \
  SPECULA_LOGGER_SOURCE_CALL(logger, spdlog::level::critical, __VA_ARGS__)
#define SPECULA_LOGGER_SOURCE_FATAL(logger, file, line, function, ...)         \
  SPECULA_LOGGER_SOURCE_CALL(logger, spdlog::level::critical, __VA_ARGS__)

#define SPECULA_CORE_TRACE(...)                                                \
  SPECULA_LOGGER_TRACE(ludus::logger::get_logger(), __VA_ARGS__)
#define SPECULA_CORE_DEBUG(...)                                                \
  SPECULA_LOGGER_DEBUG(ludus::logger::get_logger(), __VA_ARGS__)
#define SPECULA_CORE_INFO(...)                                                 \
  SPECULA_LOGGER_INFO(ludus::logger::get_logger(), __VA_ARGS__)
#define SPECULA_CORE_WARN(...)                                                 \
  SPECULA_LOGGER_WARN(ludus::logger::get_logger(), __VA_ARGS__)
#define SPECULA_CORE_ERROR(...)                                                \
  SPECULA_LOGGER_ERROR(ludus::logger::get_logger(), __VA_ARGS__)
#define SPECULA_CORE_CRITICAL(...)                                             \
  SPECULA_LOGGER_CRITICAL(ludus::logger::get_logger(), __VA_ARGS__)
#define SPECULA_CORE_FATAL(...)                                                \
  SPECULA_LOGGER_FATAL(ludus::logger::get_logger(), __VA_ARGS__)

#define SPECULA_CORE_SOURCE_TRACE(file, line, function, ...)                   \
  SPECULA_LOGGER_SOURCE_TRACE(ludus::logger::get_logger(), file, line,         \
                              function, __VA_ARGS__)
#define SPECULA_CORE_SOURCE_DEBUG(file, line, function, ...)                   \
  SPECULA_LOGGER_SOURCE_DEBUG(ludus::logger::get_logger(), file, line,         \
                              function, __VA_ARGS__)
#define SPECULA_CORE_SOURCE_INFO(file, line, function, ...)                    \
  SPECULA_LOGGER_SOURCE_INFO(ludus::logger::get_logger(), file, line,          \
                             function, __VA_ARGS__)
#define SPECULA_CORE_SOURCE_WARN(file, line, function, ...)                    \
  SPECULA_LOGGER_SOURCE_WARN(ludus::logger::get_logger(), file, line,          \
                             function, __VA_ARGS__)
#define SPECULA_CORE_SOURCE_ERROR(file, line, function, ...)                   \
  SPECULA_LOGGER_SOURCE_ERROR(ludus::logger::get_logger(), file, line,         \
                              function, __VA_ARGS__)
#define SPECULA_CORE_SOURCE_CRITICAL(file, line, function, ...)                \
  SPECULA_LOGGER_SOURCE_CRITICAL(ludus::logger::get_logger(), file, line,      \
                                 function, __VA_ARGS__)
#define SPECULA_CORE_SOURCE_FATAL(file, line, function, ...)                   \
  SPECULA_LOGGER_SOURCE_FATAL(ludus::logger::get_logger(), file, line,         \
                              function, __VA_ARGS__)

#define LTRACE(...) SPECULA_CORE_TRACE(__VA_ARGS__)
#define LDEBUG(...) SPECULA_CORE_DEBUG(__VA_ARGS__)
#define LINFO(...) SPECULA_CORE_INFO(__VA_ARGS__)
#define LWARN(...) SPECULA_CORE_WARN(__VA_ARGS__)
#define LERROR(...) SPECULA_CORE_ERROR(__VA_ARGS__)
#define LCRITICAL(...) SPECULA_CORE_CRITICAL(__VA_ARGS__)
#define LFATAL(...) SPECULA_CORE_FATAL(__VA_ARGS__)

#define LCTRACE(...) SPECULA_CLIENT_TRACE(__VA_ARGS__)
#define LCDEBUG(...) SPECULA_CLIENT_DEBUG(__VA_ARGS__)
#define LCINFO(...) SPECULA_CLIENT_INFO(__VA_ARGS__)
#define LCWARN(...) SPECULA_CLIENT_WARN(__VA_ARGS__)
#define LCERROR(...) SPECULA_CLIENT_ERROR(__VA_ARGS__)
#define LCCRITICAL(...) SPECULA_CLIENT_CRITICAL(__VA_ARGS__)
#define LCFATAL(...) SPECULA_CLIENT_FATAL(__VA_ARGS__)

#define LSTRACE(file, line, function, ...)                                     \
  SPECULA_CORE_SOURCE_TRACE(file, line, function, __VA_ARGS__)
#define LSDEBUG(file, line, function, ...)                                     \
  SPECULA_CORE_SOURCE_DEBUG(file, line, function, __VA_ARGS__)
#define LSINFO(file, line, function, ...)                                      \
  SPECULA_CORE_SOURCE_INFO(file, line, function, __VA_ARGS__)
#define LSWARN(file, line, function, ...)                                      \
  SPECULA_CORE_SOURCE_WARN(file, line, function, __VA_ARGS__)
#define LSERROR(file, line, function, ...)                                     \
  SPECULA_CORE_SOURCE_ERROR(file, line, function, __VA_ARGS__)
#define LSCRITICAL(file, line, function, ...)                                  \
  SPECULA_CORE_SOURCE_CRITICAL(file, line, function, __VA_ARGS__)
#define LSFATAL(file, line, function, ...)                                     \
  SPECULA_CORE_SOURCE_FATAL(file, line, function, __VA_ARGS__)

#define LCSTRACE(file, line, function, ...)                                    \
  SPECULA_CLIENT_SOURCE_TRACE(file, line, function, __VA_ARGS__)
#define LCSDEBUG(file, line, function, ...)                                    \
  SPECULA_CLIENT_SOURCE_DEBUG(file, line, function, __VA_ARGS__)
#define LCSINFO(file, line, function, ...)                                     \
  SPECULA_CLIENT_SOURCE_INFO(file, line, function, __VA_ARGS__)
#define LCSWARN(file, line, function, ...)                                     \
  SPECULA_CLIENT_SOURCE_WARN(file, line, function, __VA_ARGS__)
#define LCSERROR(file, line, function, ...)                                    \
  SPECULA_CLIENT_SOURCE_ERROR(file, line, function, __VA_ARGS__)
#define LCSCRITICAL(file, line, function, ...)                                 \
  SPECULA_CLIENT_SOURCE_CRITICAL(file, line, function, __VA_ARGS__)
#define LCSFATAL(file, line, function, ...)                                    \
  SPECULA_CLIENT_SOURCE_FATAL(file, line, function, __VA_ARGS__)

namespace ludus {
namespace logger {
enum LogLevel {
  TRACE = spdlog::level::trace,
  DEBUG = spdlog::level::debug,
  INFO = spdlog::level::info,
  WARN = spdlog::level::warn,
  ERR = spdlog::level::warn,
  CRITICAL = spdlog::level::critical,
  OFF = spdlog::level::off,
};

#ifdef __DEBUG__
bool initalize_logger(const LogLevel &console_level = DEBUG,
                      const LogLevel &file_level = TRACE);
#else
bool initalize_logger(const LogLevel &console_level = OFF,
                      const LogLevel &file_lavel = INFO);
#endif

std::shared_ptr<spdlog::logger> get_logger();

template <typename... _ARGS>
inline void trace(std::string fmt, const _ARGS &... args) {
  get_logger()->trace(fmt, args...);
}
template <typename... _ARGS>
inline void debug(std::string fmt, const _ARGS &... args) {
  get_logger()->debug(fmt, args...);
}
template <typename... _ARGS>
inline void info(std::string fmt, const _ARGS &... args) {
  get_logger()->info(fmt, args...);
}
template <typename... _ARGS>
inline void warn(std::string fmt, const _ARGS &... args) {
  get_logger()->warn(fmt, args...);
}
template <typename... _ARGS>
inline void error(std::string fmt, const _ARGS &... args) {
  get_logger()->error(fmt, args...);
}
template <typename... _ARGS>
inline void critical(std::string fmt, const _ARGS &... args) {
  get_logger()->info(fmt, args...);
}
} // namespace logger

} // namespace ludus

#endif // SPECULA_LOG_HPP_
