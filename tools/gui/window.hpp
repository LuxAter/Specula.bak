#ifndef SPECULA_GUI_WINDOW_HPP_
#define SPECULA_GUI_WINDOW_HPP_

#include <functional>
#include <memory>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace gui {
struct Window : public std::enable_shared_from_this<Window> {
public:
  Window(const std::string &title, bool delete_on_close = false,
         bool status = true)
      : title(title), status(status), previous_status(status),
        delete_on_close(delete_on_close) {}
  Window(const std::string &title, const uint32_t &flags,
         bool delete_on_close = false, bool status = true)
      : title(title), status(status), previous_status(status),
        delete_on_close(delete_on_close), window_flags(flags) {}
  ~Window() {}
  std::string title;
  bool status = true;
  bool previous_status = true;
  bool delete_on_close = false;

  uint32_t window_flags = ImGuiWindowFlags_None;
  void draw();
  virtual void render();
  inline std::shared_ptr<Window> get_ptr() { return shared_from_this(); }

  virtual void open();
  virtual void close();
  virtual void deleted();

  std::function<void(std::shared_ptr<Window>)> open_callback;
  std::function<void(std::shared_ptr<Window>)> delete_callback;
  std::function<void(std::shared_ptr<Window>)> close_callback;
};

template <typename WindowType = Window, typename... Args>
inline std::shared_ptr<Window> new_window(const Args &... args) {
  return std::make_shared<WindowType>(args...);
}
} // namespace gui

#endif // SPECULA_GUI_WINDOW_HPP_
