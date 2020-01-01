#ifndef SPECULA_GUI_HPP_
#define SPECULA_GUI_HPP_

#include <string>
#include <memory>

#include <GLFW/glfw3.h>

#include <specula/specula.hpp>

namespace gui {
void init(GLFWwindow *window);
void shutdown();
void frame();
void render();
void style(bool light, const std::string &accent);
void style_gui();
void menu_bar();

void viewer();
void material_editor();
void set_material_ptr(const std::shared_ptr<specula::Material>& mat);
} // namespace gui

#endif // SPECULA_GUI_HPP_
