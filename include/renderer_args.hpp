#ifndef SPECULA_RENDERER_ARGS_HPP_
#define SPECULA_RENDERER_ARGS_HPP_

#include <optional>
#include <thread>

namespace specula {
struct renderer_args_t {
  std::string file;
  std::size_t frame;
  std::size_t spp, min_bounces, tile_size, threads, res_width, res_height;
  float fov;
  bool render_albedo, render_normal, render_depth, denoise;
  bool sequence;
};
class RendererArgs {
public:
  RendererArgs();
  inline renderer_args_t build() const { return args; }

  RendererArgs &file(const std::string &file);
  RendererArgs &file(const std::optional<std::string> &file);
  RendererArgs &frame(const std::size_t &frame);
  RendererArgs &frame(const std::optional<std::size_t> &frame);
  RendererArgs &spp(const std::size_t &spp);
  RendererArgs &spp(const std::optional<std::size_t> &spp);
  RendererArgs &min_bounces(const std::size_t &min_bounces);
  RendererArgs &min_bounces(const std::optional<std::size_t> &min_bounces);
  RendererArgs &tile_size(const std::size_t &tile_size);
  RendererArgs &tile_size(const std::optional<std::size_t> &tile_size);
  RendererArgs &threads(const std::size_t &threads);
  RendererArgs &threads(const std::optional<std::size_t> &threads);
  RendererArgs &res_width(const std::size_t &res_width);
  RendererArgs &res_width(const std::optional<std::size_t> &res_width);
  RendererArgs &res_height(const std::size_t &res_height);
  RendererArgs &res_height(const std::optional<std::size_t> &res_height);
  RendererArgs &fov(const float &fov);
  RendererArgs &fov(const std::optional<float> &fov);
  RendererArgs &albedo(const bool &albedo);
  RendererArgs &albedo(const std::optional<bool> &albedo);
  RendererArgs &normal(const bool &normal);
  RendererArgs &normal(const std::optional<bool> &normal);
  RendererArgs &depth(const bool &depth);
  RendererArgs &depth(const std::optional<bool> &depth);
  RendererArgs &denoise(const bool &denoise);
  RendererArgs &denoise(const std::optional<bool> &denoise);
  RendererArgs &sequence(const bool &sequence);
  RendererArgs &sequence(const std::optional<bool> &sequence);

private:
  renderer_args_t args;
};
} // namespace specula

#endif // SPECULA_RENDERER_ARGS_HPP_
