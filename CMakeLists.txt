# ##############################################################################
# Project
# ##############################################################################

cmake_minimum_required(VERSION 3.8.2)
project(Specula VERSION 0.2.0 LANGUAGES CXX)

set(EXECUTABLE_NAME specula)
option(STATIC_ANALYSIS "Enables static analysis for code" ON)
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
  # find_program(CMAKE_CXX_CLANG_TIDY NAMES clang-tidy)
  # find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
  # find_program(CMAKE_CXX_CPPLINT NAMES cpplint)
  # find_program(CMAKE_CXX_INCLUDE_WHAT_YOU_USE NAMES iwyu-tidy)
  # set(CMAKE_LINK_WHAT_YOU_USE TRUE)
endif()

# ##############################################################################
# Files
# ##############################################################################

set(SOURCES src/main.cpp)

configure_file("${PROJECT_SOURCE_DIR}/include/version.hpp.in"
               "${PROJECT_BINARY_DIR}/version.hpp")
include_directories("${PROJECT_BINARY_DIR}")

file(GLOB template_files
     RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/resources
     ${CMAKE_CURRENT_SOURCE_DIR}/resources/*)
foreach(file ${template_files})
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/resources/${file}
                 ${CMAKE_CURRENT_BINARY_DIR}/resources/${file} @ONLY)
endforeach()

file(GLOB template_files
     RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/scripts
     ${CMAKE_CURRENT_SOURCE_DIR}/scripts/*)
foreach(file ${template_files})
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/scripts/${file}
                 ${CMAKE_CURRENT_BINARY_DIR}/scripts/${file} @ONLY)
endforeach()

# ##############################################################################
# Targets
# ##############################################################################

add_executable(${EXECUTABLE_NAME} ${SOURCES})
target_include_directories(${EXECUTABLE_NAME}
                           PUBLIC ${PROJECT_SOURCE_DIR}/include)
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

# ##############################################################################
# Dependencies
# ##############################################################################

find_package(Threads REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} ${CMAKE_THREAD_LIBS_INIT})

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
  message(FATAL_ERROR "Git is required for getting dependencies")
else()
  set(LIBPNG_FOUND TRUE)
endif()

if(LIBPNG_FOUND)
  set(PNG_TESTS OFF CACHE BOOL "Build libpng tests")
  set(PNG_SHARED OFF CACHE BOOL "Build shared lib")
  add_subdirectory(${PROJECT_SOURCE_DIR}/external/libpng)
  target_include_directories(${EXECUTABLE_NAME}
                             PUBLIC ${PROJECT_SOURCE_DIR}/external/libpng)
  target_link_libraries(${EXECUTABLE_NAME} png_static)
endif()

if(NOT EXISTS ${PROJECT_SOURCE_DIR}/external/luajit/README AND GIT_FOUND)
  execute_process(COMMAND git
                          submodule
                          update
                          --init
                          --
                          external/luajit
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
  set(LUAJIT_FOUND TRUE)
elseif(NOT GIT_FOUND)
  message(FATAL_ERROR "Git is required for getting dependencies")
else()
  set(LUAJIT_FOUND TRUE)
endif()

if(LUAJIT_FOUND)
  add_custom_target(luajit
                    COMMAND ${CMAKE_COMMAND}
                            -E
                            copy_directory
                            ${CMAKE_CURRENT_SOURCE_DIR}/external/luajit
                            ${CMAKE_CURRENT_BINARY_DIR}/external/luajit
                    COMMAND cd
                            ${CMAKE_CURRENT_BINARY_DIR}/external/luajit
                            &&
                            make
                            install
                            PREFIX=${CMAKE_CURRENT_BINARY_DIR}/external/luajit)
  add_library(luajit_static STATIC IMPORTED)
  set_property(
    TARGET luajit_static
    PROPERTY IMPORTED_LOCATION
             ${CMAKE_CURRENT_BINARY_DIR}/external/luajit/lib/libluajit-5.1.a)
  add_dependencies(luajit_static luajit)
  target_include_directories(
    ${EXECUTABLE_NAME}
    PUBLIC ${PROJECT_BINARY_DIR}/external/luajit/include/luajit-2.0)
  target_link_libraries(${EXECUTABLE_NAME}
                        luajit_static
                        m
                        dl)
endif()

if(NOT EXISTS ${PROJECT_SOURCE_DIR}/external/sol2/README.md AND GIT_FOUND)
  execute_process(COMMAND git
                          submodule
                          update
                          --init
                          --
                          external/sol2
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
  set(SOL_FOUND TRUE)
elseif(NOT GIT_FOUND)
  message(FATAL_ERROR "Git is required for getting dependencies")
else()
  set(SOL_FOUND TRUE)
endif()

if(SOL_FOUND)
  target_include_directories(${EXECUTABLE_NAME}
                             PUBLIC ${CMAKE_SOURCE_DIR}/external/sol2/include)
endif()

if(NOT EXISTS ${PROJECT_SOURCE_DIR}/external/filesystem/README.md AND GIT_FOUND)
  execute_process(COMMAND git
                          submodule
                          update
                          --init
                          --
                          external/filesystem
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
  set(FILESYSTEM_FOUND TRUE)
elseif(NOT GIT_FOUND)
  message(FATAL_ERROR "Git is required for getting dependencies")
else()
  set(FILESYSTEM_FOUND TRUE)
endif()

if(FILESYSTEM_FOUND)
  target_include_directories(
    ${EXECUTABLE_NAME}
    PUBLIC ${CMAKE_SOURCE_DIR}/external/filesystem/include)
endif()

if(NOT EXISTS ${PROJECT_SOURCE_DIR}/external/variant/README.md AND GIT_FOUND)
  execute_process(COMMAND git
                          submodule
                          update
                          --init
                          --
                          external/variant
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
  set(VARIANT_FOUND TRUE)
elseif(NOT GIT_FOUND)
  message(FATAL_ERROR "Git is required for getting dependencies")
else()
  set(VARIANT_FOUND TRUE)
endif()

if(VARIANT_FOUND)
  target_include_directories(
    ${EXECUTABLE_NAME}
    PUBLIC ${CMAKE_SOURCE_DIR}/external/variant/include)
endif()

if(NOT EXISTS ${PROJECT_SOURCE_DIR}/external/glm/readme.md AND GIT_FOUND)
  execute_process(COMMAND git
                          submodule
                          update
                          --init
                          --
                          external/glm
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
  set(GLM_FOUND TRUE)
elseif(NOT GIT_FOUND)
  message(FATAL_ERROR "Git is required for getting dependencies")
else()
  set(GLM_FOUND TRUE)
endif()

if(GLM_FOUND)
  target_include_directories(${EXECUTABLE_NAME}
                             PUBLIC ${CMAKE_SOURCE_DIR}/external/glm)
endif()

if(NOT EXISTS ${PROJECT_SOURCE_DIR}/external/CLI11/README.md AND GIT_FOUND)
  execute_process(COMMAND git
                          submodule
                          update
                          --init
                          --
                          external/CLI11
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
  set(CLI11_FOUND TRUE)
elseif(NOT GIT_FOUND)
  message(FATAL_ERROR "Git is required for getting dependencies")
else()
  set(CLI11_FOUND TRUE)
endif()

if(CLI11_FOUND)
  target_include_directories(${EXECUTABLE_NAME}
                             PUBLIC ${CMAKE_SOURCE_DIR}/external/CLI11/include)
endif()

if(NOT EXISTS ${PROJECT_SOURCE_DIR}/external/fmt/README.rst AND GIT_FOUND)
  execute_process(COMMAND git
                          submodule
                          update
                          --init
                          --
                          external/fmt
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
  set(FMT_FOUND TRUE)
elseif(NOT GIT_FOUND)
  message(FATAL_ERROR "Git is required for getting dependencies")
else()
  set(FMT_FOUND TRUE)
endif()

if(FMT_FOUND)
  add_subdirectory(external/fmt)
  target_link_libraries(${EXECUTABLE_NAME} fmt::fmt)
endif()

find_package(OpenCL)
if(OpenCL_FOUND)
  target_link_libraries(${EXECUTABLE_NAME} OpenCL::OpenCL)
  target_compile_definitions(${EXECUTABLE_NAME} PUBLIC -D__HAS_OPENCL__)
else()
  message(WARNING "OpenCL was not found")
endif()

# ##############################################################################
# Definitions
# ##############################################################################

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(${EXECUTABLE_NAME} PUBLIC -DDebug)
endif()

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

# ##############################################################################
# Coverage
# ##############################################################################

# ##############################################################################
# Packaging
# ##############################################################################

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  install(TARGETS ${EXECUTABLE_NAME} DESTINATION BIN_INSTALL_DIR)
  install(DIRECTORY resources DESTINATION BIN_INSTALL_DIR)
  set(CPACK_PACKAGE_NAME "${EXECUTABLE_NAME}")
  set(
    CPACK_PACKAGE_VERSION

    "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
    )
  set(CPACK_MONOLITHIC_INSTALL TRUE)
  include(CPack)
endif()
