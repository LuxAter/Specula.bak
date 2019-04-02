cmake_minimum_required(VERSION 3.0)
project(Specula)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

find_package(Threads)
if (THREADS_FOUND)
  link_libraries(${CMAKE_THREADS_LIBS_INIT})
endif()
find_package(PNG)
if (PNG_FOUND)
  include_directories(${PNG_INCLUDE_DIRS})
  link_libraries(${PNG_LIBRARIES})
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/")
file(GLOB_RECURSE lib_src ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")
list(REMOVE_ITEM lib_src "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
add_library(specula ${lib_src})

add_executable(specula.exe "src/main.cpp")
target_link_libraries(specula.exe specula)
