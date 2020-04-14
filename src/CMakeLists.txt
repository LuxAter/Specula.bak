# ##############################################################################
# DEPENDENCIES
# ##############################################################################
add_library(specula-dependencies INTERFACE)
target_link_libraries(
  specula-dependencies
  INTERFACE spdlog
         fmt::fmt
         stb::stb
         IlmImf
         Imath
         Half
         ghc_filesystem)

# ##############################################################################
# SOURCE FILES
# ##############################################################################
include(WriteCompilerDetectionHeader)
string(TIMESTAMP YYYYMMDD "%Y-%m-%d")
set(SOURCES
    core/geometry/ray.cpp
    core/geometry/point.cpp
    core/geometry/bounds.cpp
    core/geometry/common.cpp
    core/geometry/matrix.cpp
    core/geometry/normal.cpp
    core/geometry/vector.cpp
    core/spectrum/coefficient.cpp
    core/spectrum/common.cpp
    core/spectrum/rgb.cpp
    core/spectrum/sampled.cpp
    core/transform/transform.cpp
    core/transform/animated_transform.cpp
    core/quaternion.cpp
    core/interaction.cpp
    core/rng.cpp
    core/sampler.cpp
    core/medium.cpp
    core/film.cpp
    core/imageio.cpp
    core/efloat.cpp
    core/filter.cpp
    core/memory.cpp
    core/parallel.cpp
    core/sampling.cpp
    dev/log.cpp
    dev/prof.cpp)
configure_file("${SPECULA_SOURCE_DIR}/include/specula/version.hpp.in"
               "${SPECULA_SOURCE_DIR}/include/specula/version.hpp")
set(SPECULA_COMPILERS MSVC GNU Clang Intel AppleClang)
write_compiler_detection_header(
  FILE
  ${SPECULA_SOURCE_DIR}/include/specula/global/compiler.hpp
  PREFIX
  SPECULA
  COMPILERS
  ${SPECULA_COMPILERS}
  FEATURES
  cxx_constexpr
  cxx_deleted_functions
  cxx_extern_templates
  cxx_final
  cxx_noexcept
  cxx_override
  cxx_alignas
  cxx_alignof
  cxx_nullptr
  cxx_static_assert
  cxx_attribute_deprecated
  cxx_thread_local)

# ##############################################################################
# STATIC LIBRARY
# ##############################################################################
if(SPECULA_BUILD_STATIC_LIBS)
  add_library(specula-static STATIC ${SOURCES})
  add_library(specula::static ALIAS specula-static)

  target_include_directories(specula-static
                             PUBLIC ${SPECULA_SOURCE_DIR}/include)
  target_include_directories(specula-static
                             PRIVATE ${SPECULA_SOURCE_DIR}/include/specula)
  set_target_properties(
    specula-static PROPERTIES CXX_CLANG_TIDY "${CLANGTIDY_CMD}"
                              CXX_CPPCHECK "${CPPCHECK_CMD}")

  target_link_libraries(
    specula-static
    PUBLIC specula-dependencies specula-options specula-warnings)
  install(TARGETS specula-static ARCHIVE DESTINATION lib)
endif()

# ##############################################################################
# SHARED LIBRARY
# ##############################################################################
if(SPECULA_BUILD_SHARED_LIBS)
  add_library(specula-shared SHARED ${SOURCES})
  add_library(specula::shared ALIAS specula-shared)

  target_include_directories(specula-shared
                             PUBLIC ${SPECULA_SOURCE_DIR}/include)
  target_include_directories(specula-shared
                             PRIVATE ${SPECULA_SOURCE_DIR}/include/specula)

  set_target_properties(
    specula-shared PROPERTIES CXX_CLANG_TIDY "${CLANGTIDY_CMD}"
                              CXX_CPPCHECK "${CPPCHECK_CMD}")

  target_link_libraries(
    specula-shared
    PUBLIC specula-dependencies specula-options specula-warnings)
  install(TARGETS specula-shared LIBRARY DESTINATION lib)
endif()

# ##############################################################################
# ALIASED LIBRARY
# ##############################################################################
if(SPECULA_BUILD_SHARED_LIBS)
  add_library(specula::specula ALIAS specula-shared)
else()
  add_library(specula::specula ALIAS specula-static)
endif()
