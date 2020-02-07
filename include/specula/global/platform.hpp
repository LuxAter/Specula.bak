#ifndef SPECULA_GLOBALS_PLATFORM_HPP_
#define SPECULA_GLOBALS_PLATFORM_HPP_

#include "compiler.hpp"

#if SPECULA_COMPILER_IS_MSVC
#pragma warning(disable : 4305)
#pragma warning(disable : 4244)
#pragma warning(disable : 4843)
#pragma warning(disable : 4267)
#pragma warning(disable : 4838)
#endif

#endif // SPECULA_GLOBALS_PLATFORM_HPP_