#include <specula/specula.hpp>

#include <iostream>

#include "gl.hpp"
#include "gui.hpp"

int main(int argc, char const *argv[]) {
  std::size_t editor_count = 0;
  specula::logger::initialize_core_logger();
  gl::initialize();
  gui::initialize();
  auto viewport = gui::new_window("Viewport");
  gui::register_window(viewport);
  gui::register_window_callback("Editor", "Open", [editor_count]() mutable {
    gui::register_window("Editor",
                         gui::new_window<gui::FileDialogWindow>(".c;.cpp"));
    editor_count++;
  });
  while (!gl::should_close()) {
    gl::frame();
    gui::frame();
  }
  gui::terminate();
  gl::terminate();

  return 0;
}
