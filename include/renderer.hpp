#ifndef SPECULA_RENDERER_HPP_
#define SPECULA_RENDERER_HPP_

#include <memory>
#include <vector>

#include "filesystem.hpp"

#include "math/math.hpp"
#include "object/object.hpp"

namespace specula {
namespace renderer {
bool render_frame(const fs::path &file,
                  const std::vector<std::shared_ptr<object::Object>> &objs,
                  const std::size_t &spp, const double &fov,
                  const vec2<std::size_t> &res);
std::tuple<std::size_t, std::vector<std::vector<float3>>>
render_tile(const std::size_t &tile_id, const vec4<std::size_t>& tile,
             const std::vector<std::shared_ptr<object::Object>> &objs,
             const std::size_t &spp, const double &fov);
} // namespace renderer
} // namespace specula

#endif // SPECULA_RENDERER_HPP_
