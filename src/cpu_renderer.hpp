#ifndef SPECULA_CPU_RENDERER_HPP_
#define SPECULA_CPU_RENDERER_HPP_

#include <glm/glm.hpp>

#include "specula/image.hpp"
#include "specula/scene.hpp"
#include "specula/settings.hpp"
#include "specula/object.hpp"

#include "ray.hpp"

namespace specula {
namespace cpu {
specula::Image render(const Settings *settings, const Scene *scene);
unsigned long render_tile(const unsigned long &tile_id, specula::Image *img);
glm::vec3 ray_march(const ray &r, unsigned depth = 0);
std::pair<float, std::shared_ptr<Object>> ray_intersect(const ray& r);

ray camera_sample(const unsigned &px, const unsigned &py);
} // namespace cpu
} // namespace specula

#endif // SPECULA_CPU_RENDERER_HPP_
