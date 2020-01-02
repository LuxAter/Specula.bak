#include "gui.hpp"

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <variant>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "fonts.hpp"

static GLFWwindow *imgui_window;
static bool static_true_window = true;

static std::map<std::string, bool> windows_state;
static std::map<std::string, std::function<void()>> windows;
static std::map<std::string,
                std::map<std::string, std::variant<bool *, float *, glm::vec3 *,
                                                   std::string *>>>
    variables;

void gui::init(GLFWwindow *window) {
  imgui_window = window;
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  //   io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
  void *tmp_data = std::malloc(Roboto_Regular_ttf_size);
  memcpy(tmp_data, Roboto_Regular_ttf, Roboto_Regular_ttf_size);
  io.Fonts->AddFontFromMemoryTTF(tmp_data, Roboto_Regular_ttf_size, 20.0f);
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 410");
}

void gui::shutdown() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void gui::frame() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  for (auto &win : windows) {
    if (windows_state[win.first])
      win.second();
  }
  for (auto &win : variables) {
    if (windows_state[win.first]) {
      for (auto &var : win.second) {
        if (std::holds_alternative<bool *>(var.second))
          continue;
        else if (std::holds_alternative<float *>(var.second))
          ImGui::DragFloat(var.first.c_str(), std::get<float *>(var.second));
        else if (std::holds_alternative<glm::vec3 *>(var.second))
          ImGui::ColorEdit3(var.first.c_str(),
                            glm::value_ptr(*std::get<glm::vec3 *>(var.second)));
        else if (std::holds_alternative<std::string *>(var.second)) {
          char tmp[255];
          memcpy(tmp, std::get<std::string *>(var.second)->c_str(),
                 sizeof(char) * std::get<std::string *>(var.second)->size());
          if (ImGui::InputText(var.first.c_str(), tmp, 255)) {
            *std::get<std::string *>(var.second) = tmp;
          }
        }
      }
    }
  }
}

void gui::render() {
  ImGuiIO &io = ImGui::GetIO();
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow *backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
  }
}

void gui::create_window(const std::string &name) {
  windows_state[name] = true;
  variables[name] =
      std::map<std::string,
               std::variant<bool *, float *, glm::vec3 *, std::string *>>();
}
void gui::create_window(const std::string &name,
                        const std::function<void()> &render) {
  windows_state[name] = true;
  windows[name] = render;
}
void gui::add_variable(
    const std::string &window, const std::string &name,
    std::variant<bool *, float *, glm::vec3 *, std::string *> var) {
  variables[window][name] = var;
}