#ifndef SPECULA_GUI_HPP_
#define SPECULA_GUI_HPP_

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <unordered_map>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "gl.hpp"

namespace gui {
struct Window {
  bool display_state;
  uint32_t window_flags;
  std::function<void(const std::string&)> render_callback;
};
extern std::unordered_map<std::string, Window> windows;

bool init();
void terminate();
void frame();

void render_windows();

inline void add_window(const std::string& title,
                       const std::function<void(const std::string&)>& callback) {
  windows[title] = Window{true, 0, callback};
}
} // namespace gui

#endif // SPECULA_GUI_HPP_
