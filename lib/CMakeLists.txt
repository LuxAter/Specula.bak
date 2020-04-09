# ##############################################################################
# SOURCE FILES
# ##############################################################################
string(TIMESTAMP YYYYMMDD "%Y-%m-%d")
set(SOURCES src/core/geometry/ray.cpp src/core/geometry/point.cpp
  src/core/geometry/bounds.cpp src/core/geometry/common.cpp
  src/core/geometry/matrix.cpp src/core/geometry/normal.cpp
  src/core/geometry/vector.cpp src/core/spectrum/coefficient.cpp
  src/core/spectrum/common.cpp src/core/spectrum/rgb.cpp
  src/core/spectrum/sampled.cpp src/core/transform/transform.cpp
  src/core/film.cpp src/core/imageio.cpp
  src/core/efloat.cpp src/core/filter.cpp src/core/memory.cpp
  src/core/parallel.cpp src/core/sampling.cpp src/dev/log.cpp src/dev/prof.cpp)
configure_file("${SPECULA_SOURCE_DIR}/lib/include/specula/version.hpp.in"
  "${SPECULA_SOURCE_DIR}/lib/include/specula/version.hpp")

# ##############################################################################
# STATIC LIBRARY
# ##############################################################################
if(SPECULA_BUILD_STATIC_LIBS)
  add_library(specula-static STATIC ${SOURCES})
  add_library(specula::static ALIAS specula-static)

  target_include_directories(specula-static PUBLIC ${SPECULA_SOURCE_DIR}/lib/include)
  target_include_directories(specula-static PRIVATE ${SPECULA_SOURCE_DIR}/lib/include/specula)

  set_target_properties(specula-static PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS OFF)
  set_target_properties(specula-static PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_CMD}" CXX_CPPCHECK "${CPPCHECK_CMD}")

  target_link_libraries(specula-static PUBLIC spdlog fmt::fmt stb::stb IlmImf Imath Half)
  install(TARGETS specula-static ARCHIVE DESTINATION lib)
endif()

# ##############################################################################
# SHARED LIBRARY
# ##############################################################################
if(SPECULA_BUILD_SHARED_LIBS)
  add_library(specula-shared SHARED ${SOURCES})
  add_library(specula::shared ALIAS specula-shared)

  target_include_directories(specula-shared PUBLIC ${SPECULA_SOURCE_DIR}/lib/include)
  target_include_directories(specula-shared PRIVATE ${SPECULA_SOURCE_DIR}/lib/include/specula)

  set_target_properties(specula-shared PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS OFF)
  set_target_properties(specula-shared PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_CMD}" CXX_CPPCHECK "${CPPCHECK_CMD}")

  target_link_libraries(specula-shared PUBLIC spdlog fmt::fmt stb::stb IlmImf Imath Half)
  install(TARGETS specula-shared LIBRARY DESTINATION lib)
endif()

# ##############################################################################
# ALIASED LIBRARY
# ##############################################################################
if(SPECULA_BUILD_SHARED_LIBS)
  add_library(specula::specula ALIAS specula-shared)
elseif(SPECULA_BUILD_STATIC_LIBS)
  add_library(specula::specula ALIAS specula-static)
endif()

