
// This is a generated file. Do not edit!

#ifndef SPECULA_COMPILER_DETECTION_H
#define SPECULA_COMPILER_DETECTION_H

#ifdef __cplusplus
# define SPECULA_COMPILER_IS_Comeau 0
# define SPECULA_COMPILER_IS_Intel 0
# define SPECULA_COMPILER_IS_PathScale 0
# define SPECULA_COMPILER_IS_Embarcadero 0
# define SPECULA_COMPILER_IS_Borland 0
# define SPECULA_COMPILER_IS_Watcom 0
# define SPECULA_COMPILER_IS_OpenWatcom 0
# define SPECULA_COMPILER_IS_SunPro 0
# define SPECULA_COMPILER_IS_HP 0
# define SPECULA_COMPILER_IS_Compaq 0
# define SPECULA_COMPILER_IS_zOS 0
# define SPECULA_COMPILER_IS_XLClang 0
# define SPECULA_COMPILER_IS_XL 0
# define SPECULA_COMPILER_IS_VisualAge 0
# define SPECULA_COMPILER_IS_PGI 0
# define SPECULA_COMPILER_IS_Cray 0
# define SPECULA_COMPILER_IS_TI 0
# define SPECULA_COMPILER_IS_Fujitsu 0
# define SPECULA_COMPILER_IS_GHS 0
# define SPECULA_COMPILER_IS_SCO 0
# define SPECULA_COMPILER_IS_ARMCC 0
# define SPECULA_COMPILER_IS_AppleClang 0
# define SPECULA_COMPILER_IS_ARMClang 0
# define SPECULA_COMPILER_IS_Clang 0
# define SPECULA_COMPILER_IS_GNU 0
# define SPECULA_COMPILER_IS_MSVC 0
# define SPECULA_COMPILER_IS_ADSP 0
# define SPECULA_COMPILER_IS_IAR 0
# define SPECULA_COMPILER_IS_MIPSpro 0

#if defined(__COMO__)
# undef SPECULA_COMPILER_IS_Comeau
# define SPECULA_COMPILER_IS_Comeau 1

#elif defined(__INTEL_COMPILER) || defined(__ICC)
# undef SPECULA_COMPILER_IS_Intel
# define SPECULA_COMPILER_IS_Intel 1

#elif defined(__PATHCC__)
# undef SPECULA_COMPILER_IS_PathScale
# define SPECULA_COMPILER_IS_PathScale 1

#elif defined(__BORLANDC__) && defined(__CODEGEARC_VERSION__)
# undef SPECULA_COMPILER_IS_Embarcadero
# define SPECULA_COMPILER_IS_Embarcadero 1

#elif defined(__BORLANDC__)
# undef SPECULA_COMPILER_IS_Borland
# define SPECULA_COMPILER_IS_Borland 1

#elif defined(__WATCOMC__) && __WATCOMC__ < 1200
# undef SPECULA_COMPILER_IS_Watcom
# define SPECULA_COMPILER_IS_Watcom 1

#elif defined(__WATCOMC__)
# undef SPECULA_COMPILER_IS_OpenWatcom
# define SPECULA_COMPILER_IS_OpenWatcom 1

#elif defined(__SUNPRO_CC)
# undef SPECULA_COMPILER_IS_SunPro
# define SPECULA_COMPILER_IS_SunPro 1

#elif defined(__HP_aCC)
# undef SPECULA_COMPILER_IS_HP
# define SPECULA_COMPILER_IS_HP 1

#elif defined(__DECCXX)
# undef SPECULA_COMPILER_IS_Compaq
# define SPECULA_COMPILER_IS_Compaq 1

#elif defined(__IBMCPP__) && defined(__COMPILER_VER__)
# undef SPECULA_COMPILER_IS_zOS
# define SPECULA_COMPILER_IS_zOS 1

#elif defined(__ibmxl__) && defined(__clang__)
# undef SPECULA_COMPILER_IS_XLClang
# define SPECULA_COMPILER_IS_XLClang 1

#elif defined(__IBMCPP__) && !defined(__COMPILER_VER__) && __IBMCPP__ >= 800
# undef SPECULA_COMPILER_IS_XL
# define SPECULA_COMPILER_IS_XL 1

#elif defined(__IBMCPP__) && !defined(__COMPILER_VER__) && __IBMCPP__ < 800
# undef SPECULA_COMPILER_IS_VisualAge
# define SPECULA_COMPILER_IS_VisualAge 1

#elif defined(__PGI)
# undef SPECULA_COMPILER_IS_PGI
# define SPECULA_COMPILER_IS_PGI 1

#elif defined(_CRAYC)
# undef SPECULA_COMPILER_IS_Cray
# define SPECULA_COMPILER_IS_Cray 1

#elif defined(__TI_COMPILER_VERSION__)
# undef SPECULA_COMPILER_IS_TI
# define SPECULA_COMPILER_IS_TI 1

#elif defined(__FUJITSU) || defined(__FCC_VERSION) || defined(__fcc_version)
# undef SPECULA_COMPILER_IS_Fujitsu
# define SPECULA_COMPILER_IS_Fujitsu 1

#elif defined(__ghs__)
# undef SPECULA_COMPILER_IS_GHS
# define SPECULA_COMPILER_IS_GHS 1

#elif defined(__SCO_VERSION__)
# undef SPECULA_COMPILER_IS_SCO
# define SPECULA_COMPILER_IS_SCO 1

#elif defined(__ARMCC_VERSION) && !defined(__clang__)
# undef SPECULA_COMPILER_IS_ARMCC
# define SPECULA_COMPILER_IS_ARMCC 1

#elif defined(__clang__) && defined(__apple_build_version__)
# undef SPECULA_COMPILER_IS_AppleClang
# define SPECULA_COMPILER_IS_AppleClang 1

#elif defined(__clang__) && defined(__ARMCOMPILER_VERSION)
# undef SPECULA_COMPILER_IS_ARMClang
# define SPECULA_COMPILER_IS_ARMClang 1

#elif defined(__clang__)
# undef SPECULA_COMPILER_IS_Clang
# define SPECULA_COMPILER_IS_Clang 1

#elif defined(__GNUC__) || defined(__GNUG__)
# undef SPECULA_COMPILER_IS_GNU
# define SPECULA_COMPILER_IS_GNU 1

#elif defined(_MSC_VER)
# undef SPECULA_COMPILER_IS_MSVC
# define SPECULA_COMPILER_IS_MSVC 1

#elif defined(__VISUALDSPVERSION__) || defined(__ADSPBLACKFIN__) || defined(__ADSPTS__) || defined(__ADSP21000__)
# undef SPECULA_COMPILER_IS_ADSP
# define SPECULA_COMPILER_IS_ADSP 1

#elif defined(__IAR_SYSTEMS_ICC__) || defined(__IAR_SYSTEMS_ICC)
# undef SPECULA_COMPILER_IS_IAR
# define SPECULA_COMPILER_IS_IAR 1


#endif

#  if SPECULA_COMPILER_IS_MSVC

#    if !(_MSC_VER >= 1600)
#      error Unsupported compiler version
#    endif

  /* _MSC_VER = VVRR */
# define SPECULA_COMPILER_VERSION_MAJOR (_MSC_VER / 100)
# define SPECULA_COMPILER_VERSION_MINOR (_MSC_VER % 100)
# if defined(_MSC_FULL_VER)
#  if _MSC_VER >= 1400
    /* _MSC_FULL_VER = VVRRPPPPP */
#   define SPECULA_COMPILER_VERSION_PATCH (_MSC_FULL_VER % 100000)
#  else
    /* _MSC_FULL_VER = VVRRPPPP */
#   define SPECULA_COMPILER_VERSION_PATCH (_MSC_FULL_VER % 10000)
#  endif
# endif
# if defined(_MSC_BUILD)
#  define SPECULA_COMPILER_VERSION_TWEAK (_MSC_BUILD)
# endif

#    if _MSC_VER >= 1900
#      define SPECULA_COMPILER_CXX_CONSTEXPR 1
#    else
#      define SPECULA_COMPILER_CXX_CONSTEXPR 0
#    endif

#    if _MSC_VER >= 1900
#      define SPECULA_COMPILER_CXX_NOEXCEPT 1
#    else
#      define SPECULA_COMPILER_CXX_NOEXCEPT 0
#    endif

#    if _MSC_VER >= 1600
#      define SPECULA_COMPILER_CXX_STATIC_ASSERT 1
#    else
#      define SPECULA_COMPILER_CXX_STATIC_ASSERT 0
#    endif

#    if _MSC_VER >= 1900
#      define SPECULA_COMPILER_CXX_ATTRIBUTE_DEPRECATED 1
#    else
#      define SPECULA_COMPILER_CXX_ATTRIBUTE_DEPRECATED 0
#    endif

#  elif SPECULA_COMPILER_IS_GNU

#    if !((__GNUC__ * 100 + __GNUC_MINOR__) >= 404)
#      error Unsupported compiler version
#    endif

# if defined(__GNUC__)
#  define SPECULA_COMPILER_VERSION_MAJOR (__GNUC__)
# else
#  define SPECULA_COMPILER_VERSION_MAJOR (__GNUG__)
# endif
# if defined(__GNUC_MINOR__)
#  define SPECULA_COMPILER_VERSION_MINOR (__GNUC_MINOR__)
# endif
# if defined(__GNUC_PATCHLEVEL__)
#  define SPECULA_COMPILER_VERSION_PATCH (__GNUC_PATCHLEVEL__)
# endif

#    if (__GNUC__ * 100 + __GNUC_MINOR__) >= 406 && (__cplusplus >= 201103L || (defined(__GXX_EXPERIMENTAL_CXX0X__) && __GXX_EXPERIMENTAL_CXX0X__))
#      define SPECULA_COMPILER_CXX_CONSTEXPR 1
#    else
#      define SPECULA_COMPILER_CXX_CONSTEXPR 0
#    endif

#    if (__GNUC__ * 100 + __GNUC_MINOR__) >= 406 && (__cplusplus >= 201103L || (defined(__GXX_EXPERIMENTAL_CXX0X__) && __GXX_EXPERIMENTAL_CXX0X__))
#      define SPECULA_COMPILER_CXX_NOEXCEPT 1
#    else
#      define SPECULA_COMPILER_CXX_NOEXCEPT 0
#    endif

#    if (__GNUC__ * 100 + __GNUC_MINOR__) >= 404 && (__cplusplus >= 201103L || (defined(__GXX_EXPERIMENTAL_CXX0X__) && __GXX_EXPERIMENTAL_CXX0X__))
#      define SPECULA_COMPILER_CXX_STATIC_ASSERT 1
#    else
#      define SPECULA_COMPILER_CXX_STATIC_ASSERT 0
#    endif

#    if (__GNUC__ * 100 + __GNUC_MINOR__) >= 409 && __cplusplus > 201103L
#      define SPECULA_COMPILER_CXX_ATTRIBUTE_DEPRECATED 1
#    else
#      define SPECULA_COMPILER_CXX_ATTRIBUTE_DEPRECATED 0
#    endif

#  elif SPECULA_COMPILER_IS_Clang

#    if !(((__clang_major__ * 100) + __clang_minor__) >= 301)
#      error Unsupported compiler version
#    endif

# define SPECULA_COMPILER_VERSION_MAJOR (__clang_major__)
# define SPECULA_COMPILER_VERSION_MINOR (__clang_minor__)
# define SPECULA_COMPILER_VERSION_PATCH (__clang_patchlevel__)
# if defined(_MSC_VER)
   /* _MSC_VER = VVRR */
#  define SPECULA_SIMULATE_VERSION_MAJOR (_MSC_VER / 100)
#  define SPECULA_SIMULATE_VERSION_MINOR (_MSC_VER % 100)
# endif

#    if ((__clang_major__ * 100) + __clang_minor__) >= 301 && __has_feature(cxx_constexpr)
#      define SPECULA_COMPILER_CXX_CONSTEXPR 1
#    else
#      define SPECULA_COMPILER_CXX_CONSTEXPR 0
#    endif

#    if ((__clang_major__ * 100) + __clang_minor__) >= 301 && __has_feature(cxx_noexcept)
#      define SPECULA_COMPILER_CXX_NOEXCEPT 1
#    else
#      define SPECULA_COMPILER_CXX_NOEXCEPT 0
#    endif

#    if ((__clang_major__ * 100) + __clang_minor__) >= 301 && __has_feature(cxx_static_assert)
#      define SPECULA_COMPILER_CXX_STATIC_ASSERT 1
#    else
#      define SPECULA_COMPILER_CXX_STATIC_ASSERT 0
#    endif

#    if ((__clang_major__ * 100) + __clang_minor__) >= 304 && __cplusplus > 201103L
#      define SPECULA_COMPILER_CXX_ATTRIBUTE_DEPRECATED 1
#    else
#      define SPECULA_COMPILER_CXX_ATTRIBUTE_DEPRECATED 0
#    endif

#  elif SPECULA_COMPILER_IS_Intel

#    if !(__INTEL_COMPILER >= 1210)
#      error Unsupported compiler version
#    endif

  /* __INTEL_COMPILER = VRP */
# define SPECULA_COMPILER_VERSION_MAJOR (__INTEL_COMPILER/100)
# define SPECULA_COMPILER_VERSION_MINOR (__INTEL_COMPILER/10 % 10)
# if defined(__INTEL_COMPILER_UPDATE)
#  define SPECULA_COMPILER_VERSION_PATCH (__INTEL_COMPILER_UPDATE)
# else
#  define SPECULA_COMPILER_VERSION_PATCH (__INTEL_COMPILER   % 10)
# endif
# if defined(__INTEL_COMPILER_BUILD_DATE)
  /* __INTEL_COMPILER_BUILD_DATE = YYYYMMDD */
#  define SPECULA_COMPILER_VERSION_TWEAK (__INTEL_COMPILER_BUILD_DATE)
# endif
# if defined(_MSC_VER)
   /* _MSC_VER = VVRR */
#  define SPECULA_SIMULATE_VERSION_MAJOR (_MSC_VER / 100)
#  define SPECULA_SIMULATE_VERSION_MINOR (_MSC_VER % 100)
# endif
# if defined(__GNUC__)
#  define SPECULA_SIMULATE_VERSION_MAJOR (__GNUC__)
# elif defined(__GNUG__)
#  define SPECULA_SIMULATE_VERSION_MAJOR (__GNUG__)
# endif
# if defined(__GNUC_MINOR__)
#  define SPECULA_SIMULATE_VERSION_MINOR (__GNUC_MINOR__)
# endif
# if defined(__GNUC_PATCHLEVEL__)
#  define SPECULA_SIMULATE_VERSION_PATCH (__GNUC_PATCHLEVEL__)
# endif

#    if __cpp_constexpr >= 200704 || __INTEL_COMPILER >= 1400 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
#      define SPECULA_COMPILER_CXX_CONSTEXPR 1
#    else
#      define SPECULA_COMPILER_CXX_CONSTEXPR 0
#    endif

#    if __INTEL_COMPILER >= 1400 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
#      define SPECULA_COMPILER_CXX_NOEXCEPT 1
#    else
#      define SPECULA_COMPILER_CXX_NOEXCEPT 0
#    endif

#    if (__cpp_static_assert >= 200410 || __INTEL_COMPILER >= 1210) && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
#      define SPECULA_COMPILER_CXX_STATIC_ASSERT 1
#    else
#      define SPECULA_COMPILER_CXX_STATIC_ASSERT 0
#    endif

#    if __INTEL_COMPILER >= 1500 && ((__cplusplus >= 201300L) || ((__cplusplus == 201103L) && !defined(__INTEL_CXX11_MODE__)) || ((((__INTEL_COMPILER == 1500) && (__INTEL_COMPILER_UPDATE == 1))) && defined(__GXX_EXPERIMENTAL_CXX0X__) && !defined(__INTEL_CXX11_MODE__) ) || (defined(__INTEL_CXX11_MODE__) && defined(__cpp_aggregate_nsdmi)) )
#      define SPECULA_COMPILER_CXX_ATTRIBUTE_DEPRECATED 1
#    else
#      define SPECULA_COMPILER_CXX_ATTRIBUTE_DEPRECATED 0
#    endif

#  elif SPECULA_COMPILER_IS_AppleClang

#    if !(((__clang_major__ * 100) + __clang_minor__) >= 400)
#      error Unsupported compiler version
#    endif

# define SPECULA_COMPILER_VERSION_MAJOR (__clang_major__)
# define SPECULA_COMPILER_VERSION_MINOR (__clang_minor__)
# define SPECULA_COMPILER_VERSION_PATCH (__clang_patchlevel__)
# if defined(_MSC_VER)
   /* _MSC_VER = VVRR */
#  define SPECULA_SIMULATE_VERSION_MAJOR (_MSC_VER / 100)
#  define SPECULA_SIMULATE_VERSION_MINOR (_MSC_VER % 100)
# endif
# define SPECULA_COMPILER_VERSION_TWEAK (__apple_build_version__)

#    if ((__clang_major__ * 100) + __clang_minor__) >= 400 && __has_feature(cxx_constexpr)
#      define SPECULA_COMPILER_CXX_CONSTEXPR 1
#    else
#      define SPECULA_COMPILER_CXX_CONSTEXPR 0
#    endif

#    if ((__clang_major__ * 100) + __clang_minor__) >= 400 && __has_feature(cxx_noexcept)
#      define SPECULA_COMPILER_CXX_NOEXCEPT 1
#    else
#      define SPECULA_COMPILER_CXX_NOEXCEPT 0
#    endif

#    if ((__clang_major__ * 100) + __clang_minor__) >= 400 && __has_feature(cxx_static_assert)
#      define SPECULA_COMPILER_CXX_STATIC_ASSERT 1
#    else
#      define SPECULA_COMPILER_CXX_STATIC_ASSERT 0
#    endif

#    if ((__clang_major__ * 100) + __clang_minor__) >= 501 && __cplusplus > 201103L
#      define SPECULA_COMPILER_CXX_ATTRIBUTE_DEPRECATED 1
#    else
#      define SPECULA_COMPILER_CXX_ATTRIBUTE_DEPRECATED 0
#    endif

#  else
#    error Unsupported compiler
#  endif

#  if defined(SPECULA_COMPILER_CXX_CONSTEXPR) && SPECULA_COMPILER_CXX_CONSTEXPR
#    define SPECULA_CONSTEXPR constexpr
#  else
#    define SPECULA_CONSTEXPR 
#  endif


#  if defined(SPECULA_COMPILER_CXX_NOEXCEPT) && SPECULA_COMPILER_CXX_NOEXCEPT
#    define SPECULA_NOEXCEPT noexcept
#    define SPECULA_NOEXCEPT_EXPR(X) noexcept(X)
#  else
#    define SPECULA_NOEXCEPT
#    define SPECULA_NOEXCEPT_EXPR(X)
#  endif

#  if defined(SPECULA_COMPILER_CXX_STATIC_ASSERT) && SPECULA_COMPILER_CXX_STATIC_ASSERT
#    define SPECULA_STATIC_ASSERT(X) static_assert(X, #X)
#    define SPECULA_STATIC_ASSERT_MSG(X, MSG) static_assert(X, MSG)
#  else
#    define SPECULA_STATIC_ASSERT_JOIN(X, Y) SPECULA_STATIC_ASSERT_JOIN_IMPL(X, Y)
#    define SPECULA_STATIC_ASSERT_JOIN_IMPL(X, Y) X##Y
template<bool> struct SPECULAStaticAssert;
template<> struct SPECULAStaticAssert<true>{};
#    define SPECULA_STATIC_ASSERT(X) enum { SPECULA_STATIC_ASSERT_JOIN(SPECULAStaticAssertEnum, __LINE__) = sizeof(SPECULAStaticAssert<X>) }
#    define SPECULA_STATIC_ASSERT_MSG(X, MSG) enum { SPECULA_STATIC_ASSERT_JOIN(SPECULAStaticAssertEnum, __LINE__) = sizeof(SPECULAStaticAssert<X>) }
#  endif


#  ifndef SPECULA_DEPRECATED
#    if defined(SPECULA_COMPILER_CXX_ATTRIBUTE_DEPRECATED) && SPECULA_COMPILER_CXX_ATTRIBUTE_DEPRECATED
#      define SPECULA_DEPRECATED [[deprecated]]
#      define SPECULA_DEPRECATED_MSG(MSG) [[deprecated(MSG)]]
#    elif SPECULA_COMPILER_IS_GNU || SPECULA_COMPILER_IS_Clang
#      define SPECULA_DEPRECATED __attribute__((__deprecated__))
#      define SPECULA_DEPRECATED_MSG(MSG) __attribute__((__deprecated__(MSG)))
#    elif SPECULA_COMPILER_IS_MSVC
#      define SPECULA_DEPRECATED __declspec(deprecated)
#      define SPECULA_DEPRECATED_MSG(MSG) __declspec(deprecated(MSG))
#    else
#      define SPECULA_DEPRECATED
#      define SPECULA_DEPRECATED_MSG(MSG)
#    endif
#  endif

#endif

#endif
