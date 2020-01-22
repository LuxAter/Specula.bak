set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})

# ##############################################################################
# SOURCE FILES
# ##############################################################################
set(SOURCES
    specula.cpp
    log.cpp
    math/matrix/matrix4x4.cpp
    math/vector/vector2.cpp
    math/vector/vector3.cpp
    math/vector/vector4.cpp
    math/vector/vectorn.cpp)
configure_file("${SPECULA_SOURCE_DIR}/include/specula/version.hpp.in"
               "${SPECULA_SOURCE_DIR}/include/specula/version.hpp")

# ##############################################################################
# STATIC TARGET
# ##############################################################################
if(BUILD_STATIC_LIBS)
  add_library(specula_static STATIC ${SOURCES})
  add_library(specula::static ALIAS specula_static)
  target_include_directories(specula_static
                             PUBLIC ${SPECULA_SOURCE_DIR}/include)

  set_target_properties(
    specula_static
    PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS OFF)
  target_link_libraries(specula_static PUBLIC spdlog fmt::fmt)
  install(TARGETS specula_static ARCHIVE DESTINATION lib)
endif()

# ##############################################################################
# SHARED TARGET
# ##############################################################################
if(BUILD_SHARED_LIBS)
  add_library(specula_shared SHARED ${SOURCES})
  add_library(specula::shared ALIAS specula_shared)
  target_include_directories(specula_shared
                             PUBLIC ${SPECULA_SOURCE_DIR}/include)

  set_target_properties(
    specula_shared
    PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS OFF)
  target_link_libraries(specula_shared PUBLIC spdlog fmt::fmt)
  install(TARGETS specula_shared LIBRARY DESTINATION lib)
endif()

# ##############################################################################
# ALIASING
# ##############################################################################
if(BUILD_SHARED_LIBS)
  add_library(specula::specula ALIAS specula_shared)
elseif(BUILD_STATIC_LIBS)
  add_library(specula::specula ALIAS specula_static)
endif()
