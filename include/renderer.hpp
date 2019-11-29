#ifndef SPECULA_RENDERER_HPP_
#define SPECULA_RENDERER_HPP_

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "filesystem.hpp"
#include "ray.hpp"

#include "object/object.hpp"

namespace specula {
namespace renderer {
extern std::vector<std::shared_ptr<object::Object>> objs;
extern glm::uvec2 res;
extern std::size_t min_bounce, spp;
extern float ep, t_max, filmz, fov;
extern glm::mat4 view;

struct tile_response_t {
  std::size_t id;
  std::vector<std::vector<glm::vec3>> data, albido, normal;
  std::vector<std::vector<float>> depth;
};

bool render_frame(const fs::path &file,
                  const std::vector<std::shared_ptr<object::Object>> &in_objs,
                  const std::array<bool, 3> &renders,
                  const std::size_t &tile_size, const std::size_t &in_spp,
                  const float &in_fov, const std::size_t &in_min_bounce,
                  const glm::uvec2 &in_res,
                  const std::array<glm::vec3, 3> &camera, const bool &denoise);
tile_response_t render_tile(const std::size_t &tile_id, const glm::uvec4 &tile);

std::tuple<glm::vec3, glm::vec3, glm::vec3, float>
ray_march(ray r, const std::size_t &depth);
std::tuple<float, std::shared_ptr<object::Object>> ray_intersect(const ray &r);
} // namespace renderer
} // namespace specula

#endif // SPECULA_RENDERER_HPP_
