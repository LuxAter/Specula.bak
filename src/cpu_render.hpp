#ifndef SPECULA_CPU_RENDER_HPP_
#define SPECULA_CPU_RENDER_HPP_

#include <functional>
#include <memory>

#include <glm/glm.hpp>

#include "specula/core.hpp"
#include "specula/image.hpp"
#include "specula/ray.hpp"
#include "specula/scene.hpp"

namespace specula {
namespace cpu {
bool render(const std::shared_ptr<Image> &img, const Scene &scene,
            const RenderArgs &args);
unsigned long
render_tile(const unsigned long &tile_id, const glm::uvec4 &bounds,
            const std::shared_ptr<Image> &img,
            const std::function<glm::vec2(const glm::uvec2 &)> &func);
glm::vec3 ray_trace(const Ray &ray, unsigned long depth = 0);
std::pair<float, std::shared_ptr<Object>> ray_march(const Ray &ray);
} // namespace cpu
} // namespace specula

#endif // SPECULA_CPU_RENDER_HPP_
