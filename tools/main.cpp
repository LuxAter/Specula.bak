#include <specula/specula.hpp>

#include "argparse.hpp"
#include "gl.hpp"
#include "gui.hpp"

int main(int argc, char* argv[]) {
  specula::initialize();
  args::parse_args(argc, argv);

  gl::init();
  gui::init();

  specula::Image img = specula::render();

  GLuint image_texture;
  glGenTextures(1, &image_texture);
  glBindTexture(GL_TEXTURE_2D, image_texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.width, img.height, 0, GL_RGB,
               GL_FLOAT, img.get_ptr());

  gui::add_window("Viewport", [image_texture, img](const std::string& name) {
      ImGui::Image((void*)(intptr_t)image_texture, ImVec2(img.width, img.height));
  });

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
