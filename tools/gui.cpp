#include "gui.hpp"

#include <algorithm>
#include <map>
#include <vector>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "fonts.hpp"
#include "gl.hpp"
#include "gui/window.hpp"

static bool always_open = true;
static std::map<std::string,
                std::pair<std::map<std::string, std::function<void()>>,
                          std::vector<std::shared_ptr<gui::Window>>>>
    windows;

bool gui::initialize() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  io.Fonts->AddFontFromMemoryCompressedBase85TTF(roboto_compressed_data_base85,
                                                 20);
  io.Fonts->AddFontFromMemoryCompressedBase85TTF(
      firacode_compressed_data_base85, 20);

  ImGui_ImplGlfw_InitForOpenGL(gl::window, true);
  ImGui_ImplOpenGL3_Init("#version 410");
  return true;
}
void gui::terminate() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void gui::frame() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  render_dockspace();

  static bool demo_window = true;
  ImGui::ShowDemoWindow(&demo_window);
  for (auto &group : windows) {
    for (auto &window : group.second.second) {
      if (window == nullptr)
        continue;
      window->render();
    }
  }

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void gui::render_dockspace() {
  ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->Pos);
  ImGui::SetNextWindowSize(viewport->Size);
  ImGui::SetNextWindowViewport(viewport->ID);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

  ImGui::Begin("Specula", &always_open,
               ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking |
                   ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                   ImGuiWindowFlags_NoBringToFrontOnFocus |
                   ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground);
  ImGui::PopStyleVar(3);
  ImGuiID dockspace_id = ImGui::GetID("SpeculaDockspace");
  ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

  render_menu_bar();

  ImGui::End();
}

void gui::render_menu_bar() {
  if (ImGui::BeginMenuBar()) {
    ImGui::MenuItem("Specula");
    if (ImGui::BeginMenu("Windows")) {
      if (windows["_"].first.size() != 0) {
        for (auto &callback : windows["_"].first) {
          std::size_t split = callback.first.find(';');
          if (split != std::string::npos) {
            if (ImGui::MenuItem(callback.first.substr(0, split).c_str(),
                                callback.first.substr(split).c_str())) {
              callback.second();
            }
          } else {
            if (ImGui::MenuItem(callback.first.c_str(), NULL)) {
              callback.second();
            }
          }
        }
        if (windows.size() > 1 || windows["_"].second.size() != 0)
          ImGui::Separator();
      }
      for (auto &group : windows) {
        if (group.first == "" || group.first == "_")
          continue;
        if (ImGui::BeginMenu(group.first.c_str())) {
          for (auto &callback : group.second.first) {
            std::size_t split = callback.first.find(';');
            if (split != std::string::npos) {
              if (ImGui::MenuItem(callback.first.substr(0, split).c_str(),
                                  callback.first.substr(split).c_str())) {
                callback.second();
              }
            } else {
              if (ImGui::MenuItem(callback.first.c_str(), NULL)) {
                callback.second();
              }
            }
          }
          if (group.second.first.size() != 0 && group.second.second.size() != 0)
            ImGui::Separator();
          for (auto &win : group.second.second) {
            if (win == nullptr)
              continue;
            ImGui::MenuItem(win->title.c_str(), NULL, &win->status);
          }
          ImGui::EndMenu();
        }
      }
      if (windows.size() > 1 && windows.find("_") != windows.end() &&
          windows["_"].second.size() != 0)
        ImGui::Separator();
      for (auto &win : windows["_"].second) {
        ImGui::MenuItem(win->title.c_str(), NULL, &win->status);
      }
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }
}

void gui::register_window(const std::string &cat,
                          const std::shared_ptr<Window> &window) {
  if (std::find(windows[cat].second.begin(), windows[cat].second.end(),
                window->get_ptr()) == windows[cat].second.end()) {
    windows[cat].second.push_back(window->get_ptr());
  }
}
void gui::remove_window(const std::string &cat,
                        const std::shared_ptr<Window> &window) {
  std::vector<std::shared_ptr<Window>>::iterator it;
  if ((it = std::find(windows[cat].second.begin(), windows[cat].second.end(),
                      window->get_ptr())) != windows[cat].second.end()) {
    windows[cat].second.erase(it);
  }
}
void gui::register_window(const std::shared_ptr<Window> &window) {
  if (std::find(windows["_"].second.begin(), windows["_"].second.end(),
                window->get_ptr()) == windows["_"].second.end()) {
    windows["_"].second.push_back(window->get_ptr());
  }
}
void gui::remove_window(const std::shared_ptr<Window> &window) {
  std::vector<std::shared_ptr<Window>>::iterator it;
  if ((it = std::find(windows["_"].second.begin(), windows["_"].second.end(),
                      window->get_ptr())) != windows["_"].second.end()) {
    windows["_"].second.erase(it);
  } else {
    for (auto &group : windows) {
      if ((it = std::find(group.second.second.begin(),
                          group.second.second.end(), window->get_ptr())) !=
          group.second.second.end()) {
        group.second.second.erase(it);
        return;
      }
    }
  }
}

void gui::register_window_callback(const std::string &cat,
                                   const std::string &title,
                                   const std::function<void()> &callback) {
  windows[cat].first[title] = callback;
}
void gui::remove_window_callback(const std::string &cat,
                                 const std::string &title) {
  std::map<std::string, std::function<void()>>::iterator it;
  if ((it = windows[cat].first.find(title)) != windows[cat].first.end()) {
    windows[cat].first.erase(it);
  }
}
