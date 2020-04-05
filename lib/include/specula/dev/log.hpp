/**
 * @file log.hpp
 * @brief Specula Logging System
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2020-03-14
 * @ingroup dev dev-log
 */
#ifndef SPECULA_LOG_HPP_
#define SPECULA_LOG_HPP_

/**
 * @defgroup dev-log Logging
 * @ingroup dev
 *
 * This module implements a robust logging system that is used by the renderer.
 * The logging system is derived from
 * [spdlog](https://github.com/gabime/spdlog), and so provides all of the
 * features that library provides. For most casses it should be unneccessary to
 * use these functions, but when embedding Specula into a different application
 * it may be useful to incorperate the Specula logs with the applications
 * logging system, or the reverse, where a third party application may want to
 * use Speculas logging system.
 *
 * In either case most calls should be done through the macros, as that also
 * provides the source locations of the call, and thus improve the debugging
 * utility of the log messages.
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>

#ifdef __DEBUG__
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif

#include <spdlog/sinks/base_sink.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/null_sink.h>
#include <spdlog/sinks/ostream_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>

/**
 * @brief Specula logger call
 * @ingroup dev-log
 *
 * @warning This macro should not be called directly by the user, but instead
 * by other macro functions, that provide the ``logger`` and the ``level``.
 *
 * @param logger The ``spdlog`` logger to use.
 * @param level The log level for this message.
 * @param ... Log message and additional arguments for formatting.
 */
#define SPECULA_LOGGER_CALL(logger, level, ...)                                \
  (logger)->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION},       \
                level, __VA_ARGS__)
/**
 * @brief Specula logger call
 * @ingroup dev-log
 *
 * @warning This macro should not be called directly by the user, but instead
 * by other macro functions, that provide the ``logger``, ``level``, ``file``,
 * ``line``, and ``function`` parameters.
 *
 * @param logger The ``spdlog`` logger to use.
 * @param level The log level for this message.
 * @param file The source file the log message is from.
 * @param line The line in the source file of the log message.
 * @param function The function that the log message is from.
 * @param ... Log message and additional arguments for formatting.
 */
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
  SPECULA_LOGGER_TRACE(specula::logger::get_core(), __VA_ARGS__)
#define SPECULA_CLIENT_TRACE(client, ...)                                      \
  SPECULA_LOGGER_TRACE(specula::logger::get_client(client), __VA_ARGS__)
#define SPECULA_CORE_DEBUG(...)                                                \
  SPECULA_LOGGER_DEBUG(specula::logger::get_core(), __VA_ARGS__)
#define SPECULA_CLIENT_DEBUG(client, ...)                                      \
  SPECULA_LOGGER_DEBUG(specula::logger::get_client(client), __VA_ARGS__)
#define SPECULA_CORE_INFO(...)                                                 \
  SPECULA_LOGGER_INFO(specula::logger::get_core(), __VA_ARGS__)
#define SPECULA_CLIENT_INFO(client, ...)                                       \
  SPECULA_LOGGER_INFO(specula::logger::get_client(client), __VA_ARGS__)
#define SPECULA_CORE_WARN(...)                                                 \
  SPECULA_LOGGER_WARN(specula::logger::get_core(), __VA_ARGS__)
#define SPECULA_CLIENT_WARN(client, ...)                                       \
  SPECULA_LOGGER_WARN(specula::logger::get_client(client), __VA_ARGS__)
#define SPECULA_CORE_ERROR(...)                                                \
  SPECULA_LOGGER_ERROR(specula::logger::get_core(), __VA_ARGS__)
#define SPECULA_CLIENT_ERROR(client, ...)                                      \
  SPECULA_LOGGER_ERROR(specula::logger::get_client(client), __VA_ARGS__)
#define SPECULA_CORE_CRITICAL(...)                                             \
  SPECULA_LOGGER_CRITICAL(specula::logger::get_core(), __VA_ARGS__)
#define SPECULA_CLIENT_CRITICAL(client, ...)                                   \
  SPECULA_LOGGER_CRITICAL(specula::logger::get_client(client), __VA_ARGS__)
#define SPECULA_CORE_FATAL(...)                                                \
  SPECULA_LOGGER_FATAL(specula::logger::get_core(), __VA_ARGS__)
#define SPECULA_CLIENT_FATAL(client, ...)                                      \
  SPECULA_LOGGER_FATAL(specula::logger::get_client(client), __VA_ARGS__)

#define SPECULA_CORE_SOURCE_TRACE(file, line, function, ...)                   \
  SPECULA_LOGGER_SOURCE_TRACE(specula::logger::get_core(), file, line,         \
                              function, __VA_ARGS__)
#define SPECULA_CLIENT_SOURCE_TRACE(client, file, line, function, ...)         \
  SPECULA_LOGGER_SOURCE_TRACE(specula::logger::get_client(client), file, line, \
                              function, __VA_ARGS__)
#define SPECULA_CORE_SOURCE_DEBUG(file, line, function, ...)                   \
  SPECULA_LOGGER_SOURCE_DEBUG(specula::logger::get_core(), file, line,         \
                              function, __VA_ARGS__)
#define SPECULA_CLIENT_SOURCE_DEBUG(client, file, line, function, ...)         \
  SPECULA_LOGGER_SOURCE_DEBUG(specula::logger::get_client(client), file, line, \
                              function, __VA_ARGS__)
#define SPECULA_CORE_SOURCE_INFO(file, line, function, ...)                    \
  SPECULA_LOGGER_SOURCE_INFO(specula::logger::get_core(), file, line,          \
                             function, __VA_ARGS__)
#define SPECULA_CLIENT_SOURCE_INFO(client, file, line, function, ...)          \
  SPECULA_LOGGER_SOURCE_INFO(specula::logger::get_client(client), file, line,  \
                             function, __VA_ARGS__)
#define SPECULA_CORE_SOURCE_WARN(file, line, function, ...)                    \
  SPECULA_LOGGER_SOURCE_WARN(specula::logger::get_core(), file, line,          \
                             function, __VA_ARGS__)
#define SPECULA_CLIENT_SOURCE_WARN(client, file, line, function, ...)          \
  SPECULA_LOGGER_SOURCE_WARN(specula::logger::get_client(client), file, line,  \
                             function, __VA_ARGS__)
#define SPECULA_CORE_SOURCE_ERROR(file, line, function, ...)                   \
  SPECULA_LOGGER_SOURCE_ERROR(specula::logger::get_core(), file, line,         \
                              function, __VA_ARGS__)
#define SPECULA_CLIENT_SOURCE_ERROR(client, file, line, function, ...)         \
  SPECULA_LOGGER_SOURCE_ERROR(specula::logger::get_client(client), file, line, \
                              function, __VA_ARGS__)
#define SPECULA_CORE_SOURCE_CRITICAL(file, line, function, ...)                \
  SPECULA_LOGGER_SOURCE_CRITICAL(specula::logger::get_core(), file, line,      \
                                 function, __VA_ARGS__)
#define SPECULA_CLIENT_SOURCE_CRITICAL(client, file, line, function, ...)      \
  SPECULA_LOGGER_SOURCE_CRITICAL(specula::logger::get_client(client), file,    \
                                 line, function, __VA_ARGS__)
#define SPECULA_CORE_SOURCE_FATAL(file, line, function, ...)                   \
  SPECULA_LOGGER_SOURCE_FATAL(specula::logger::get_core(), file, line,         \
                              function, __VA_ARGS__)
#define SPECULA_CLIENT_SOURCE_FATAL(client, file, line, function, ...)         \
  SPECULA_LOGGER_SOURCE_FATAL(specula::logger::get_client(client), file, line, \
                              function, __VA_ARGS__)

/**
 * @brief Logs a trace message for the core logger
 * @ingroup dev-log
 *
 * @param ... Log message and formatting arguments
 */
#define LTRACE(...) SPECULA_CORE_TRACE(__VA_ARGS__)
/**
 * @brief Logs a debug message for the core logger
 * @ingroup dev-log
 *
 * @param ... Log message and formatting arguments
 */
#define LDEBUG(...) SPECULA_CORE_DEBUG(__VA_ARGS__)
/**
 * @brief Logs an info message for the core logger
 * @ingroup dev-log
 *
 * @param ... Log message and formatting arguments
 */
#define LINFO(...) SPECULA_CORE_INFO(__VA_ARGS__)
/**
 * @brief Logs a warning message for the core logger
 * @ingroup dev-log
 *
 * @param ... Log message and formatting arguments
 */
#define LWARN(...) SPECULA_CORE_WARN(__VA_ARGS__)
/**
 * @brief Logs an error message for the core logger
 * @ingroup dev-log
 *
 * @param ... Log message and formatting arguments
 */
#define LERROR(...) SPECULA_CORE_ERROR(__VA_ARGS__)
/**
 * @brief Logs a critical message for the core logger
 * @ingroup dev-log
 *
 * @param ... Log message and formatting arguments
 */
#define LCRITICAL(...) SPECULA_CORE_CRITICAL(__VA_ARGS__)
/**
 * @brief Logs a fatal message for the core logger
 * @ingroup dev-log
 *
 * @param ... Log message and formatting arguments
 */
#define LFATAL(...) SPECULA_CORE_FATAL(__VA_ARGS__)

#define LCTRACE(client, ...) SPECULA_CLIENT_TRACE(client, __VA_ARGS__)
#define LCDEBUG(client, ...) SPECULA_CLIENT_DEBUG(client, __VA_ARGS__)
#define LCINFO(client, ...) SPECULA_CLIENT_INFO(client, __VA_ARGS__)
#define LCWARN(client, ...) SPECULA_CLIENT_WARN(client, __VA_ARGS__)
#define LCERROR(client, ...) SPECULA_CLIENT_ERROR(client, __VA_ARGS__)
#define LCCRITICAL(client, ...) SPECULA_CLIENT_CRITICAL(client, __VA_ARGS__)
#define LCFATAL(client, ...) SPECULA_CLIENT_FATAL(client, __VA_ARGS__)

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

#define LCSTRACE(client, file, line, function, ...)                            \
  SPECULA_CLIENT_SOURCE_TRACE(client, file, line, function, __VA_ARGS__)
#define LCSDEBUG(client, file, line, function, ...)                            \
  SPECULA_CLIENT_SOURCE_DEBUG(client, file, line, function, __VA_ARGS__)
#define LCSINFO(client, file, line, function, ...)                             \
  SPECULA_CLIENT_SOURCE_INFO(client, file, line, function, __VA_ARGS__)
#define LCSWARN(client, file, line, function, ...)                             \
  SPECULA_CLIENT_SOURCE_WARN(client, file, line, function, __VA_ARGS__)
#define LCSERROR(client, file, line, function, ...)                            \
  SPECULA_CLIENT_SOURCE_ERROR(client, file, line, function, __VA_ARGS__)
#define LCSCRITICAL(client, file, line, function, ...)                         \
  SPECULA_CLIENT_SOURCE_CRITICAL(client, file, line, function, __VA_ARGS__)
#define LCSFATAL(client, file, line, function, ...)                            \
  SPECULA_CLIENT_SOURCE_FATAL(client, file, line, function, __VA_ARGS__)

namespace specula {
namespace logger {
typedef spdlog::sinks::rotating_file_sink_mt RotatingFileSink;
typedef spdlog::sinks::daily_file_sink_mt DailyFileSink;
typedef spdlog::sinks::basic_file_sink_mt BasicFileSink;
typedef spdlog::sinks::stdout_sink_mt StdoutSink;
typedef spdlog::sinks::stderr_sink_mt StderrSink;
typedef spdlog::sinks::stdout_color_sink_mt StdoutColorSink;
typedef spdlog::sinks::stderr_color_sink_mt StderrColorSink;
typedef spdlog::sinks::ostream_sink_mt OstreamSink;
typedef spdlog::sinks::null_sink_mt NullSink;

enum LogLevel {
  TRACE = spdlog::level::trace,
  DEBUG = spdlog::level::debug,
  INFO = spdlog::level::info,
  WARN = spdlog::level::warn,
  ERR = spdlog::level::warn,
  CRITICAL = spdlog::level::critical,
  OFF = spdlog::level::off,
};

template <typename Sink, typename... Args>
void register_sink(const LogLevel &sink_level, const Args &... args) {
  push_sink(std::make_shared<Sink>(args...), sink_level);
}
template <typename Sink, typename A0, typename... Args>
typename std::enable_if<!std::is_same<A0, LogLevel>::value, void>::type
register_sink(const A0 &a0, const Args &... args) {
  push_sink(std::make_shared<Sink>(a0, args...), LogLevel::TRACE);
}
template <typename Sink> void register_sink() {
  push_sink(std::make_shared<Sink>(), LogLevel::TRACE);
}

void push_sink(const spdlog::sink_ptr &sink, const LogLevel &sink_level);

bool initialize_core_logger();
bool initialize_logger(const std::string &name);
bool terminate_logger(const std::string &name);

std::shared_ptr<spdlog::logger> get_core();
std::shared_ptr<spdlog::logger> get_client(const std::string &name);

namespace core {
template <typename... _ARGS>
inline void trace(std::string fmt, const _ARGS &... args) {
  get_core()->trace(fmt, args...);
}
template <typename... _ARGS>
inline void debug(std::string fmt, const _ARGS &... args) {
  get_core()->debug(fmt, args...);
}
template <typename... _ARGS>
inline void info(std::string fmt, const _ARGS &... args) {
  get_core()->info(fmt, args...);
}
template <typename... _ARGS>
inline void warn(std::string fmt, const _ARGS &... args) {
  get_core()->warn(fmt, args...);
}
template <typename... _ARGS>
inline void error(std::string fmt, const _ARGS &... args) {
  get_core()->error(fmt, args...);
}
template <typename... _ARGS>
inline void critical(std::string fmt, const _ARGS &... args) {
  get_core()->critical(fmt, args...);
}
} // namespace core
namespace client {
template <typename... _ARGS>
inline void trace(const std::string &logger, std::string fmt,
                  const _ARGS &... args) {
  get_client(logger)->trace(fmt, args...);
}
template <typename... _ARGS>
inline void debug(const std::string &logger, std::string fmt,
                  const _ARGS &... args) {
  get_client(logger)->debug(fmt, args...);
}
template <typename... _ARGS>
inline void info(const std::string &logger, std::string fmt,
                 const _ARGS &... args) {
  get_client(logger)->info(fmt, args...);
}
template <typename... _ARGS>
inline void warn(const std::string &logger, std::string fmt,
                 const _ARGS &... args) {
  get_client(logger)->warn(fmt, args...);
}
template <typename... _ARGS>
inline void error(const std::string &logger, std::string fmt,
                  const _ARGS &... args) {
  get_client(logger)->error(fmt, args...);
}
template <typename... _ARGS>
inline void critical(const std::string &logger, std::string fmt,
                     const _ARGS &... args) {
  get_client(logger)->critical(fmt, args...);
}
} // namespace client
} // namespace logger
} // namespace specula

#endif // SPECULA_LOG_HPP_
