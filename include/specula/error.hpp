#ifndef SPECULA_ERROR_HPP_
#define SPECULA_ERROR_HPP_

#include "log.hpp"

#ifdef __DEBUG__
#define CHECK_EXPR(level, expr)                                                \
  ((expr) ? (void)0                                                            \
          : SPECULA_LOGGER_CALL(specula::logger::get_logger(), level,          \
                                "Check \"{}\" failed", #expr))
#define CHECK_EXPR_TRACE(expr) CHECK_EXPR(spdlog::level::trace, expr)
#define CHECK_EXPR_DEBUG(expr) CHECK_EXPR(spdlog::level::trace, expr)
#define CHECK_EXPR_INFO(expr) CHECK_EXPR(spdlog::level::info, expr)
#define CHECK_EXPR_WARN(expr) CHECK_EXPR(spdlog::level::warn, expr)
#define CHECK_EXPR_ERROR(expr) CHECK_EXPR(spdlog::level::error, expr)
#define CHECK_EXPR_CRITICAL(expr) CHECK_EXPR(spdlog::level::critical, expr)

#define CHECK_EQ(a, b) CHECK_EXPR_CRITICAL(a == b)
#define CHECK_NE(a, b) CHECK_EXPR_CRITICAL(a != b)
#else
#define CHECK_EQ(a, b)
#define CHECK_NE(a, b)
#endif

#endif // SPECULA_ERROR_HPP_