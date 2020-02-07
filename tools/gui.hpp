#ifndef SPECULA_GUI_HPP_
#define SPECULA_GUI_HPP_

#include <imgui.h>

#include "gui/window.hpp"
#include "gui/editor.hpp"
#include "gui/file.hpp"

namespace gui {
  extern ImFont* roboto;
  extern ImFont* roboto_small;
  extern ImFont* firacode;
bool initialize();
void terminate();

void frame();
void render_dockspace();
void render_menu_bar();

void register_window(const std::string &cat, const std::shared_ptr<Window> &window);
void remove_window(const std::string &cat, const std::shared_ptr<Window> &window);
void register_window(const std::shared_ptr<Window> &window);
void remove_window(const std::shared_ptr<Window> &window);

void register_window_callback(const std::string &cat, const std::string &title,
                              const std::function<void()> &callback);
void remove_window_callback(const std::string &cat, const std::string &title);
} // namespace gui

#endif // SPECULA_GUI_HPP_
