#include "editor.hpp"
#include "window.hpp"

#include <TextEditor.h>

#include <fstream>
#include <specula/specula.hpp>

#include "../gl.hpp"
#include "../gui.hpp"

gui::EditorWindow::EditorWindow(const std::string &file)
    : Window(file.substr(file.rfind('/') + 1),
             static_cast<uint32_t>(ImGuiWindowFlags_MenuBar |
                                   ImGuiWindowFlags_HorizontalScrollbar)),
      file_path(file), focus(false) {
  editor.SetLanguageDefinition(TextEditor::LanguageDefinition::CPlusPlus());

  std::ifstream load_stream(file_path);
  if (load_stream.is_open()) {
    std::string str((std::istreambuf_iterator<char>(load_stream)),
                    std::istreambuf_iterator<char>());
    editor.SetText(str);
    load_stream.close();
  }
}

void gui::EditorWindow::render() {
  auto cpos = editor.GetCursorPosition();
  bool ro = editor.IsReadOnly();
  ImGui::Begin(this->title.c_str(), &this->status, this->window_flags);
  ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
  if (ImGui::IsWindowFocused() != focus) {
    focus = ImGui::IsWindowFocused();
    LCINFO("GUI", "Editor focus changed");
    if (!focus)
      save_file();
  }
  if (gl::get_key(GLFW_KEY_LEFT_CONTROL) ||
      gl::get_key(GLFW_KEY_RIGHT_CONTROL)) {
    if (gl::get_key(GLFW_KEY_S))
      save_file();
  }
  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Save", "Ctrl+S")) {
        save_file();
      }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Edit")) {
      if (ImGui::MenuItem("Read-only mode", nullptr, &ro))
        editor.SetReadOnly(ro);
      ImGui::Separator();

      if (ImGui::MenuItem("Undo", "Ctrl-Z", nullptr, !ro && editor.CanUndo()))
        editor.Undo();
      if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && editor.CanRedo()))
        editor.Redo();

      ImGui::Separator();

      if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, editor.HasSelection()))
        editor.Copy();
      if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr,
                          !ro && editor.HasSelection()))
        editor.Cut();
      if (ImGui::MenuItem("Delete", "Del", nullptr,
                          !ro && editor.HasSelection()))
        editor.Delete();
      if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr,
                          !ro && ImGui::GetClipboardText() != nullptr))
        editor.Paste();

      ImGui::Separator();

      if (ImGui::MenuItem("Select all", nullptr, nullptr))
        editor.SetSelection(TextEditor::Coordinates(),
                            TextEditor::Coordinates(editor.GetTotalLines(), 0));

      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("View")) {
      if (ImGui::MenuItem("Dark palette"))
        editor.SetPalette(TextEditor::GetDarkPalette());
      if (ImGui::MenuItem("Light palette"))
        editor.SetPalette(TextEditor::GetLightPalette());
      if (ImGui::MenuItem("Retro blue palette"))
        editor.SetPalette(TextEditor::GetRetroBluePalette());
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }

  ImGui::PushFont(gui::firacode);
  ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1,
              cpos.mColumn + 1, editor.GetTotalLines(),
              editor.IsOverwrite() ? "Ovr" : "Ins",
              editor.CanUndo() ? "*" : " ",
              editor.GetLanguageDefinition().mName.c_str(), file_path.c_str());

  editor.Render("TextEditor");
  ImGui::PopFont();
  ImGui::End();
}

void gui::EditorWindow::save_file() {
  auto text_to_save = editor.GetText();
  FILE *out = std::fopen(file_path.c_str(), "w");
  if (out != nullptr) {
    std::fprintf(out, "%s", text_to_save.c_str());
    std::fclose(out);
  } else {
    LCERROR("Failed to open file \"{}\" for writting", file_path);
  }
}
