#ifndef SPECULA_LOG_HPP_
#define SPECULA_LOG_HPP_

#include <cstdlib>
#include <iostream>

#ifdef DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif

#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#define TRACE(...) SPDLOG_TRACE(__VA_ARGS__)
#define LTRACE(...) SPDLOG_TRACE(__VA_ARGS__)
#define LDEBUG(...) SPDLOG_DEBUG(__VA_ARGS__)
#define INFO(...) SPDLOG_INFO(__VA_ARGS__)
#define LINFO(...) SPDLOG_INFO(__VA_ARGS__)
#define WARN(...) SPDLOG_WARN(__VA_ARGS__)
#define LWARN(...) SPDLOG_WARN(__VA_ARGS__)
#define ERROR(...) SPDLOG_ERROR(__VA_ARGS__)
#define LERROR(...) SPDLOG_ERROR(__VA_ARGS__)
#define CRITICAL(...) SPDLOG_CRITICAL(__VA_ARGS__)
#define LCRITICAL(...) SPDLOG_CRITICAL(__VA_ARGS__)

namespace specula {
namespace logger {
bool initalize_logger(const std::size_t &verbosity);
template <typename... _ARGS>
inline void trace(std::string_view fmt, const _ARGS &... args) {
  spdlog::trace(fmt, args...);
}
template <typename... _ARGS>
inline void debug(std::string_view fmt, const _ARGS &... args) {
  spdlog::debug(fmt, args...);
}
template <typename... _ARGS>
inline void info(std::string_view fmt, const _ARGS &... args) {
  spdlog::info(fmt, args...);
}
template <typename... _ARGS>
inline void warn(std::string_view fmt, const _ARGS &... args) {
  spdlog::warn(fmt, args...);
}
template <typename... _ARGS>
inline void error(std::string_view fmt, const _ARGS &... args) {
  spdlog::error(fmt, args...);
}
template <typename... _ARGS>
inline void critical(std::string_view fmt, const _ARGS &... args) {
  spdlog::critical(fmt, args...);
}
} // namespace logger
} // namespace specula

#endif // SPECULA_LOG_HPP_
