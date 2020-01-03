#include "specula/color.hpp"

#include <vector>

#include <glm/glm.hpp>

#include "specula/rand.hpp"

static glm::vec3 last_color;
static float golden_ratio_conj = 2224.92235949;

glm::vec3 specula::rand_color() {
  if (last_color == glm::vec3(0)) {
    last_color = glm::vec3(frand(), frand(0.3f, 1.0f), frand(0.95f, 0.951f));
  } else {
    last_color = glm::vec3(std::fmod(last_color.x + golden_ratio_conj, 360.0f),
                           frand(0.3f, 1.0f), frand(0.95f, 0.951f));
  }
  return hsv_rgb(last_color);
}
