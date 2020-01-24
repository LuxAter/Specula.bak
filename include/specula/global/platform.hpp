#ifndef SPECULA_GLOBALS_PLATFORM_HPP_
#define SPECULA_GLOBALS_PLATFORM_HPP_

#ifdef defined(_WIN32) || defined(_WIN64)
#defined SPECULA_IS_WINDOWS
#endif

#if defined(_MSC_VER)
#define SPECULA_IS_MSCV
#if _MSC_VER == 1800
#define snprintf _snprintf
#endif
#endif

#if defined(SPECULA_IS_MSVC)
#pragma warning(disable : 4305)
#pragma warning(disable : 4244)
#pragma warning(disable : 4843)
#pragma warning(disable : 4267)
#pragma warning(disable : 4838)
#endif

#endif // SPECULA_GLOBALS_PLATFORM_HPP_