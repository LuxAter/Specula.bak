set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})

# ##############################################################################
# SOURCE FILES
# ##############################################################################
set(SOURCES
    core/geometry/bounds.cpp
    core/geometry/normal.cpp
    core/geometry/point.cpp
    core/geometry/ray.cpp
    core/geometry/vector.cpp
    core/geometry/common.cpp
    core/geometry/matrix.cpp
    core/transform.cpp
    core/interaction.cpp
    dev/log.cpp)
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
  target_include_directories(specula_static
                             PRIVATE ${SPECULA_SOURCE_DIR}/include/specula)

  set_target_properties(
    specula_static
    PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS OFF)
  target_link_libraries(specula_static PUBLIC spdlog fmt::fmt glm::glm)
  target_include_directories(specula_static PUBLIC ${SPECULA_GPU_INCLUDE_DIRS})
  target_link_libraries(specula_static PUBLIC ${SPECULA_GPU_LIBRARIES})
  target_compile_definitions(specula_static PUBLIC ${SPECULA_GPU_FLAGS})
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
  target_include_directories(specula_shared
                             PRIVATE ${SPECULA_SOURCE_DIR}/include/specula)

  set_target_properties(
    specula_shared
    PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS OFF)
  target_link_libraries(specula_shared PUBLIC spdlog fmt::fmt glm::glm)
  target_include_directories(specula_shared PUBLIC ${SPECULA_GPU_INCLUDE_DIRS})
  target_link_libraries(specula_shared PUBLIC ${SPECULA_GPU_LIBRARIES})
  target_compile_options(specula_shared PUBLIC ${SPECULA_GPU_FLAGS})
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
