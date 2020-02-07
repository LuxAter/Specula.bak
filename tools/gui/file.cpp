#include "file.hpp"

#include <sstream>

#include <ImGuiFileDialog.h>
#include <specula/specula.hpp>

#include "editor.hpp"
#include "window.hpp"

#include "../gui.hpp"
void gui::register_window(const std::string &cat,
                          const std::shared_ptr<Window> &win);
void gui::remove_window(const std::shared_ptr<Window> &win);

std::string ptr_to_str(void *ptr) {
  std::stringstream ss;
  ss << ptr;
  return ss.str();
}

gui::FileDialogWindow::FileDialogWindow(const std::string &extensions,
                                        const std::string &file_path)
    : Window(ptr_to_str((void *)this)) {
  char *buff = (char *)std::malloc(sizeof(char) * extensions.size() + 1);
  for (std::size_t i = 0; i < extensions.size(); ++i) {
    if (extensions[i] == ';')
      buff[i] = '\0';
    else
      buff[i] = extensions[i];
  }
  buff[extensions.size()] = '\0';
  ImGuiFileDialog::Instance()->OpenDialog(ptr_to_str((void *)this),
                                          "Choose File", buff, file_path);
}

void gui::FileDialogWindow::render() {
  ImGui::PushFont(gui::roboto_small);
  if (ImGuiFileDialog::Instance()->FileDialog(ptr_to_str((void *)this))) {
    ImGui::SetNextWindowSize(ImVec2(300, 300));
    if (ImGuiFileDialog::Instance()->IsOk == true) {
      std::string file_path_name =
          ImGuiFileDialog::Instance()->GetFilepathName();
      std::string file_path = ImGuiFileDialog::Instance()->GetCurrentPath();
      gui::register_window("Editor",
                           gui::new_window<EditorWindow>(file_path_name));
    }
    ImGuiFileDialog::Instance()->CloseDialog(ptr_to_str((void *)this));
    gui::remove_window(shared_from_this());
  }
  ImGui::PopFont();
}
