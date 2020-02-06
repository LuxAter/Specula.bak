#include "gl.hpp"

#include <GLFW/glfw3.h>
#include <chrono>
#include <glm/glm.hpp>
#include <vector>

#include <specula/specula.hpp>

void glfw_error_callback(int error, const char *description) {
  LCERROR("OpenGL", "[{}] {}", error, description);
}

static std::chrono::high_resolution_clock::time_point fps_start;
static std::size_t fps_counter = 0;
#ifdef __DEBUG__
static std::size_t fps_report_interval = 10;
#else
static std::size_t fps_report_interval = 60;
#endif

namespace gl {
GLFWwindow *window = nullptr;
} // namespace gl

bool gl::initialize() {
  specula::logger::initialize_logger("OpenGL");
  if (!glfwInit()) {
    LCERROR("OpenGL", "GLFW initalization failed");
    return false;
  } else {
    LCINFO("OpenGL", "Initalized GLFW");
  }
  glfwSetErrorCallback(glfw_error_callback);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  window = glfwCreateWindow(1000, 1000, "Specula", NULL, NULL);
  if (!window) {
    LCERROR("OpenGL", "Failed to construct GLFW window");
    glfwTerminate();
    return false;
  }
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    LCERROR("OpenGL", "Failed to initalize OpenGL context");
    glfwDestroyWindow(window);
    glfwTerminate();
    return false;
  }
  glfwSwapInterval(1);
  fps_start = std::chrono::high_resolution_clock::now();
  fps_counter = 0;
  return true;
}
void gl::terminate() {
  if (window)
    glfwDestroyWindow(window);
  glfwTerminate();
}

bool gl::should_close() { return glfwWindowShouldClose(window); }
void gl::set_should_close(bool setting) {
  glfwSetWindowShouldClose(window, setting ? GLFW_TRUE : GLFW_FALSE);
}

void gl::frame() {
  glfwPollEvents();
  glfwSwapBuffers(window);
  clear();
  fps_counter++;
  if (fps_counter % 60 == 0) {
    std::chrono::high_resolution_clock::time_point now_tp =
        std::chrono::high_resolution_clock::now();
    std::size_t duration =
        std::chrono::duration_cast<std::chrono::seconds>(now_tp - fps_start)
            .count();
    if (duration >= fps_report_interval) {
      LCINFO("OpenGL", "FPS: {:6.2}",
             fps_counter / static_cast<float>(duration));
      fps_counter = 0;
      fps_start = now_tp;
    }
  }
}

bool gl::get_key(const int &key) {
  return glfwGetKey(gl::window, key) == GLFW_PRESS;
}
void gl::clear_color(const glm::vec3 &c) { glClearColor(c.r, c.g, c.b, 0.0f); }
void gl::clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }