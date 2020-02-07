#include "window.hpp"

#include <functional>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "../gui.hpp"
void gui::remove_window(const std::shared_ptr<Window> &win);

void gui::Window::draw() {
  if (status != previous_status) {
    if (status)
      open();
    else
      close();
    previous_status = status;
  }
  if (status == true) {
    render();
  }
}
void gui::Window::render() {
  ImGui::Begin(title.c_str(), &status, window_flags);
  ImGui::End();
}
void gui::Window::open() {
  if (open_callback)
    open_callback(shared_from_this());
}
void gui::Window::close() {
  if (delete_on_close) {
    gui::remove_window(shared_from_this());
    deleted();
  } else if (close_callback)
    close_callback(shared_from_this());
}
void gui::Window::deleted() {
  if (delete_callback)
    delete_callback(shared_from_this());
}
