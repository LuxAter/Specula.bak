set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})

# ##############################################################################
# SOURCE FILES
# ##############################################################################
set(SOURCES main.cpp gl.cpp gui.cpp glad/glad.c)
list(
  APPEND SOURCES
         ${SPECULA_SOURCE_DIR}/external/imgui/imgui_demo.cpp
         ${SPECULA_SOURCE_DIR}/external/imgui/imgui_widgets.cpp
         ${SPECULA_SOURCE_DIR}/external/imgui/imgui_draw.cpp
         ${SPECULA_SOURCE_DIR}/external/imgui/imgui.cpp
         ${SPECULA_SOURCE_DIR}/external/imgui/examples/imgui_impl_glfw.cpp
         ${SPECULA_SOURCE_DIR}/external/imgui/examples/imgui_impl_opengl3.cpp)

# ##############################################################################
# TARGET
# ##############################################################################
add_executable(specula ${SOURCES})
target_include_directories(specula PUBLIC ${SPECULA_SOURCE_DIR}/tools)
set_target_properties(specula PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED
                                                         YES CXX_EXTENSIONS OFF)
target_include_directories(
  specula PUBLIC ${SPECULA_SOURCE_DIR}/external/imgui
                 ${SPECULA_SOURCE_DIR}/external/imgui/examples)
target_link_libraries(specula specula::specula glfw ${CMAKE_DL_LIBS})
target_compile_definitions(specula PUBLIC -DIMGUI_IMPL_OPENGL_LOADER_GLAD)
install(TARGETS specula RUNTIME DESTINATION bin)
