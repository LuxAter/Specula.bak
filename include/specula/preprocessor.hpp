#ifndef SPECULA_PREPROCESSOR_HPP_
#define SPECULA_PREPROCESSOR_HPP_

#include "log.hpp"

#include "compiler.hpp"
#include "types.hpp"

#ifdef __DEBUG__
#define SPECULA_ASSERT(expr)                                                   \
  ((expr) ? (void)0 : LCRITICAL("Assertion \"{}\" failed", #expr))
#define CHECK_NE(expr, v)                                                   \
  (((expr) != 0) ? (void)0 : LCRITICAL("Assertion \"{}\" failed", #expr))
#else
#define SPECULA_ASSERT(expr) ((void)0)
#endif

#endif // SPECULA_PREPROCESSOR_HPP_
