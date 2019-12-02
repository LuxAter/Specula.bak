#ifndef SPECULA_RENDERER_HPP_
#define SPECULA_RENDERER_HPP_

#include <cstdlib>
#include <string>

#include "renderer_args.hpp"
#include "image/image.hpp"
#include "object/object_class.hpp"

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
} // namespace specula

#endif // SPECULA_RENDERER_HPP_
