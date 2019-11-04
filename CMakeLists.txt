# ##############################################################################
# Project
# ##############################################################################

cmake_minimum_required(VERSION 3.8.2)
project(Specula VERSION 0.2.1 LANGUAGES CXX)

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
    src/main.cpp
    src/cli/argparse.cpp
    src/log.cpp
    src/image/image_class.cpp)

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
target_link_libraries(${EXECUTABLE_NAME} ${CMAKE_THREAD_LIBS_INIT})

load_external(libpng)
if(LIBPNG_FOUND)
  set(PNG_TESTS OFF CACHE BOOL "Build libpng tests")
  set(PNG_SHARED OFF CACHE BOOL "Build shared lib")
  add_subdirectory(${PROJECT_SOURCE_DIR}/external/libpng)
  target_include_directories(${EXECUTABLE_NAME}
                             PUBLIC ${PROJECT_SOURCE_DIR}/external/libpng)
  target_link_libraries(${EXECUTABLE_NAME} png_static)
endif()

load_external(libjpeg-turbo)
if(LIBJPEG-TURBO_FOUND)
  set(ENABLE_SHARED OFF CACHE BOOL "Build shared libraries")
  add_subdirectory(${PROJECT_SOURCE_DIR}/external/libjpeg-turbo)
  target_link_libraries(${EXECUTABLE_NAME} turbojpeg-static)
endif()

load_external(luajit)
if(LUAJIT_FOUND)
  add_subdirectory(${PROJECT_SOURCE_DIR}/external/luajit)
  target_link_libraries(${EXECUTABLE_NAME} liblua)
endif()

load_external(sol2)
if(SOL2_FOUND)
  add_subdirectory(${PROJECT_SOURCE_DIR}/external/sol2)
  target_link_libraries(${EXECUTABLE_NAME} sol2::sol2)
endif()

load_external(filesystem)
if(FILESYSTEM_FOUND)
  add_subdirectory(${PROJECT_SOURCE_DIR}/external/filesystem)
  target_link_libraries(${EXECUTABLE_NAME} ghc_filesystem)
endif()

load_external(variant)
if(VARIANT_FOUND)
  add_subdirectory(${PROJECT_SOURCE_DIR}/external/variant)
  target_link_libraries(${EXECUTABLE_NAME} mpark_variant)
endif()

load_external(glm)
if(GLM_FOUND)
  add_subdirectory(${PROJECT_SOURCE_DIR}/external/glm)
  target_link_libraries(${EXECUTABLE_NAME} glm::glm)
endif()

load_external(CLI11)
if(CLI11_FOUND)
  add_subdirectory(${PROJECT_SOURCE_DIR}/external/CLI11)
  target_link_libraries(${EXECUTABLE_NAME} CLI11::CLI11)
endif()

load_external(fmt)
if(FMT_FOUND)
  add_subdirectory(external/fmt)
  target_link_libraries(${EXECUTABLE_NAME} fmt::fmt)
endif()

load_external(spdlog)
if(SPDLOG_FOUND)
  add_subdirectory(external/spdlog)
  target_link_libraries(${EXECUTABLE_NAME} spdlog::spdlog)
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
  set(CPACK_GENERATOR "STGZ;TGZ;ZIP")
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
