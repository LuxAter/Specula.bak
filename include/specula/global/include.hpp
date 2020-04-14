/**
 * @file include.hpp
 * @brief Global includes
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2020-04-02
 * @ingroup global global-includes
 */
#ifndef SPECULA_GLOBAL_INCLUDE_HPP_
#define SPECULA_GLOBAL_INCLUDE_HPP_

/**
 * @defgroup global-includes Global Includes
 * @ingroup global
 *
 * Many standard library files are required in all files, so this collection of
 * globally included header files, is used instead. This way each header file
 * is only parsed once at compile type, and optimizes compilation.
 *
 * Other commonly used external library headers are also included here.
 */

#include "compiler.hpp"
#include "os.hpp"

#include <algorithm>
#include <cassert>
#include <cinttypes>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#if SPECULA_OS_IS_Windows || SPECULA_OS_IS_BSD || SPECULA_OS_IS_OSX
#include <stdlib.h>
#else
#include <malloc.h>
#endif

#if SPECULA_COMPILER_IS_MSVC == 1
#include <float.h>
#include <intrin.h>
#endif

#include <fmt/format.h>
#include <fmt/ostream.h>

#include "../dev.hpp"

#endif /* end of include guard: SPECULA_GLOBAL_INCLUDE_HPP_ */
