cmake_minimum_required(VERSION 3.8.2)
project(Specula VERSION 2.0.2 LANGUAGES CXX)

set(ENABLE_WARNINGS_SETTINGS ON)
option(ENABLE_LTO "Enable link time optimization" ON)
option(ENABLE_DOCTESTS "Enable tests in library" ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
# set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
set(CMAKE_CXX_CPPCHECK "cppcheck")
# set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "iwyu-tool")
include(ConfigSafeGuards)
include(Colors)
include(CTest)
include(Doctest)
include(Documentation)
include(LTO)
include(Misc)
include(Warnings)
find_lto(CXX)
find_package(PNG REQUIRED)
find_package(Threads REQUIRED)
add_definitions(-DCOLOR_DEPTH=8 ${PNG_DEFINITIONS})

set(SOURCES
    src/specula.cpp
    src/util/log.cpp
    src/image/img.cpp
    src/image/png.cpp)

set(TESTFILES tests/main.cpp)
set(LIBRARY_NAME specula)

add_library(${LIBRARY_NAME} OBJECT ${SOURCES})

target_include_directories(${LIBRARY_NAME}
                           PUBLIC ${PROJECT_SOURCE_DIR}/include
                                  ${PNG_INCLUDE_DIRS})
target_link_libraries(${LIBRARY_NAME}
                      PUBLIC doctest ${PNG_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE ${LIBRARY_NAME})
target_enable_lto(main optimized)

set_target_properties(${LIBRARY_NAME} main
                      PROPERTIES CXX_STANDARD
                                 17
                                 CXX_STANDARD_REQUIRED
                                 YES
                                 CXX_EXTENSIONS
                                 NO)

string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_DEFINE)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -D${CMAKE_BUILD_TYPE_DEFINE})
add_subdirectory(tests)
