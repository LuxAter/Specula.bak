/**
 * @file os.hpp
 * @brief Os detection
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2020-03-30
 * @ingroup global global-os
 */
#ifndef SPECULA_OS_DETECTION_H
#define SPECULA_OS_DETECTION_H

/**
 * @defgroup global-os Global OS
 * @ingroup global
 *
 * Preprocessor definitions that are used to detect the operating system at
 * compile time.
 */

/**
 * @ingroup global-os
 */
#define SPECULA_OS_IS_Windows 0
/**
 * @ingroup global-os
 */
#define SPECULA_OS_IS_Android 0
/**
 * @ingroup global-os
 */
#define SPECULA_OS_IS_Linux 0
/**
 * @ingroup global-os
 */
#define SPECULA_OS_IS_BSD 0
/**
 * @ingroup global-os
 */
#define SPECULA_OS_IS_HP_UX 0
/**
 * @ingroup global-os
 */
#define SPECULA_OS_IS_AIX 0
/**
 * @ingroup global-os
 */
#define SPECULA_OS_IS_IOS 0
/**
 * @ingroup global-os
 */
#define SPECULA_OS_IS_OSX 0
/**
 * @ingroup global-os
 */
#define SPECULA_OS_IS_Solaris 0

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#undef SPECULA_OS_IS_Windows
#define SPECULA_OS_IS_Windows 1
#elif defined(__ANDROID__)
#undef SPECULA_OS_IS_Android
#define SPECULA_OS_IS_Android 1
#elif defined(__linux__)
#undef SPECULA_OS_IS_Linux
#define SPECULA_OS_IS_Linux 1
#elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
#include <sys/param.h>
#if defined(BSD)
#undef SPECULA_OS_IS_BSD
#define SPECULA_OS_IS_BSD 1
#endif
#elif defined(__hpux)
#undef SPECULA_OS_IS_HP_UX
#define SPECULA_OS_IS_HP_UX 1
#elif defined(__AIX)
#undef SPECULA_OS_IS_AIX
#define SPECULA_OS_IS_AIX 1
#elif defined(__APPLE__) && defined(__MACH__)
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR == 1 || TARGET_OS_IPHONE == 1
#undef SPECULA_OS_IS_IOS
#define SPECULA_OS_IS_IOS 1
#elif TARGET_OS_MAC == 1
#undef SPECULA_OS_IS_OSX
#define SPECULA_OS_IS_OSX 1
#endif
#elif defined(__sun) && defined(__SVR4)
#undef SPECULA_OS_IS_Solaris
#define SPECULA_OS_IS_Solaris 1
#else
#error Unsupported operating system
#endif

#endif // SPECULA_OS_DETECTION_H
