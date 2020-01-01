#include "gui.hpp"

#include <filesystem>
#include <map>
#include <memory>
#include <string>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>

#include <specula/specula.hpp>

#include "colors.hpp"
#include "fonts.hpp"
#include "imgui_ser.hpp"
#include "specula/material.hpp"

static std::map<std::string, bool> windows;
static GLFWwindow *imgui_window;
static bool dockspace_open = false;
static bool static_true_window = true;

static std::shared_ptr<specula::Material> mat;

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
  windows["viewer"] = true;
  windows["material editor"] = true;
  if (std::filesystem::exists("imgui_style.ini")) {
    ImGuiLoadStyle("imgui_style.ini", ImGui::GetStyle());
  } else {
    style(false, "Blue");
  }
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

  ImGuiDockNodeFlags dockspace_flags =
      ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_AutoHideTabBar;
  ImGuiWindowFlags window_flags =
      ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking |
      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
      ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
      ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
  ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->Pos);
  ImGui::SetNextWindowSize(viewport->Size);
  ImGui::SetNextWindowViewport(viewport->ID);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::Begin("Specula Editor", &static_true_window, window_flags);
  ImGui::PopStyleVar(3);
  ImGuiID dockspace = ImGui::GetID("Specula Dockspace");
  ImGui::DockSpace(dockspace, ImVec2(0.0f, 0.0f), dockspace_flags);
  if (!dockspace_open) {
    ImGuiID dock_main = dockspace;
    ImGuiID dock_left = ImGui::DockBuilderSplitNode(dock_main, ImGuiDir_Left,
                                                    0.20f, NULL, &dock_main);
    ImGuiID dock_right = ImGui::DockBuilderSplitNode(dock_main, ImGuiDir_Right,
                                                     0.20f, NULL, &dock_main);
    ImGui::DockBuilderDockWindow("Material Editor", dock_right);
    ImGui::DockBuilderDockWindow("Viewer", dock_main);
    ImGui::DockBuilderFinish(dockspace);
    dockspace_open = true;
  }

  menu_bar();
  ImGui::End();

  viewer();
  material_editor();
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

void gui::style(bool light, const std::string &accent) {
  ImGuiStyle &style = ImGui::GetStyle();

  ImVec4 col_text, col_back, col_area, col_main;
  if (light) {
    col_text = isotope["grey10"];
    col_back = isotope["grey1"];
  } else {
    col_text = isotope["grey1"];
    col_back = isotope["grey10"];
  }
  col_main = isotope[accent];
  col_area = light ? isotope["light_" + accent] : isotope["dark_" + accent];

  style.Colors[ImGuiCol_Text] =
      ImVec4(col_text.x, col_text.y, col_text.z, 1.00f);
  style.Colors[ImGuiCol_TextDisabled] =
      ImVec4(col_text.x, col_text.y, col_text.z, 0.58f);
  style.Colors[ImGuiCol_WindowBg] =
      ImVec4(col_back.x, col_back.y, col_back.z, 1.00f);
  style.Colors[ImGuiCol_ChildBg] =
      ImVec4(col_back.x, col_back.y, col_back.z, 0.00f);
  style.Colors[ImGuiCol_PopupBg] =
      ImVec4(col_back.x, col_back.y, col_back.z, 0.85f);
  style.Colors[ImGuiCol_Border] =
      ImVec4(col_text.x, col_text.y, col_text.z, 0.30f);
  style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  style.Colors[ImGuiCol_FrameBg] =
      ImVec4(col_area.x, col_area.y, col_area.z, 1.00f);
  style.Colors[ImGuiCol_FrameBgHovered] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.68f);
  style.Colors[ImGuiCol_FrameBgActive] =
      ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);

  style.Colors[ImGuiCol_Tab] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.44f);
  style.Colors[ImGuiCol_TabHovered] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.86f);
  style.Colors[ImGuiCol_TabActive] =
      ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
  style.Colors[ImGuiCol_TabUnfocused] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.24f);
  style.Colors[ImGuiCol_TabUnfocusedActive] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.80f);

  style.Colors[ImGuiCol_TitleBg] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.45f);
  style.Colors[ImGuiCol_TitleBgCollapsed] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.35f);
  style.Colors[ImGuiCol_TitleBgActive] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
  style.Colors[ImGuiCol_MenuBarBg] =
      ImVec4(col_area.x, col_area.y, col_area.z, 0.57f);
  style.Colors[ImGuiCol_ScrollbarBg] =
      ImVec4(col_area.x, col_area.y, col_area.z, 1.00f);
  style.Colors[ImGuiCol_ScrollbarGrab] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.31f);
  style.Colors[ImGuiCol_ScrollbarGrabHovered] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
  style.Colors[ImGuiCol_ScrollbarGrabActive] =
      ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
  style.Colors[ImGuiCol_CheckMark] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.80f);
  style.Colors[ImGuiCol_SliderGrab] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.24f);
  style.Colors[ImGuiCol_SliderGrabActive] =
      ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
  style.Colors[ImGuiCol_Button] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.44f);
  style.Colors[ImGuiCol_ButtonHovered] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.86f);
  style.Colors[ImGuiCol_ButtonActive] =
      ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
  style.Colors[ImGuiCol_Header] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.76f);
  style.Colors[ImGuiCol_HeaderHovered] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.86f);
  style.Colors[ImGuiCol_HeaderActive] =
      ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
  style.Colors[ImGuiCol_ResizeGrip] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.20f);
  style.Colors[ImGuiCol_ResizeGripHovered] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
  style.Colors[ImGuiCol_ResizeGripActive] =
      ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
  style.Colors[ImGuiCol_PlotLines] =
      ImVec4(col_text.x, col_text.y, col_text.z, 0.63f);
  style.Colors[ImGuiCol_PlotLinesHovered] =
      ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
  style.Colors[ImGuiCol_PlotHistogram] =
      ImVec4(col_text.x, col_text.y, col_text.z, 0.63f);
  style.Colors[ImGuiCol_PlotHistogramHovered] =
      ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
  style.Colors[ImGuiCol_TextSelectedBg] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.43f);
  style.Colors[ImGuiCol_ModalWindowDarkening] =
      ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
  style.Colors[ImGuiCol_DockingPreview] =
      ImVec4(col_area.x, col_area.y, col_area.z, 0.65f);
  style.Colors[ImGuiCol_DockingEmptyBg] =
      ImVec4(col_back.x, col_back.y, col_back.z, 1.00f);
  style.Colors[ImGuiCol_DragDropTarget] =
      ImVec4(col_area.x, col_area.y, col_area.z, 0.65f);

  style.PopupRounding = 3;

  style.WindowPadding = ImVec2(4, 4);
  style.FramePadding = ImVec2(6, 4);
  style.ItemSpacing = ImVec2(6, 2);

  style.ScrollbarSize = 18;

  style.WindowBorderSize = 1;
  style.ChildBorderSize = 1;
  style.PopupBorderSize = 1;
  style.FrameBorderSize = 0;

  style.WindowRounding = 3;
  style.ChildRounding = 3;
  style.FrameRounding = 3;
  style.ScrollbarRounding = 2;
  style.GrabRounding = 3;

  style.TabBorderSize = 0;
  style.TabRounding = 3;

  if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }
  ImGuiSaveStyle("imgui_style.ini", ImGui::GetStyle());
}

void gui::style_gui() {
  static bool style_light = false;
  static std::string accent = "Blue";
  if (ImGui::BeginCombo("Theme", style_light ? "Light" : "Dark")) {
    if (ImGui::Selectable("Dark", !style_light)) {
      style_light = false;
      gui::style(style_light, accent);
    }
    if (!style_light)
      ImGui::SetItemDefaultFocus();
    if (ImGui::Selectable("Light", style_light)) {
      style_light = true;
      gui::style(style_light, accent);
    }
    if (style_light)
      ImGui::SetItemDefaultFocus();
    ImGui::EndCombo();
  }
  if (ImGui::BeginCombo("Color", accent.c_str())) {
    for (std::size_t i = 0; i < 17; ++i) {
      bool is_selected = (accent == colors[i]);
      if (ImGui::Selectable(colors[i].c_str(), is_selected)) {
        accent = colors[i];
        gui::style(style_light, accent);
      }
      if (is_selected)
        ImGui::SetItemDefaultFocus();
    }
    ImGui::EndCombo();
  }
}

void gui::menu_bar() {
  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Quit", "ESC"))
        glfwSetWindowShouldClose(imgui_window, true);
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Window")) {
      if (ImGui::MenuItem("Viewer", "", windows["viewer"]))
        windows["viewer"] = !windows["viewer"];
      if (ImGui::MenuItem("Material Editor", "", windows["material editor"]))
        windows["material editor"] = !windows["material editor"];
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Settings")) {
      style_gui();
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }
}

void gui::viewer() {
  if (!windows["viewer"])
    return;
  ImGui::Begin("Viewer", &windows["viewer"],
               ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
  ImGui::Text("Some preview image");
  ImGui::End();
}
void gui::material_editor() {
  if (!windows["material editor"])
    return;
  ImGui::Begin("Material Editor", &windows["material editor"],
               ImGuiWindowFlags_NoTitleBar);
  ImGui::ColorEdit3("Base Color", glm::value_ptr(mat->base_color));
  ImGui::SliderFloat("Subsurface", &(mat->subsurface), 0.0f, 1.0f);
  ImGui::SliderFloat3("Subsurface Radius",
                      glm::value_ptr(mat->subsurface_radius), 0.0f, 1.0f);
  ImGui::ColorEdit3("Subsurface Color", glm::value_ptr(mat->subsurface_color));
  ImGui::SliderFloat("Metallic", &(mat->metallic), 0.0f, 1.0f);
  ImGui::SliderFloat("Specular", &(mat->specular), 0.0f, 1.0f);
  ImGui::SliderFloat("Specular Tint", &(mat->specular_tint), 0.0f, 1.0f);
  ImGui::SliderFloat("Roughness", &(mat->roughness), 0.0f, 1.0f);
  ImGui::SliderFloat("Anisotropic", &(mat->anisotropic), 0.0f, 1.0f);
  ImGui::SliderFloat("Anisotropic Rotation", &(mat->anisotropic_rotation), 0.0f,
                     1.0f);
  ImGui::SliderFloat("Sheen", &(mat->sheen), 0.0f, 1.0f);
  ImGui::SliderFloat("Sheen Tint", &(mat->sheen_tint), 0.0f, 1.0f);
  ImGui::SliderFloat("Clearcoat", &(mat->clearcoat), 0.0f, 1.0f);
  ImGui::SliderFloat("Clearcoat Roughness", &(mat->clearcoat_roughness), 0.0f,
                     1.0f);
  ImGui::SliderFloat("IOR", &(mat->ior), 0.0f, 1.0f);
  ImGui::SliderFloat("Transmission", &(mat->transmission), 0.0f, 1.0f);
  ImGui::End();
}

void gui::set_material_ptr(const std::shared_ptr<specula::Material> &mat_) {
  mat = mat_;
}
