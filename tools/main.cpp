#include <iostream>

#include <glad/glad.h>

#include <memory>
#include <specula/log.hpp>
#include <specula/specula.hpp>

#include <GLFW/glfw3.h>

#include <imgui.h>

#include "gui.hpp"
#include "specula/material.hpp"

void glfw_error_callback(int error_code, const char *description) {
  specula::logger::error("GLFW [{}]: {}", error_code, description);
}
void glfw_framebuffer_size_callback(GLFWwindow *, int w, int h) {
  glViewport(0, 0, w, h);
}

int main(int argc, char const *argv[]) {
  specula::initalize_logger(10);
  auto [major, minor, patch] = specula::get_version();
  LINFO("Specula v{}.{}.{}", major, minor, patch);

  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit()) {
    const char *glfw_error;
    glfwGetError(&glfw_error);
    LCRITICAL("Failed to initalize GLFW: {}", glfw_error);
    return -1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  GLFWwindow *window = glfwCreateWindow(1280, 720, "Specula", NULL, NULL);
  if (window == NULL) {
    glfwTerminate();
    LCRITICAL("Failed to create GLFW window");
    return -1;
  }
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    LCRITICAL("Failed to load OpenGL");
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
  }

  glViewport(0, 0, 1280, 720);
  glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);
  glClearColor(0.0, 0.0, 0.0, 1.0);

  gui::init(window);

  glm::vec3 base_color;
  gui::create_window("Material Editor");
  gui::add_variable("Material Editor", "Base Color", &base_color);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);

    gui::frame();

    gui::render();
    glfwSwapBuffers(window);
  }

  gui::shutdown();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
