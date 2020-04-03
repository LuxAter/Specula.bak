/**
 * @file error.hpp
 * @brief Error checking utilities
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2020-04-02
 * @ingroup dev dev-error
 */
#ifndef SPECULA_DEV_ERROR_HPP_
#define SPECULA_DEV_ERROR_HPP_

/**
 * @defgroup dev-error Development Error
 * @ingroup dev
 * This module provides macros to execute runtime checks on values and log
 * messages on their failure. It provides common check expressions for all
 * boolean operations with the set of ``CHECK*`` macros.
 *
 * @note The default log elevel is ``ERROR``, to specify otherwise directly use
 * the ``CHECK_EXPR_*`` macros.
 */

#include "log.hpp"

#ifdef __DEBUG__
/**
 * @brief Evaluates an expression and logs an error on failure.
 * @ingroup dev-error
 *
 * Evaluates a boolean expression, and if ``false`` then logs a message of the
 * specified log level.
 *
 * @param level Level of error to log
 * @param (expr) Expression to evaluate
 */
#define CHECK_EXPR(level, expr)                                                \
  ((expr) ? (void)0                                                            \
          : SPECULA_LOGGER_CALL(specula::logger::get_core(), level,            \
                                "Check \"{}\" failed", #expr))
/**
 * @brief Evaluates an expression and logs a trace message on failure.
 * @ingroup dev-error
 *
 * Evaluates a boolean expression and if ``false``, then logs a trace message.
 *
 * @param expr Expression to evaluate
 * @see CHECK_EXPR
 */
#define CHECK_EXPR_TRACE(expr) CHECK_EXPR(spdlog::level::trace, expr)
/**
 * @brief Evaluates an expression and logs a debug message on failure.
 * @ingroup dev-error
 *
 * Evaluates a boolean expression and if ``false``, then logs a debug message.
 *
 * @param expr Expression to evaluate
 * @see CHECK_EXPR
 */
#define CHECK_EXPR_DEBUG(expr) CHECK_EXPR(spdlog::level::trace, expr)
/**
 * @brief Evaluates an expression and logs an info message on failure.
 * @ingroup dev-error
 *
 * Evaluates a boolean expression and if ``false``, then logs an info message.
 *
 * @param expr Expression to evaluate
 * @see CHECK_EXPR
 */
#define CHECK_EXPR_INFO(expr) CHECK_EXPR(spdlog::level::info, expr)
/**
 * @brief Evaluates an expression and logs a warning message on failure.
 * @ingroup dev-error
 *
 * Evaluates a boolean expression and if ``false``, then logs a warning
 * message.
 *
 * @param expr Expression to evaluate
 * @see CHECK_EXPR
 */
#define CHECK_EXPR_WARN(expr) CHECK_EXPR(spdlog::level::warn, expr)
/**
 * @brief Evaluates an expression and logs an error message on failure.
 * @ingroup dev-error
 *
 * Evaluates a boolean expression and if ``false``, then logs an error message.
 *
 * @param expr Expression to evaluate
 * @see CHECK_EXPR
 */
#define CHECK_EXPR_ERROR(expr) CHECK_EXPR(spdlog::level::error, expr)
/**
 * @brief Evaluates an expression and logs a critical message on failure.
 * @ingroup dev-error
 *
 * Evaluates a boolean expression and if ``false``, then logs a critical
 * message.
 *
 * @param expr Expression to evaluate
 * @see CHECK_EXPR
 */
#define CHECK_EXPR_CRITICAL(expr) CHECK_EXPR(spdlog::level::critical, expr)

/**
 * @brief Evalues an expression and logs an error messsage on failure.
 * @ingroup dev-error
 *
 * @param expr Expression to evaluate.
 * @see CHECK_EXPR_ERROR CHECK_EXPR
 */
#define CHECK(expr) CHECK_EXPR_ERROR((expr))
#define CHECK_EQ(a, b) CHECK((a) == (b))
#define CHECK_NE(a, b) CHECK((a) != (b))
#define CHECK_LT(a, b) CHECK((a) < (b))
#define CHECK_GT(a, b) CHECK((a) > (b))
#define CHECK_LE(a, b) CHECK((a) <= (b))
#define CHECK_GE(a, b) CHECK((a) >= (b))
#else
#define CHECK(expr)
#define CHECK_EQ(a, b)
#define CHECK_NE(a, b)
#define CHECK_LT(a, b)
#define CHECK_GT(a, b)
#define CHECK_LE(a, b)
#define CHECK_GE(a, b)
#endif // __DEBUG__

#endif // SPECULA_DEV_ERROR_HPP_
