# ##############################################################################
# PROJECT
# ##############################################################################
cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)
project(Specula VERSION 3.0.0)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  set(SPECULA_MAIN_PROJECT TRUE)
  set(CMAKE_VERBOSE_MAKEFILE OFF)
endif()

# ##############################################################################
# BUILD MODE
# ##############################################################################
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE
      "Debug"
      CACHE STRING "Build Mode" FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
  if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
    execute_process(
      COMMAND
        ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
        ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json)
  endif()
endif()

# ##############################################################################
# OPTIONS
# ##############################################################################
option(SPECULA_BUILD_CLI "Compiles CLI executable" ${SPECULA_MAIN_PROJECT})
option(SPECULA_BUILD_GUI "Compiles GUI executable" ${SPECULA_MAIN_PROJECT})
option(SPECULA_BUILD_DOCS "Compiles documentation" ${SPECULA_MAIN_PROJECT})
option(SPECULA_BUILD_TESTS "Compiles Unit Test exectuable"
       ${SPECULA_MAIN_PROJECT})
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  option(SPECULA_PROFILING "Enable profiling" ${SPECULA_MAIN_PROJECT})
  option(SPECULA_STATIC_ANALYSIS "Use static analysis tools" FALSE)
else()
  option(SPECULA_PROFILING "Enable profiling" FALSE)
  option(SPECULA_STATIC_ANALYSIS "Use static analysis tools" TRUE)
endif()
if(NOT CMAKE_SYSTEM_NAME STREQUAL "Windows")
  option(SPECULA_BUILD_SHARED_LIBS "Compile shared libraries" TRUE)
  option(SPECULA_BUILD_STATIC_LIBS "Compile static libraries" FALSE)
else()
  option(SPECULA_BUILD_STATIC_LIBS "Compile static libraries" TRUE)
  set(SPECULA_BUILD_SHARED_LIBS FALSE)
endif()

option(SPECULA_FIX "Apply available static analysis fixes" FALSE)
option(SPECULA_OPTIMIZE_DEBUG
       "Enable compile time optimization for debug build" FALSE)
set(SPECULA_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(SPECULA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# ##############################################################################
# COMPILE FLAGS
# ##############################################################################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D__DEBUG__")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
if(SPECULA_PROFILING)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D__PROFILER__")
endif()
if(OPTIMIZE_DEBUG)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3")
endif()
if(NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNOMINMAX")
endif()

# ##############################################################################
# STATIC ANALYSIS
# ##############################################################################
if(SPECULA_STATIC_ANALYSIS OR CMAKE_BUILD_TYPE STREQUAL "Release")
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
  find_program(CPPCHECK_EXE "cppcheck")
  if(CPPCHECK_EXE)
    message(STATUS "Found cppcheck ${CPPCHECK_EXE}")
    set(CPPCHECK_CMD
        "${CPPCHECK_EXE}"
        "--force"
        "--std=c++17"
        "--enable=warning"
        "--enable=style"
        "--enable=performance"
        "--enable=portability")
  else()
    message(STATUS "Could not find cppcheck")
  endif()
endif()

# ##############################################################################
# DEPENDENCIES
# ##############################################################################
include(WriteCompilerDetectionHeader)
add_subdirectory(external)
set(SPECULA_COMPILERS MSVC GNU Clang Intel AppleClang)
write_compiler_detection_header(
  FILE
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/include/specula/global/compiler.hpp
  PREFIX
  SPECULA
  COMPILERS
  ${SPECULA_COMPILERS}
  FEATURES
  cxx_constexpr
  cxx_deleted_functions
  cxx_extern_templates
  cxx_final
  cxx_noexcept
  cxx_override
  cxx_alignas
  cxx_alignof
  cxx_nullptr
  cxx_static_assert
  cxx_attribute_deprecated
  cxx_thread_local)

# ##############################################################################
# LIBRARY
# ##############################################################################
add_subdirectory(lib)

# ##############################################################################
# CLI EXECUTABLE
# ##############################################################################
if(SPECULA_BUILD_CLI)
  add_subdirectory(cli)
endif()

# ##############################################################################
# GUI EXECUTABLE
# ##############################################################################
if(SPECULA_BUILD_GUI)
  add_subdirectory(gui)
endif()

# ##############################################################################
# TEST EXECUTABLE
# ##############################################################################
if(SPECULA_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

# ##############################################################################
# DOCUMENTATION
# ##############################################################################
if(SPECULA_BUILD_DOCS)
  find_package(Doxygen)
  if(Doxygen_FOUND)
    add_subdirectory(docs)
  endif()
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
