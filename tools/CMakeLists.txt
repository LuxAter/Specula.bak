set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})

# ##############################################################################
# SOURCE FILES
# ##############################################################################
file(GLOB FONT_FILES ${SPECULA_SOURCE_DIR}/resources/*.ttf)
add_custom_command(
  OUTPUT ${SPECULA_SOURCE_DIR}/tools/fonts.hpp
  COMMAND ${SPECULA_SOURCE_DIR}/resources/compile_resource.sh
          ${SPECULA_SOURCE_DIR}/tools/fonts.hpp ${SPECULA_SOURCE_DIR}/resources
          ttf
  DEPENDS ${FONT_FILES} ${SPECULA_SOURCE_DIR}/resources/compile_resource.sh
  COMMENT "Compiling fonts")
set(SOURCES main.cpp)
# list(APPEND SOURCES ${SPECULA_SOURCE_DIR}/tools/fonts.hpp) list( APPEND
# SOURCES ${SPECULA_SOURCE_DIR}/external/imgui-
# cmake/examples/imgui_impl_glfw.cpp ${SPECULA_SOURCE_DIR}/external/imgui-
# cmake/examples/imgui_impl_opengl3.cpp)

# ##############################################################################
# TARGET
# ##############################################################################
add_executable(specula ${SOURCES})
target_include_directories(specula PUBLIC ${SPECULA_SOURCE_DIR}/tools)
target_include_directories(
  specula PUBLIC ${SPECULA_SOURCE_DIR}/external/imgui-cmake/examples)

set_target_properties(specula PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED
                                                         YES CXX_EXTENSIONS OFF)
target_link_libraries(specula specula::specula)
# target_link_libraries(specula glfw glad imgui)
