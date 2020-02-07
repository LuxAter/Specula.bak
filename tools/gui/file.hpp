#ifndef SPECULA_GUI_FILE_HPP_
#define SPECULA_GUI_FILE_HPP_

#include "window.hpp"

#include <TextEditor.h>

namespace gui {
struct FileDialogWindow : public Window {
public:
  FileDialogWindow(const std::string &extensions,
                   const std::string &file_path = ".");
  virtual void render();
};
} // namespace gui

#endif // SPECULA_GUI_FILE_HPP_
