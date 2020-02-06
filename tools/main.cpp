#include <specula/specula.hpp>

#include <iostream>

#include "gl.hpp"
#include "gui.hpp"

int main(int argc, char const *argv[]) {
  specula::logger::initialize_core_logger();
  gl::initialize();
  gui::initialize();
  while (!gl::should_close()) {
    gl::frame();
    gui::frame();
    if (gl::get_key(GLFW_KEY_ESCAPE)) {
      gl::set_should_close(true);
    }
  }
  gui::terminate();
  gl::terminate();

  return 0;
}
