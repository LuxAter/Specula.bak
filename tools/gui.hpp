#ifndef SPECULA_GUI_HPP_
#define SPECULA_GUI_HPP_

#include <string>

#include <GLFW/glfw3.h>

namespace gui {
void init(GLFWwindow *window);
void shutdown();
void frame();
void render();
void style(bool light, const std::string &accent);
void style_gui();
} // namespace gui

#endif // SPECULA_GUI_HPP_