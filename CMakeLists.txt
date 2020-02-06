 
# ##############################################################################
# PROJECT
# ##############################################################################
cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)
project(Specula VERSION 2.2.8)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  set(MAIN_PROJECT TRUE)
endif()

# ##############################################################################
# OPTIONS
# ##############################################################################
option(BUILD_TOOL "Compiles binary executable" TRUE)
option(BUILD_DOCS "Compiles documentation" TRUE)
option(ENABLE_PROFILING "Enable profiling" FALSE)
if(NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  option(BUILD_SHARED_LIBS "Compile shared libraries" TRUE)
  option(BUILD_STATIC_LIBS "Compile static libraries" FALSE)
else()
  option(BUILD_STATIC_LIBS "Compile static libraries" TRUE)
  set(BUILD_SHARED_LIBS FALSE)
endif()

option(STATIC_ANALYSIS "Use static analysis tools" FALSE)
option(OPTIMIZE_DEBUG "Enable compile time optimization for debug build" FALSE)
option(ENABLE_GPU "Enables GPU computation" TRUE)
set(SPECULA_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(SPECULA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# ##############################################################################
# GPU COMPUTE
# ##############################################################################
find_package(OpenCL QUIET)
if(OpenCL_FOUND AND ENABLE_GPU)
  message(STATUS "Found OpenCL: ${OpenCL_VERSION_STRING}")
  set(SPECULA_GPU_LIBRARIES ${OpenCL_LIBRARIES})
  set(SPECULA_GPU_INCLUDE_DIRS ${OpenCL_INCLUDE_DIRS})
  set(SPECULA_GPU_FLAGS -DSPECULA_GPU)
else()
  set(SPECULA_GPU_LIBRARIES)
  set(SPECULA_GPU_INCLUDE_DIRS)
  set(SPECULA_GPU_FLAGS)
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
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
              ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
              ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json)
  endif()
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D__DEBUG__")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
if(ENABLE_PROFILING)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DENABLE_PROF")
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
if(STATIC_ANALYSIS OR CMAKE_BUILD_TYPE STREQUAL "Release")
  find_program(
    CLANG_TIDY_EXE
    NAMES "clang-tidy"
    DOC "Path to clang tidy exe")
  if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
  endif()
  find_program(CPPCHECK_EXE NAME "cppcheck" DOC "Path to cppcheck exe")
  if(CPPCHECK_EXE)
    set(CMAKE_CXX_CPPCHECK "${CPPCHECK_EXE}" "--force")
  endif()
  find_program(CPPLINT_EXE "cpplint")
  if(CPPLINT_EXE)
    set(CMAKE_CXX_CPPLINT "${CPPLINT_EXE}")
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
  ${CMAKE_CURRENT_SOURCE_DIR}/include/specula/compiler.hpp
  PREFIX
  SPECULA
  COMPILERS
  ${SPECULA_COMPILERS}
  FEATURES
  cxx_constexpr
  cxx_noexcept
  cxx_static_assert
  cxx_attribute_deprecated)

# ##############################################################################
# LIBRARY
# ##############################################################################
add_subdirectory(src)

# ##############################################################################
# EXECUTABLE
# ##############################################################################
if(BUILD_TOOL)
  add_subdirectory(tools)
endif()

# ##############################################################################
# DOCUMENTATION
# ##############################################################################
if(BUILD_DOCS)
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