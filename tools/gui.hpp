#ifndef SPECULA_GUI_HPP_
#define SPECULA_GUI_HPP_

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <variant>

#include <GLFW/glfw3.h>

#include <specula/specula.hpp>

namespace gui {

void init(GLFWwindow *window);
void shutdown();
void frame();
void render();

void create_window(const std::string &name);
void create_window(const std::string &name,
                   const std::function<void()> &render);
void add_variable(
    const std::string &window, const std::string &name,
    std::variant<bool *, float *, glm::vec3 *, std::string *> var);
} // namespace gui

#endif // SPECULA_GUI_HPP_
