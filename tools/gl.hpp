#ifndef SPECULA_GL_HPP_
#define SPECULA_GL_HPP_

#include "glad/glad.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#include <specula/specula.hpp>

namespace gl {
extern GLFWwindow* window;

bool init();
void terminate();

bool should_close();
void set_should_close(bool setting);

void frame();

bool get_key(const int& key);
void clear_color(const glm::vec3& c);
void clear();
} // namespace gl

#endif // SPECULA_GL_HPP_
