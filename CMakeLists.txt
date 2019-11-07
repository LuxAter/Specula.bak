# ##############################################################################
# Project
# ##############################################################################

cmake_minimum_required(VERSION 3.8.2)
project(Specula VERSION 0.2.6 LANGUAGES CXX)

set(LIBRARY_NAME libspecula)
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
set(CMAKE_INSTALL_DOCDIR "${CMAKE_BINARY_DIR}/docs")

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

set(SOURCES
    src/cli/argparse.cpp
    src/log.cpp
    src/image/image_class.cpp
    src/image/png.cpp
    src/image/jpeg.cpp
    src/image/bmp.cpp)
set(EXEC_SOURCES src/main.cpp)

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

add_executable(${EXECUTABLE_NAME} ${EXEC_SOURCES})
target_link_libraries(${EXECUTABLE_NAME} ${LIBRARY_NAME})
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

macro(install)

endmacro()
macro(LOAD_EXTERNAL REPO_NAME)
  string(TOUPPER ${REPO_NAME} MODULE_NAME)
  if(NOT EXISTS ${PROJECT_SOURCE_DIR}/external/${REPO_NAME}/README*
     AND GIT_FOUND)
    execute_process(COMMAND git
                            submodule
                            update
                            --init
                            --
                            external/${REPO_NAME}
                    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
    set(${MODULE_NAME}_FOUND TRUE)
  elseif(NOT GIT_FOUND)
    message(FATAL_ERROR "Git is required for cloning
    ${MODULE_NAME}")
  else()
    set(${MODULE_NAME}_FOUND TRUE)
  endif()
endmacro()

find_package(Threads REQUIRED)
target_link_libraries(${LIBRARY_NAME} ${CMAKE_THREAD_LIBS_INIT})

load_external(libpng)
if(LIBPNG_FOUND)
  set(PNG_TESTS OFF CACHE BOOL "Build libpng tests")
  set(PNG_SHARED OFF CACHE BOOL "Build shared lib")
  add_subdirectory(${PROJECT_SOURCE_DIR}/external/libpng EXCLUDE_FROM_ALL)
  target_include_directories(${LIBRARY_NAME}
                             PUBLIC ${PROJECT_SOURCE_DIR}/external/libpng)
  target_link_libraries(${LIBRARY_NAME} png_static)
endif()

load_external(libjpeg-turbo)
if(LIBJPEG-TURBO_FOUND)
  set(ENABLE_SHARED TRUE CACHE BOOL "Build shared libraries")
  set(
    WITH_JPEG8
    TRUE
    CACHE
      BOOL
      "Emulate libjpeg v8 API/ABI (this makes ${CMAKE_PROJECT_NAME} backward-incompatible with libjpeg v6b)"
    )
  add_subdirectory(${PROJECT_SOURCE_DIR}/external/libjpeg-turbo
                   EXCLUDE_FROM_ALL)
  target_link_libraries(${LIBRARY_NAME} turbojpeg-static)
endif()

load_external(luajit)
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

load_external(sol2)
if(SOL2_FOUND)
  set(SOL2_LUA_VERSION "5.1.5" CACHE STRING "Lua Version")
  add_subdirectory(${PROJECT_SOURCE_DIR}/external/sol2 EXCLUDE_FROM_ALL)
  target_link_libraries(${EXECUTABLE_NAME} sol2::sol2)
endif()

load_external(ChaiScript)
if(CHAISCRIPT_FOUND)
  target_link_libraries(${EXECUTABLE_NAME} ${CMAKE_DL_LIBS})
  target_include_directories(
    ${EXECUTABLE_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/external/ChaiScript/include)
endif()

load_external(filesystem)
if(FILESYSTEM_FOUND)
  add_subdirectory(${PROJECT_SOURCE_DIR}/external/filesystem EXCLUDE_FROM_ALL)
  target_link_libraries(${LIBRARY_NAME} ghc_filesystem)
endif()

load_external(variant)
if(VARIANT_FOUND)
  add_subdirectory(${PROJECT_SOURCE_DIR}/external/variant EXCLUDE_FROM_ALL)
  target_link_libraries(${LIBRARY_NAME} mpark_variant)
endif()

load_external(CLI11)
if(CLI11_FOUND)
  add_subdirectory(${PROJECT_SOURCE_DIR}/external/CLI11 EXCLUDE_FROM_ALL)
  target_link_libraries(${LIBRARY_NAME} CLI11::CLI11)
endif()

load_external(fmt)
if(FMT_FOUND)
  add_subdirectory(external/fmt EXCLUDE_FROM_ALL)
  target_link_libraries(${LIBRARY_NAME} fmt::fmt)
endif()

load_external(spdlog)
if(SPDLOG_FOUND)
  add_subdirectory(external/spdlog EXCLUDE_FROM_ALL)
  target_link_libraries(${LIBRARY_NAME} spdlog::spdlog)
endif()

# find_package(OpenCL) if(OpenCL_FOUND) target_link_libraries(${LIBRARY_NAME}
# OpenCL::OpenCL) target_compile_definitions(${LIBRARY_NAME} PUBLIC
# -D__HAS_OPENCL__) else() message(WARNING "OpenCL was not found") endif()

# ##############################################################################
# Definitions
# ##############################################################################

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(${LIBRARY_NAME} PUBLIC -DDebug)
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
  set(CPACK_GENERATOR "STGZ;TGZ;ZIP")
  _install(TARGETS ${LIBRARY_NAME})
  _install(TARGETS ${EXECUTABLE_NAME})
  set(CPACK_PACKAGE_VENDOR "LuxAter")
  set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
  set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
  set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
  set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
  set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
  set(CPACK_MONOLITHIC_INSTALL TRUE)
  include(CPack)
endif()
