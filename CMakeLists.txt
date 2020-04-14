# ##############################################################################
# PROJECT
# ##############################################################################
cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(Specula VERSION 1.0.0 LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  set(SPECULA_MAIN_PROJECT TRUE)
  set(CMAKE_VERBOSE_MAKEFILE OFF)
endif()
set(SPECULA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SPECULA_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

# ##############################################################################
# BUILD TYPE
# ##############################################################################
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE
      "Debug"
      CACHE STRING "Build Mode" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(BUILD_TYPE_DEBUG ON)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(BUILD_TYPE_RELEASE ON)
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
  set(BUILD_TYPE_MIN_SIZE_REL ON)
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
  set(BUILD_TYPE_REL_WITH_DEB_INFO ON)
endif()

# ##############################################################################
# OPTIONS
# ##############################################################################
option(SPECULA_BUILD_CLI "Compiles CLI executable" ${SPECULA_MAIN_PROJECT})
option(SPECULA_BUILD_DOCS "Compiles documentation" ${SPECULA_MAIN_PROJECT})
option(SPECULA_BUILD_TESTS "Compiles Unit Test exectuable" ${SPECULA_MAIN_PROJECT})
option(SPECULA_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" ${SPECULA_MAIN_PROJECT})

option(SPECULA_ENABLE_PCH "Enable Precompiled Headers" OFF)
option(SPECULA_ENABLE_IPO "Enable Interporcedural Optimization, aka Link Time Optimization (LTO)" OFF)

if(BUILD_TYPE_DEBUG OR REL_WITH_DEB_INFO)
  option(SPECULA_PROFILING "Enable profiling" ${SPECULA_MAIN_PROJECT})
  option(SPECULA_STATIC_ANALYSIS "Use static analysis tools" ${SPECULA_MAIN_PROJECT})
else()
  option(SPECULA_PROFILING "Enable profiling" FALSE)
  option(SPECULA_STATIC_ANALYSIS "Use static analysis tools" FALSE)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  option(SPECULA_ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

  option(SPECULA_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" FALSE)
  option(SPECULA_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" FALSE)
  option(SPECULA_ENALBE_SANITIZER_UNDEFINED_BEHAVIOR "Enable undefined behavior sanitizer" FALSE)
  option(SPECULA_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" FALSE)

  if(SPECULA_ENABLE_SANITIZER_ADDRESS OR SPECULA_ENABLE_SANITIZER_MEMORY OR SPECULA_ENALBE_SANITIZER_UNDEFINED_BEHAVIOR OR SPECULA_ENABLE_SANITIZER_THREAD)
    set(SPECULA_ENABLE_SANITIZERS)
  endif()
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  option(SPECULA_BUILD_SHARED_LIBS "Compile shared libraries" FALSE)
  option(SPECULA_BUILD_STATIC_LIBS "Compile static libraries" TRUE)
else()
  option(SPECULA_BUILD_STATIC_LIBS "Compile static libraries" TRUE)
  option(SPECULA_BUILD_SHARED_LIBS "Compile shared libraries" TRUE)
endif()

if(SPECULA_STATIC_ANALYSIS)
  option(SPECULA_ENABLE_CPPCHECK "Enable cppcheck" TRUE)
  option(SPECULA_ENABLE_CLANG_TIDY "Enable clang-tidy" TRUE)
  option(SPECULA_ENABLE_FIXER "Apply available static analysis fixes" FALSE)
endif()

# ##############################################################################
# CCACHE
# ##############################################################################
find_program(CCACHE ccache)
if(CCACHE)
  message(STATUS "using ccache")
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
else()
  message(STATUS "ccache not found cannot use")
endif()

# ##############################################################################
# IPO
# ##############################################################################
if(SPECULA_ENABLE_IPO)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT IPO_SUPPORT OUTPUT IPO_SUPPORT_MSG)
  if(IPO_SUPPORT)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
  else()
    message(SEND_ERROR "IPO is not supported: ${IPO_SUPPORT_MSG}")
  endif()
endif()

# ##############################################################################
# CONFIG TARGETS
# ##############################################################################
add_library(specula-options INTERFACE)
target_compile_features(specula-options INTERFACE cxx_std_17)
add_library(specula-warnings INTERFACE)

# ##############################################################################
# COVERAGE
# ##############################################################################
if(SPECULA_ENABLE_COVERAGE)
  target_compile_options(specula-options INTERFACE --coverage -O0 -g)
  target_link_libraries(specula-options INTERFACE --coverage)
endif()

# ##############################################################################
# SANITIZERS
# ##############################################################################
if(SPECULA_ENABLE_SANITIZERS)
  set(SANITIZERS "")
  if(SPECULA_ENABLE_SANITIZER_ADDRESS)
    LIST(APPEND SANITIZERS "address")
  endif()
  if(SPECULA_ENABLE_SANITIZER_MEMORY)
    LIST(APPEND SANITIZERS "memory")
  endif()
  if(SPECULA_ENABLE_SANITIZER_UNDEFINED_BEHAVIOR)
    LIST(APPEND SANITIZERS "undefined")
  endif()
  if(SPECULA_ENABLE_SANITIZER_THREAD)
    LIST(APPEND SANITIZERS "thread")
  endif()
  list(JOIN SANITIZERS "," SANITIZERS)
  if(NOT "${SANITIZERS}" STREQUAL "")
    target_compile_options(specula-options INTERFACE -fsanitize=${SANITIZERS})
    target_link_libraries(specula-options INTERFACE -fsanitize=${SANITIZERS})
  endif()
endif()

# ##############################################################################
# WARNINGS
# ##############################################################################
set(MSVC_WARNINGS
    /W4
    /w14242
    /w14254
    /w14263
    /w14265
    /w14287
    /we4289
    /w14296
    /w14311
    /w14545
    /w14546
    /w14547
    /w14549
    /w14555
    /w14619
    /w14640
    /w14826
    /w14905
    /w14906
    /w14928)
set(CLANG_WARNINGS
    -Wall
    -Wextra
    -Wshadow
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Wcast-align
    -Wunused
    -Woverloaded-virtual
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wnull-dereference
    -Wdouble-promotion
    -Wformat=2)
if(SPECULA_WARNINGS_AS_ERRORS)
  set(CLANG_WARNINGS ${CLANG_WARNINGS} -Werror)
  set(MSVC_WARNIGNS ${MSVC_WARNIGNS} /Wx)
endif()
set(GCC_WARNINGS ${CLANG_WARNINGS} -Wmisleading-indentation -Wduplicated-cond
                 -Wduplicated-branches -Wlogical-op -Wuseless-cast)
if(MSVC)
  target_compile_options(specula-warnings INTERFACE ${MSVC_WARNIGNS})
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(specula-warnings INTERFACE ${GNU_WARNINGS})
else()
  target_compile_options(specula-warnings INTERFACE ${CLANG_WARNINGS})
endif()

# ##############################################################################
# STATIC ANALYSIS
# ##############################################################################
if(SPECULA_STATIC_ANALYSIS)
  if(SPECULA_ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE "clang-tidy")
    if(CLANG_TIDY_EXE)
      message(STATUS "Found clang-tidy ${CLANG_TIDY_EXE}")
      set(CLANG_TIDY_CMD "${CLANG_TIDY_EXE}"
                         "--checks=*,-modernize-use-trailing-return-type")
      if(SPECULA_FIX)
        list(APPEND CLANG_TIDY_CMD "--fix")
      endif()
    else()
      message(STATUS "Could not find clang-tidy")
    endif()
  endif()
  if(SPECULA_ENABLE_CPPCHEC)
    find_program(CPPCHECK_EXE "cppcheck")
    if(CPPCHECK_EXE)
      message(STATUS "Found cppcheck ${CPPCHECK_EXE}")
      set(CPPCHECK_CMD
          "${CPPCHECK_EXE}"
          "--suppress=missingInclude"
          "--enable=all"
          "--inconclusive")
    else()
      message(STATUS "Could not find cppcheck")
    endif()
  endif()
endif()

# ##############################################################################
# PCH
# ##############################################################################
if(SPECULA_ENABLE_PCH)
  target_precompile_headers(specula-options INTERFACE <algorithm> <cassert> <cinttypes> <cmath> <cstdint> <cstring> <limits> <memory> <string> <type_traits> <vector>)
endif()

# ##############################################################################
# TARGETS
# ##############################################################################

# CLI
if(SPECULA_BUILD_CLI)
  # add_subdirectory(cli)
endif()

# DEPENDENCIES
add_subdirectory(extern)

# DOCUMENTATION
if(SPECULA_BUILD_DOCS)
  add_subdirectory(docs)
endif()

# TESTING
if(SPECULA_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

# LIBRARY
add_subdirectory(src)

# ##############################################################################
# REPORTING
# ##############################################################################
if(SPECULA_MAIN_PROJECT)
  message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
  message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
  message(STATUS "CMAKE_VERSION: ${CMAKE_VERSION}")
  message(STATUS "CMAKE_GENERATOR: ${CMAKE_GENERATOR}")
  message(STATUS "CMAKE_C_COMPILER_ID: ${CMAKE_C_COMPILER_ID}")
  message(STATUS "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
  message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
endif()

# ##############################################################################
# PACKAGING
# ##############################################################################
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CPACK_GENERATOR "TGZ;ZIP")
  set(CPACK_PACKAGE_VENDOR "LuxAter")
  set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
  set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
  set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
  set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
  set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
  set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
  set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${CMAKE_SYSTEM_NAME}")
  set(CPACK_MONOLITHIC_INSTALL TRUE)
  include(CPack)
endif()
