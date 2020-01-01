#include "gui.hpp"

#include <map>
#include <string>

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

static std::string colors[17] = {
    "Red",       "Pink",  "Purple", "Deep Purple", "Indigo",     "Blue",
    "Pale Blue", "Cyan",  "Teal",   "Green",       "Pale Green", "Lime",
    "Yellow",    "Amber", "Orange", "Deep Orange", "Brown"};

void gui::init(GLFWwindow *window) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  //   io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 410");
  ImGui::StyleColorsDark();
  style(false, "Blue");
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
  ImVec4 *colors = style.Colors;

  std::map<std::string, ImVec4> isotope;

  isotope["light_Red"] = ImVec4(0.99609375, 0.53515625, 0.37890625, 1.0);
  isotope["Red"] = ImVec4(0.953125, 0.26171875, 0.2109375, 1.0);
  isotope["dark_Red"] = ImVec4(0.7265625, 0.0, 0.05078125, 1.0);
  isotope["light_Pink"] = ImVec4(0.99609375, 0.375, 0.5625, 1.0);
  isotope["Pink"] = ImVec4(0.91015625, 0.1171875, 0.38671875, 1.0);
  isotope["dark_Pink"] = ImVec4(0.6875, 0.0, 0.2265625, 1.0);
  isotope["light_Purple"] = ImVec4(0.8125, 0.359375, 0.88671875, 1.0);
  isotope["Purple"] = ImVec4(0.609375, 0.15234375, 0.6875, 1.0);
  isotope["dark_Purple"] = ImVec4(0.4140625, 0.0, 0.5, 1.0);
  isotope["light_Deep Purple"] = ImVec4(0.6015625, 0.40234375, 0.9140625, 1.0);
  isotope["Deep Purple"] = ImVec4(0.40234375, 0.2265625, 0.71484375, 1.0);
  isotope["dark_Deep Purple"] = ImVec4(0.1953125, 0.04296875, 0.5234375, 1.0);
  isotope["light_Indigo"] = ImVec4(0.45703125, 0.48828125, 0.90625, 1.0);
  isotope["Indigo"] = ImVec4(0.24609375, 0.31640625, 0.70703125, 1.0);
  isotope["dark_Indigo"] = ImVec4(0.0, 0.16015625, 0.515625, 1.0);
  isotope["light_Blue"] = ImVec4(0.4296875, 0.7734375, 0.99609375, 1.0);
  isotope["Blue"] = ImVec4(0.12890625, 0.5859375, 0.94921875, 1.0);
  isotope["dark_Blue"] = ImVec4(0.0, 0.41015625, 0.75, 1.0);
  isotope["light_Pale Blue"] = ImVec4(0.40234375, 0.8515625, 0.99609375, 1.0);
  isotope["Pale Blue"] = ImVec4(0.01171875, 0.66015625, 0.953125, 1.0);
  isotope["dark_Pale Blue"] = ImVec4(0.0, 0.4765625, 0.75390625, 1.0);
  isotope["light_Cyan"] = ImVec4(0.3828125, 0.93359375, 0.99609375, 1.0);
  isotope["Cyan"] = ImVec4(0.0, 0.734375, 0.828125, 1.0);
  isotope["dark_Cyan"] = ImVec4(0.0, 0.54296875, 0.63671875, 1.0);
  isotope["light_Teal"] = ImVec4(0.3203125, 0.77734375, 0.71875, 1.0);
  isotope["Teal"] = ImVec4(0.0, 0.5859375, 0.53125, 1.0);
  isotope["dark_Teal"] = ImVec4(0.0, 0.40234375, 0.35546875, 1.0);
  isotope["light_Green"] = ImVec4(0.5, 0.8828125, 0.4921875, 1.0);
  isotope["Green"] = ImVec4(0.296875, 0.68359375, 0.3125, 1.0);
  isotope["dark_Green"] = ImVec4(0.03125, 0.49609375, 0.13671875, 1.0);
  isotope["light_Pale Green"] = ImVec4(0.7421875, 0.9609375, 0.4765625, 1.0);
  isotope["Pale Green"] = ImVec4(0.54296875, 0.76171875, 0.2890625, 1.0);
  isotope["dark_Pale Green"] = ImVec4(0.3515625, 0.5703125, 0.0859375, 1.0);
  isotope["light_Lime"] = ImVec4(0.99609375, 0.99609375, 0.4296875, 1.0);
  isotope["Lime"] = ImVec4(0.80078125, 0.859375, 0.22265625, 1.0);
  isotope["dark_Lime"] = ImVec4(0.59765625, 0.6640625, 0.0, 1.0);
  isotope["light_Yellow"] = ImVec4(0.99609375, 0.99609375, 0.4453125, 1.0);
  isotope["Yellow"] = ImVec4(0.99609375, 0.91796875, 0.23046875, 1.0);
  isotope["dark_Yellow"] = ImVec4(0.78125, 0.72265625, 0.0, 1.0);
  isotope["light_Amber"] = ImVec4(0.99609375, 0.94921875, 0.3125, 1.0);
  isotope["Amber"] = ImVec4(0.99609375, 0.75390625, 0.02734375, 1.0);
  isotope["dark_Amber"] = ImVec4(0.77734375, 0.56640625, 0.0, 1.0);
  isotope["light_Orange"] = ImVec4(0.99609375, 0.78515625, 0.27734375, 1.0);
  isotope["Orange"] = ImVec4(0.99609375, 0.59375, 0.0, 1.0);
  isotope["dark_Orange"] = ImVec4(0.7734375, 0.41015625, 0.0, 1.0);
  isotope["light_Deep Orange"] = ImVec4(0.87890625, 0.5390625, 0.3125, 1.0);
  isotope["Deep Orange"] = ImVec4(0.87890625, 0.33984375, 0.1328125, 1.0);
  isotope["dark_Deep Orange"] = ImVec4(0.765625, 0.109375, 0.0, 1.0);
  isotope["light_Brown"] = ImVec4(0.66015625, 0.5078125, 0.453125, 1.0);
  isotope["Brown"] = ImVec4(0.47265625, 0.33203125, 0.28125, 1.0);
  isotope["dark_Brown"] = ImVec4(0.29296875, 0.171875, 0.125, 1.0);
  isotope["grey1"] = ImVec4(0.921875, 0.93359375, 0.94140625, 1.0);
  isotope["grey2"] = ImVec4(0.80859375, 0.84375, 0.859375, 1.0);
  isotope["grey3"] = ImVec4(0.6875, 0.7421875, 0.76953125, 1.0);
  isotope["grey4"] = ImVec4(0.5625, 0.640625, 0.6796875, 1.0);
  isotope["grey5"] = ImVec4(0.46875, 0.5625, 0.609375, 1.0);
  isotope["grey6"] = ImVec4(0.375, 0.48828125, 0.54296875, 1.0);
  isotope["grey7"] = ImVec4(0.328125, 0.4296875, 0.4765625, 1.0);
  isotope["grey8"] = ImVec4(0.26953125, 0.3515625, 0.390625, 1.0);
  isotope["grey9"] = ImVec4(0.21484375, 0.27734375, 0.30859375, 1.0);
  isotope["grey10"] = ImVec4(0.1484375, 0.1953125, 0.21875, 1.0);

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
      ImVec4(col_main.x, col_main.y, col_main.z, 0.45f);
  style.Colors[ImGuiCol_TabUnfocused] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.35f);
  style.Colors[ImGuiCol_TabActive] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
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