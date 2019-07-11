cmake_minimum_required(VERSION 3.8.2)
project(Specula VERSION 2.0.1 LANGUAGES CXX)

set(ENABLE_WARNINGS_SETTINGS ON)
option(ENABLE_LTO "Enable link time optimization" ON)
option(ENABLE_DOCTESTS "Enable tests in library" ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
set(CMAKE_CXX_CPPCHECK "cppcheck")
set(CMAKE_CXX_CPPLINT "cpplint")
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "iwyu-tool")
include(ConfigSafeGuards)
include(Colors)
include(CTest)
include(Doctest)
include(Documentation)
include(LTO)
include(Misc)
include(Warnings)
find_lto(CXX)

set(SOURCES src/specula.cpp)

set(TESTFILES tests/main.cpp)
set(LIBRARY_NAME specula)

add_library(${LIBRARY_NAME} OBJECT ${SOURCES})

target_include_directories(${LIBRARY_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${LIBRARY_NAME} PUBLIC doctest)

target_set_warnings(${LIBRARY_NAME}
                    ENABLE
                    ALL
                    AS_ERROR
                    ALL
                    DISABLE
                    Annoying)
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE ${LIBRARY_NAME})
target_set_warnings(main
                    ENABLE
                    ALL
                    AS_ERROR
                    ALL
                    DISABLE
                    Annoying)
target_enable_lto(main optimized)

set_target_properties(${LIBRARY_NAME} main
                      PROPERTIES CXX_STANDARD
                                 17
                                 CXX_STANDARD_REQUIRED
                                 YES
                                 CXX_EXTENSIONS
                                 NO)

add_subdirectory(tests)
