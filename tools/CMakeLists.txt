set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SPECULA_BINARY_DIR})

# ##############################################################################
# SOURCE FILES
# ##############################################################################
set(SOURCES
    main.cpp
    gl.cpp
    gui.cpp
    gui/window.cpp
    gui/editor.cpp
    gui/file.cpp
    glad/glad.c)
list(
  APPEND SOURCES
         ${SPECULA_SOURCE_DIR}/external/imgui/imgui_demo.cpp
         ${SPECULA_SOURCE_DIR}/external/imgui/imgui_widgets.cpp
         ${SPECULA_SOURCE_DIR}/external/imgui/imgui_draw.cpp
         ${SPECULA_SOURCE_DIR}/external/imgui/imgui.cpp
         ${SPECULA_SOURCE_DIR}/external/imgui/examples/imgui_impl_glfw.cpp
         ${SPECULA_SOURCE_DIR}/external/imgui/examples/imgui_impl_opengl3.cpp)
list(APPEND SOURCES
            ${SPECULA_SOURCE_DIR}/external/ImGuiColorTextEdit/TextEditor.cpp
            ${SPECULA_SOURCE_DIR}/external/ImGuiFileDialog/ImGuiFileDialog.cpp)
add_custom_command(
  OUTPUT ${SPECULA_SOURCE_DIR}/tools/fonts.hpp
  COMMAND ${SPECULA_BINARY_DIR}/scripts/binary_to_compressed -base85
          ${SPECULA_SOURCE_DIR}/resources/Roboto-Regular.ttf roboto >>
          ${SPECULA_SOURCE_DIR}/tools/fonts.hpp
  COMMAND ${SPECULA_BINARY_DIR}/scripts/binary_to_compressed -base85
          ${SPECULA_SOURCE_DIR}/resources/FiraCode-Regular.ttf firacode >>
          ${SPECULA_SOURCE_DIR}/tools/fonts.hpp)
list(APPEND SOURCES ${SPECULA_SOURCE_DIR}/tools/fonts.hpp)

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
target_include_directories(
  specula PUBLIC ${SPECULA_SOURCE_DIR}/external/ImGuiColorTextEdit
                 ${SPECULA_SOURCE_DIR}/external/ImGuiFileDialog)
target_link_libraries(specula specula::specula glfw ${CMAKE_DL_LIBS})
target_compile_definitions(specula PUBLIC -DIMGUI_IMPL_OPENGL_LOADER_GLAD)

if(UNIX)
  if(APPLE)
    target_compile_definitions(specula PUBLIC -DAPPLE)
  else()
    target_compile_definitions(specula PUBLIC -DLINUX)
  endif()
  target_compile_definitions(specula PUBLIC -DUNIX)
elseif(WIN32)
  target_compile_definitions(specula PUBLIC -DWIN32)
  target_compile_definitions(specula PUBLIC -DMINGW32)
  set(DIRENT_INCLUDE_DIR ${SPECULA_SOURCE_DIR}/external/dirent)
  target_include_directories(${DIRENT_INCLUDE_DIR})
endif()

install(TARGETS specula RUNTIME DESTINATION bin)
