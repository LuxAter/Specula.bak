set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})

# ##############################################################################
# SOURCE FILES
# ##############################################################################
set(SOURCES
core/geometry/bounds.cpp
core/geometry/bounds2.cpp
core/geometry/bounds3.cpp
core/geometry/bounds4.cpp
core/geometry/common.cpp
core/geometry/epsilon.cpp
core/geometry/geometric.cpp
core/geometry/integer.cpp
core/geometry/interval.cpp
core/geometry/matrix_access.cpp
core/geometry/matrix.cpp
core/geometry/noise.cpp
core/geometry/norm.cpp
core/geometry/normal.cpp
core/geometry/point.cpp
core/geometry/quaternion.cpp
core/geometry/random.cpp
core/geometry/ray_differential.cpp
core/geometry/ray.cpp
core/geometry/relational.cpp
core/geometry/trigonometry.cpp
core/geometry/vector.cpp
core/transform/transform.cpp
core/transform/animated_transform.cpp
dev/log.cpp global/math.cpp)
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
  target_link_libraries(
    specula_static PUBLIC spdlog fmt::fmt glm::glm)
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

  set_target_properties(
    specula_shared
    PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS OFF)
  target_link_libraries(
    specula_shared PUBLIC spdlog fmt::fmt glm::glm)
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