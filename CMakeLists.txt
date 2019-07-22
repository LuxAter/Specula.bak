# ##############################################################################
# Project
# ##############################################################################

cmake_minimum_required(VERSION 3.8.2)
project(Specula VERSION 2.0.4 LANGUAGES CXX)

set(EXECUTABLE_NAME main)
set(LIBRARY_NAME specula)
set(TEST_NAME unit_tests)
set(TEST_RUNNER_PARAMS "")

# ##############################################################################
# Settings
# ##############################################################################

set(default_build_type "Release")
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

# ##############################################################################
# Static Analysis
# ##############################################################################

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

# ##############################################################################
# Files
# ##############################################################################

set(SOURCES
    src/specula.cpp
    src/util/log.cpp
    src/cli/argparse.cpp
    src/image/img.cpp
    src/image/png.cpp)

set(TEST_SOURCES tests/main.cpp tests/util/fmt.cpp)
file(GLOB_RECURSE data resources/*)

configure_file("${PROJECT_SOURCE_DIR}/include/version.hpp.in"
               "${PROJECT_BINARY_DIR}/version.hpp")
include_directories("${PROJECT_BINARY_DIR}")

# ##############################################################################
# Targets
# ##############################################################################

add_library(${LIBRARY_NAME} OBJECT ${SOURCES})
target_include_directories(${LIBRARY_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(${LIBRARY_NAME} PUBLIC -Wall -Wfloat-conversion)
set_target_properties(${LIBRARY_NAME}
                      PROPERTIES CXX_STANDARD
                                 17
                                 CXX_STANDARD_REQUIRED
                                 YES
                                 CXX_EXTENSIONS
                                 NO)

add_executable(${EXECUTABLE_NAME} src/main.cpp)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${LIBRARY_NAME})
target_compile_options(${EXECUTABLE_NAME} PUBLIC -Wall -Wfloat-conversion)
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

find_package(PNG REQUIRED)
find_package(Threads REQUIRED)
target_link_libraries(${LIBRARY_NAME}
                      PUBLIC doctest ${PNG_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(${LIBRARY_NAME} PUBLIC ${PNG_INCLUDE_DIRS})

# ##############################################################################
# Definitions
# ##############################################################################

add_definitions(-DCOLOR_DEPTH=8 ${PNG_DEFINITIONS})

# ##############################################################################
# Documentation
# ##############################################################################

find_package(Doxygen)
if(DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
                 ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc
                    ${DOXYGEN_EXECUTABLE}
                    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                    &>
                    doxygen.log
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()

# ##############################################################################
# Testing
# ##############################################################################

add_library(doctest INTERFACE)
target_include_directories(
  doctest
  INTERFACE ${PROJECT_SOURCE_DIR}/external/doctest/doctest)
add_executable(${TEST_NAME} ${TEST_SOURCES})
target_link_libraries(${TEST_NAME} PRIVATE ${LIBRARY_NAME} doctest)
set_target_properties(${TEST_MAIN}
                      PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set_target_properties(${EXECUTABLE_NAME}
                      PROPERTIES CXX_STANDARD
                                 17
                                 CXX_STANDARD_REQUIRED
                                 YES
                                 CXX_EXTENSIONS
                                 NO)
add_test(NAME ${LIBRARY_NAME}.${TEST_NAME}
         COMMAND ${TEST_NAME} ${TEST_RUNNER_PARAMS})

# ##############################################################################
# Coverage
# ##############################################################################

find_program(GCOV_PATH gcov)
find_program(LCOV_PATH lcov)
find_program(GENHTML_PATH genhtml)
find_program(GCOVR_PATH gcovr PATHS ${CMAKE_SOURCE_DIR}/tests)

if(NOT GCOV_PATH)
  message(FATAL_ERROR "gcov not found!")
endif()
if(NOT LCOV_PATH)
  message(FATAL_ERROR "lcov not found!")
endif()
if(NOT GENHTML_PATH)
  message(FATAL_ERROR "genhtml not found!")
endif()

set(CMAKE_CXX_FLAGS_COVERAGE
    "-g -O0 -fprofile-arcs -ftest-coverage"
    CACHE STRING "Flags used by the C++ compiler during coverage builds." FORCE)
set(CMAKE_C_FLAGS_COVERAGE
    "-g -O0 -fprofile-arcs -ftest-coverage"
    CACHE STRING "Flags used by the C compiler during coverage builds." FORCE)
set(
  CMAKE_EXE_LINKER_FLAGS_COVERAGE
  ""
  CACHE STRING "Flags used for linking binaries during coverage builds." FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_COVERAGE
    ""
    CACHE STRING
          "Flags used by the shared libraries linker during coverage builds."
          FORCE)
mark_as_advanced(CMAKE_CXX_FLAGS_COVERAGE
                 CMAKE_C_FLAGS_COVERAGE
                 CMAKE_EXE_LINKER_FLAGS_COVERAGE
                 CMAKE_SHARED_LINKER_FLAGS_COVERAGE)

add_custom_target(coverage
                  ${LCOV_PATH}
                  --directory
                  .
                  --zerocounters
                  COMMAND ${TEST_NAME} ${ARGV3}
                  COMMAND ${LCOV_PATH}
                          --directory
                          .
                          --capture
                          --output-file
                          coverage.info
                  COMMAND ${LCOV_PATH}
                          --remove
                          coverage.info
                          '*/tests/*'
                          '*/external/*'
                          --output-file
                          coverage.info.cleaned
                  COMMAND ${GENHTML_PATH}
                          -o
                          coverage
                          coverage.info.cleaned
                  COMMAND ${LCOV_PATH} --list coverage.info.cleaned
                  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

# ##############################################################################
# Packaging
# ##############################################################################

install(TARGETS ${LIBRARY_NAME} DESTINATION LIBRARY_INSTALL_DR)
install(DIRECTORY resources DESTINATION LIBRARY_INSTALL_DIR)
set(CPACK_PACKAGE_NAME "${LIBRARY_NAME}")
set(
  CPACK_PACKAGE_VERSION
  "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
set(CPACK_MONOLITHIC_INSTALL TRUE)
include(CPack)
