#include "renderer_args.hpp"

#include <optional>
#include <thread>
#include <cmath>

specula::RendererArgs::RendererArgs()
    : args{"out.png", 0,     16,
           10,        32,    std::thread::hardware_concurrency(),
           1000,      1000,  M_PI / 4.0f,
           false,     false, false,
           false,     false} {
           }

specula::RendererArgs &specula::RendererArgs::file(const std::string &file) {
  args.file = file;
  return *this;
}
specula::RendererArgs &
specula::RendererArgs::file(const std::optional<std::string> &file) {
  if (file)
    args.file = file.value();
  return *this;
}
specula::RendererArgs &specula::RendererArgs::frame(const std::size_t &frame) {
  args.frame = frame;
  return *this;
}
specula::RendererArgs &
specula::RendererArgs::frame(const std::optional<std::size_t> &frame) {
  if (frame)
    args.frame = frame.value();
  return *this;
}
specula::RendererArgs &specula::RendererArgs::spp(const std::size_t &spp) {
  args.spp = spp;
  return *this;
}
specula::RendererArgs &
specula::RendererArgs::spp(const std::optional<std::size_t> &spp) {
  if (spp)
    args.spp = spp.value();
  return *this;
}
specula::RendererArgs &
specula::RendererArgs::min_bounces(const std::size_t &min_bounces) {
  args.min_bounces = min_bounces;
  return *this;
}
specula::RendererArgs &specula::RendererArgs::min_bounces(
    const std::optional<std::size_t> &min_bounces) {
  if (min_bounces)
    args.min_bounces = min_bounces.value();
  return *this;
}
specula::RendererArgs &
specula::RendererArgs::tile_size(const std::size_t &tile_size) {
  args.tile_size = tile_size;
  return *this;
}
specula::RendererArgs &
specula::RendererArgs::tile_size(const std::optional<std::size_t> &tile_size) {
  if (tile_size)
    args.tile_size = tile_size.value();
  return *this;
}
specula::RendererArgs &
specula::RendererArgs::threads(const std::size_t &threads) {
  args.threads = threads;
  return *this;
}
specula::RendererArgs &
specula::RendererArgs::threads(const std::optional<std::size_t> &threads) {
  if (threads)
    args.threads = threads.value();
  return *this;
}
specula::RendererArgs &
specula::RendererArgs::res_width(const std::size_t &res_width) {
  args.res_width = res_width;
  return *this;
}
specula::RendererArgs &
specula::RendererArgs::res_width(const std::optional<std::size_t> &res_width) {
  if (res_width)
    args.res_width = res_width.value();
  return *this;
}
specula::RendererArgs &
specula::RendererArgs::res_height(const std::size_t &res_height) {
  args.res_height = res_height;
  return *this;
}
specula::RendererArgs &specula::RendererArgs::res_height(
    const std::optional<std::size_t> &res_height) {
  if (res_height)
    args.res_height = res_height.value();
  return *this;
}
specula::RendererArgs &specula::RendererArgs::fov(const float &fov) {
  args.fov = fov;
  return *this;
}
specula::RendererArgs &
specula::RendererArgs::fov(const std::optional<float> &fov) {
  if (fov)
    args.fov = fov.value();
  return *this;
}
specula::RendererArgs &specula::RendererArgs::albedo(const bool &albedo) {
  args.render_albedo = albedo;
  return *this;
}
specula::RendererArgs &
specula::RendererArgs::albedo(const std::optional<bool> &albedo) {
  if (albedo)
    args.render_albedo = albedo.value();
  return *this;
}
specula::RendererArgs &specula::RendererArgs::normal(const bool &normal) {
  args.render_normal = normal;
  return *this;
}
specula::RendererArgs &
specula::RendererArgs::normal(const std::optional<bool> &normal) {
  if (normal)
    args.render_normal = normal.value();
  return *this;
}
specula::RendererArgs &specula::RendererArgs::depth(const bool &depth) {
  args.render_depth = depth;
  return *this;
}
specula::RendererArgs &
specula::RendererArgs::depth(const std::optional<bool> &depth) {
  if (depth)
    args.render_depth = depth.value();
  return *this;
}
specula::RendererArgs &specula::RendererArgs::denoise(const bool &denoise) {
  args.denoise = denoise;
  return *this;
}
specula::RendererArgs &
specula::RendererArgs::denoise(const std::optional<bool> &denoise) {
  if (denoise)
    args.denoise = denoise.value();
  return *this;
}
specula::RendererArgs &specula::RendererArgs::sequence(const bool &sequence) {
  args.sequence = sequence;
  return *this;
}
specula::RendererArgs &
specula::RendererArgs::sequence(const std::optional<bool> &sequence) {
  if (sequence)
    args.sequence = sequence.value();
  return *this;
}
