#ifndef SPECULA_GUI_EDITOR_HPP_
#define SPECULA_GUI_EDITOR_HPP_

#include "window.hpp"

#include <TextEditor.h>

namespace gui {
struct EditorWindow : public Window {
public:
  EditorWindow(const std::string &file);
  virtual void render();

  void save_file();

  TextEditor editor;
  std::string file_path;
  bool focus;
};
} // namespace gui

#endif // SPECULA_GUI_EDITOR_HPP_
