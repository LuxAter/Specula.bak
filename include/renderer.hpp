#ifndef SPECULA_RENDERER_HPP_
#define SPECULA_RENDERER_HPP_

#include <cstdlib>
#include <string>

#include "image/image.hpp"
#include "math.hpp"
#include "object/object_class.hpp"
#include "renderer_args.hpp"

namespace specula {
struct buffer_t {
  const std::shared_ptr<image::Image> img, albedo, depth, normal;
};
bool render(const renderer_args_t &args);

#ifdef __OPENCL__
bool gpu_renderer(const std::vector<std::shared_ptr<ObjectBase>> &objs,
                  const renderer_args_t &args, const buffer_t &buffers);
#endif
bool cpu_renderer(const std::vector<std::shared_ptr<ObjectBase>> &objs,
                  const renderer_args_t &args, const buffer_t &buffers);

std::size_t cpu_render_tile(const std::size_t &tile_id,
                            const glm::uvec2 &img_bounds,
                            const glm::uvec4 &tile_bounds,
                            const buffer_t &buffers);
} // namespace specula

#endif // SPECULA_RENDERER_HPP_
