#ifndef SPECULA_RENDERER_HPP_
#define SPECULA_RENDERER_HPP_

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "filesystem.hpp"

#include "object/object.hpp"

namespace specula {
namespace renderer {
bool render_frame(const fs::path &file,
                  const std::vector<std::shared_ptr<object::Object>> &objs,
                  const std::size_t &spp, const float &fov,
                  const glm::uvec2 &res,
                  const std::array<glm::vec3, 3> &camera);
std::tuple<std::size_t, std::vector<std::vector<glm::vec3>>>
render_tile(const std::size_t &tile_id, const glm::uvec4 &tile,
            const glm::uvec2 &res,
            const std::vector<std::shared_ptr<object::Object>> &objs,
            const std::size_t &spp, const float &fov, const float &filmz,
            const glm::mat4 &view);
glm::vec3 ray_march(const glm::vec3 &o, const glm::vec3 &d,
                    const std::vector<std::shared_ptr<object::Object>> &objs,
                    const float &ep, const float &t_max,
                    const std::size_t &depth);
std::tuple<float, std::shared_ptr<object::Object>>
ray_intersect(const glm::vec3 &o, const glm::vec3 &d,
              const std::vector<std::shared_ptr<object::Object>> &objs,
              const float &ep, const float &t_max);
} // namespace renderer
} // namespace specula

#endif // SPECULA_RENDERER_HPP_
