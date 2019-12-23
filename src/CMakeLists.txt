set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})

# ##############################################################################
# GPU KERNELS
# ##############################################################################
if(GPU_OPTIMIZE)
  file(GLOB OPENCL_KERNELS ${SPECULA_SOURCE_DIR}/resources/*.cl)
  add_custom_command(
    OUTPUT ${SPECULA_SOURCE_DIR}/src/kernels.hpp
    COMMAND ${SPECULA_SOURCE_DIR}/resources/compile_kernels.sh
            ${SPECULA_SOURCE_DIR}/src/kernels.hpp
            ${SPECULA_SOURCE_DIR}/resources
    DEPENDS ${OPENCL_KERNELS} ${SPECULA_SOURCE_DIR}/resources/compile_kernels.sh
    COMMENT "Generating GPU kernels")
endif()

# ##############################################################################
# SOURCE FILES
# ##############################################################################
set(SOURCES specula.cpp image.cpp stb_image_write.cpp)
if(GPU_OPTIMIZE)
  list(APPEND SOURCES ${SPECULA_SOURCE_DIR}/src/kernels.hpp)
endif()
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
    PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS OFF)
  target_link_libraries(specula_static spdlog::spdlog)
  target_link_libraries(specula_static glm::glm_static)
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
    PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS OFF)
  target_link_libraries(specula_shared spdlog::spdlog)
  target_link_libraries(specula_shared glm::glm_shared)
endif()

# ##############################################################################
# ALIASING
# ##############################################################################
if(BUILD_SHARED_LIBS)
  add_library(specula::specula ALIAS specula_shared)
elseif(BUILD_STATIC_LIBS)
  add_library(specula::specula ALIAS specula_static)
endif()
