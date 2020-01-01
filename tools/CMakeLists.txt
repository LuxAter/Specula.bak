set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})

# ##############################################################################
# SOURCE FILES
# ##############################################################################
set(SOURCES main.cpp gui.cpp)
list(
  APPEND
    SOURCES
    ${SPECULA_SOURCE_DIR}/external/imgui-cmake/examples/imgui_impl_glfw.cpp
    ${SPECULA_SOURCE_DIR}/external/imgui-cmake/examples/imgui_impl_opengl3.cpp)

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
target_link_libraries(specula glfw glad imgui)
