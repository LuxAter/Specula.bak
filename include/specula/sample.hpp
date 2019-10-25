#ifndef SPECULA_SAMPLE_HPP_
#define SPECULA_SAMPLE_HPP_

#include <random>
#include <vector>

#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

namespace specula {
namespace sample {
inline std::vector<glm::vec3> UniformHemisphere(const std::size_t n_samples,
                                                const glm::vec3 &normal) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dist(0.0f, 1.0f);
  std::vector<glm::vec3> samples;
  glm::vec3 v = glm::cross(glm::vec3(0.0, 0.0, 1.0), normal);
  const float c = glm::dot(glm::vec3(0.0, 0.0, 1.0), normal);
  glm::mat4 R(1.0f);
  if (normal.x == 0.0f && normal.y == 0.0f && normal.z == -1.0f) {
    R = glm::rotate(R, (float)M_PI, glm::vec3(1.0f, 0.0f, 0.0f));
  } else {
    glm::mat4 v_skew(0.0, -v.z, v.y, 0.0f, v.z, 0, -v.x, 0.0f, -v.y, v.x, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    R += v_skew + 1.0f / (1.0f - c) * v_skew * v_skew;
  }
  for (std::size_t i = 0; i < n_samples; ++i) {
    const float u1 = dist(gen), u2 = dist(gen);
    const float r = std::sqrt(u1);
    const float theta = 2 * M_PI * u2;
    const float x = r * std::cos(theta);
    const float y = r * std::sin(theta);
    samples.push_back(
        R * glm::vec4(x, y, std::sqrt(std::max(0.0f, 1.0f - u1)), 1.0f));
  }
  return samples;
}
} // namespace sample
} // namespace specula

#endif // SPECULA_SAMPLE_HPP_
