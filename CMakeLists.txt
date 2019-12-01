# ##############################################################################
# PROJECT
# ##############################################################################
cmake_minimum_required(VERSION 3.8.2 FATAL_ERROR)
project(
  Specula
  VERSION 0.4.4
  LANGUAGES CXX)

# ##############################################################################
# OPTIONS
# ##############################################################################
option(ENABLE_OPENCL "Use OpenCL and GPU optimizations" TRUE)
option(ENABLE_OIDN "Enables Intel Open AI Denoise" TRUE)
# option(BUILD_SHARED_LIBS "Builed shared library" TRUE)

# ##############################################################################
# SOURCE
# ##############################################################################
set(SOURCES
    src/log.cpp
    src/image/image_class.cpp
    src/image/png.cpp
    src/image/jpeg.cpp
    src/image/bmp.cpp
    src/object/object_class.cpp
    src/scene.cpp
    src/rand.cpp
    src/renderer.cpp
    src/renderer_args.cpp)
set(EXEC_SOURCES src/main.cpp src/cli.cpp)
configure_file("${PROJECT_SOURCE_DIR}/include/version.hpp.in"
               "${PROJECT_SOURCE_DIR}/include/version.hpp")

# ##############################################################################
# BUILD TYPE
# ##############################################################################
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE
      "Debug"
      CACHE STRING "Choose the type of build" FORCE)
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

# ##############################################################################
# TARGETS
# ##############################################################################
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external)
add_library(specula_static STATIC ${SOURCES})
target_include_directories(specula_static PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(
  specula_static PUBLIC -Wall -Wextra
                        $<$<CONFIG:Debug>:-O0>$<$<CONFIG:Release>:-O3>)
target_compile_definitions(specula_static PUBLIC
                           $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:RELEASE>)
set_target_properties(
  specula_static PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES
                            CXX_EXTENSIONS TRUE)
find_package(Git REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenCL OPTIONAL)
target_link_libraries(specula_static PUBLIC ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(specula_static PUBLIC fmt::fmt)
target_link_libraries(specula_static PUBLIC spdlog::spdlog)
target_link_libraries(specula_static PUBLIC png)
target_link_libraries(specula_static PUBLIC turbojpeg-static)
target_link_libraries(specula_static PUBLIC ghc_filesystem)
target_link_libraries(specula_static PUBLIC mpark_variant)
target_link_libraries(specula_static PUBLIC glm::glm_static)

target_include_directories(specula_static
                           PRIVATE ${PROJECT_SOURCE_DIR}/external/libpng)

if(ENABLE_OPENCL AND OpenCL_FOUND)
  target_link_libraries(specula_static PUBLIC ${OpenCL_LIBRARIES})
  target_include_directories(specula_static PRIVATE ${OpenCL_INCLUDE_DIRS})
endif()

if(BUILD_SHARED_LIBS)
  add_library(specula_shared SHARED ${SOURCES})
  target_include_directories(specula_shared
                             PUBLIC ${PROJECT_SOURCE_DIR}/include)
  target_compile_options(
    specula_shared PUBLIC -Wall -Wextra
                          $<$<CONFIG:Debug>:-O0>$<$<CONFIG:Release>:-O3>)
  target_compile_definitions(
    specula_shared PUBLIC $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:RELEASE>)
  set_target_properties(
    specula_shared PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES
                              CXX_EXTENSIONS TRUE)

  target_link_libraries(specula_shared PUBLIC ${CMAKE_THREAD_LIBS_INIT})
  target_link_libraries(specula_shared PUBLIC fmt::fmt)
  target_link_libraries(specula_shared PUBLIC spdlog::spdlog)
  target_link_libraries(specula_shared PUBLIC png)
  target_link_libraries(specula_shared PUBLIC turbojpeg)
  target_link_libraries(specula_shared PUBLIC ghc_filesystem)
  target_link_libraries(specula_shared PUBLIC mpark_variant)
  target_link_libraries(specula_shared PUBLIC glm::glm_shared)

  target_include_directories(specula_shared
                             PRIVATE ${PROJECT_SOURCE_DIR}/external/libpng)
  if(ENABLE_OPENCL AND OpenCL_FOUND)
    target_link_libraries(specula_shared PUBLIC ${OpenCL_LIBRARIES})
    target_include_directories(specula_shared PRIVATE ${OpenCL_INCLUDE_DIRS})
  endif()
  add_library(specula ALIAS specula_shared)
else()
  add_library(specula ALIAS specula_static)
endif()

add_executable(main ${EXEC_SOURCES})
target_link_libraries(main specula)
target_compile_options(
  main PUBLIC -Wall -Wextra $<$<CONFIG:Debug>:-O0>$<$<CONFIG:Release>:-O3>)
target_compile_definitions(main PUBLIC
                           $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:RELEASE>)
set_target_properties(main PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES
                                      CXX_EXTENSIONS TRUE)

target_link_libraries(main luajit_static m dl)
target_link_libraries(main sol2::sol2)
target_link_libraries(main CLI11::CLI11)

target_include_directories(
  main PRIVATE ${PROJECT_BINARY_DIR}/external/luajit/include/luajit-2.0)

# ##############################################################################
# PACKAGING
# ##############################################################################

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CPACK_GENERATOR "TGZ;ZIP")
  _install(TARGETS ${LIBRARY_NAME} ARCHIVE DESTINATION lib)
  _install(TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION bin)
  set(CPACK_PACKAGE_VENDOR "LuxAter")
  set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
  set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
  set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
  set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
  set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
  set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${CMAKE_SYSTEM_NAME}")
  set(CPACK_MONOLITHIC_INSTALL TRUE)
  include(CPack)
endif()
