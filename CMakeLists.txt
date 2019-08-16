# ##############################################################################
# Project
# ##############################################################################

cmake_minimum_required(VERSION 3.8.2)
project(Specula VERSION 0.0.3 LANGUAGES CXX)

set(EXECUTABLE_NAME main)
set(LIBRARY_NAME specula)
set(TEST_NAME unit_tests)
set(TEST_RUNNER_PARAMS "")
option(STATIC_ANALYSIS "Enables static analysis for code" ON)
option(COVERAGE "Enables unit test coverage" ON)
option(DOCUMENTATION "Enables documentation" ON)

# ##############################################################################
# Settings
# ##############################################################################

set(default_build_type "Debug")
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
  set(default_build_type "Debug")
endif()
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(
    STATUS
      "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE
      "${default_build_type}"
      CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()
string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_DEFINE)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -D${CMAKE_BUILD_TYPE_DEFINE})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
  execute_process(COMMAND ${CMAKE_COMMAND}
                          -E
                          copy_if_different
                          ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
                          ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(Git QUIET)

# ##############################################################################
# Static Analysis
# ##############################################################################

if(STATIC_ANALYSIS OR CMAKE_BUILD_TYPE STREQUAL "Release")
  find_program(CLANG_TIDY clang-tidy)
  if(CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY}")
  endif()
  find_program(CPPCHECK cppcheck)
  if(CPPCHECK)
    set(CMAKE_CXX_CPPCHECK "${CPPCHECK}")
  endif()
  find_program(IWYU_TOOL iwyu-tool)
  if(IWYU_TOOL)
    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "${IWYU_TOOL}")
  endif()
endif()

# ##############################################################################
# Files
# ##############################################################################

set(SOURCES src/specula.cpp)

set(TEST_SOURCES tests/main.cpp)
file(GLOB_RECURSE data resources/*)

configure_file("${PROJECT_SOURCE_DIR}/include/version.hpp.in"
               "${PROJECT_BINARY_DIR}/version.hpp")
include_directories("${PROJECT_BINARY_DIR}")

# ##############################################################################
# Targets
# ##############################################################################

add_library(${LIBRARY_NAME} ${SOURCES})
target_include_directories(${LIBRARY_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_options(${LIBRARY_NAME} PUBLIC -Wall -Wfloat-conversion -O3)
else()
  target_compile_options(${LIBRARY_NAME} PUBLIC -Wall -Wfloat-conversion -O0)
endif()
set_target_properties(${LIBRARY_NAME}
                      PROPERTIES CXX_STANDARD
                                 17
                                 CXX_STANDARD_REQUIRED
                                 YES
                                 CXX_EXTENSIONS
                                 NO)

add_executable(${EXECUTABLE_NAME} src/main.cpp)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${LIBRARY_NAME})
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_options(${EXECUTABLE_NAME} PUBLIC -Wall -Wfloat-conversion -O3)
else()
  target_compile_options(${EXECUTABLE_NAME} PUBLIC -Wall -Wfloat-conversion -O0)
endif()
set_target_properties(${EXECUTABLE_NAME}
                      PROPERTIES CXX_STANDARD
                                 17
                                 CXX_STANDARD_REQUIRED
                                 YES
                                 CXX_EXTENSIONS
                                 NO)

file(COPY ${data} DESTINATION resources)

# ##############################################################################
# Dependencies
# ##############################################################################

if(NOT EXISTS ${PROJECT_SOURCE_DIR}/external/doctest/README.md AND GIT_FOUND)
  execute_process(COMMAND git
                          submodule
                          update
                          --init
                          --
                          external/doctest
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
  set(DOCTEST_FOUND TRUE)
elseif(NOT GIT_FOUND)
  message("Git is required for getting dependencies" FATAL_ERROR)
else()
  set(DOCTEST_FOUND TRUE)
endif()
if(NOT EXISTS ${PROJECT_SOURCE_DIR}/external/libpng/README.md AND GIT_FOUND)
  execute_process(COMMAND git
                          submodule
                          update
                          --init
                          --
                          external/libpng
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
  set(LIBPNG_FOUND TRUE)
elseif(NOT GIT_FOUND)
  message("Git is required for getting dependencies" FATAL_ERROR)
else()
  set(LIBPNG_FOUND TRUE)
endif()

if(LIBPNG_FOUND)
  set(PNG_TESTS OFF CACHE BOOL "Build libpng tests")
  set(PNG_SHARED OFF CACHE BOOL "Build shared lib")
  add_subdirectory(${PROJECT_SOURCE_DIR}/external/libpng)
  target_include_directories(${LIBRARY_NAME}
                             PUBLIC ${PROJECT_SOURCE_DIR}/external/libpng)
  target_link_libraries(${LIBRARY_NAME} png_static)
endif()

# ##############################################################################
# Definitions
# ##############################################################################

# ##############################################################################
# Documentation
# ##############################################################################

if(DOCUMENTATION)
  find_package(Doxygen)
  if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
                   ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(docs
                      ${DOXYGEN_EXECUTABLE}
                      ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                      &>
                      doxygen.log
                      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  endif()
endif()

# ##############################################################################
# Testing
# ##############################################################################

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_library(doctest INTERFACE)
  target_include_directories(
    doctest
    INTERFACE ${PROJECT_SOURCE_DIR}/external/doctest/doctest
              ${PROJECT_SOURCE_DIR}/include)
  add_executable(${TEST_NAME} ${TEST_SOURCES})
  target_link_libraries(${TEST_NAME} PRIVATE doctest)
  target_include_directories(${TEST_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
  set_target_properties(${TEST_MAIN}
                        PROPERTIES CXX_STANDARD
                                   17
                                   CXX_STANDARD_REQUIRED
                                   YES
                                   CXX_EXTENSIONS
                                   NO
                                   RUNTIME_OUTPUT_DIRECTORY
                                   ${PROJECT_BINARY_DIR})
  add_test(NAME ${LIBRARY_NAME}.${TEST_NAME}
           COMMAND ${TEST_NAME} ${TEST_RUNNER_PARAMS})
  set(CMAKE_CXX_FLAGS_DEBUG
      "-g -O0 --std=c++17"
      CACHE STRING "Flags used by the C++ compiler during coverage builds."
            FORCE)
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG
      "--std=c++17"
      CACHE STRING "Flags used for linking binaries during coverage builds."
            FORCE)
endif()

# ##############################################################################
# Coverage
# ##############################################################################

if(COVERAGE AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  if("${CMAKE_C_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang"
     OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang")
    find_program(GCOV_TOOL "llvm-cov")
  elseif(CMAKE_COMPILER_IS_GNUCXX)
    find_program(GCOV_TOOL "gcov")
  endif()
  find_program(GCOVR_PATH gcovr)

  if(NOT GCOV_TOOL)
    message(FATAL_ERROR "gcov/llvm-cov not found!")
  endif()
  if(NOT GCOVR_PATH)
    message(FATAL_ERROR "gcovr not found!")
  endif()

  set(CMAKE_CXX_FLAGS_DEBUG
      "-g -O0 --std=c++17 --coverage"
      CACHE STRING "Flags used by the C++ compiler during coverage builds."
            FORCE)
  set(CMAKE_C_FLAGS_DEBUG
      "-g -O0 -fprofile-arcs -ftest-coverage"
      CACHE STRING "Flags used by the C compiler during coverage builds." FORCE)
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG
      "--std=c++17 --coverage"
      CACHE STRING "Flags used for linking binaries during coverage builds."
            FORCE)
  set(CMAKE_SHARED_LINKER_FLAGS_DEBUG
      ""
      CACHE STRING
            "Flags used by the shared libraries linker during coverage builds."
            FORCE)
  mark_as_advanced(CMAKE_CXX_FLAGS_DEBUG
                   CMAKE_C_FLAGS_DEBUG
                   CMAKE_EXE_LINKER_FLAGS_DEBUG
                   CMAKE_SHARED_LINKER_FLAGS_DEBUG)

  add_custom_target(coverage ${TEST_NAME} ${ARGV3}
                    COMMAND mkdir -p coverage
                    COMMAND cd
                            coverage
                            &&
                            ${GCOVR_PATH}
                            --gcov-executable
                            ${GCOV_TOOL}
                            -r
                            ${PROJECT_SOURCE_DIR}
                            -e
                            '.*/tests/.*'
                            -e
                            '.*/external/.*'
                            -s
                            --html
                            --html-details
                            -o
                            index.html
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

# ##############################################################################
# Packaging
# ##############################################################################

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  install(TARGETS ${LIBRARY_NAME} DESTINATION LIBRARY_INSTALL_DR)
  install(DIRECTORY resources DESTINATION LIBRARY_INSTALL_DIR)
  set(CPACK_PACKAGE_NAME "${LIBRARY_NAME}")
  set(
    CPACK_PACKAGE_VERSION

    "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
    )
  set(CPACK_MONOLITHIC_INSTALL TRUE)
  include(CPack)
endif()
