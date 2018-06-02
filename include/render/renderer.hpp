#ifndef SPECULA_RENDER_RENDERER_HPP_
#define SPECULA_RENDER_RENDERER_HPP_

#include "../image.hpp"
#include "caster.hpp"
#include "options.hpp"
#include "../scene.hpp"

namespace specula {
  Image RenderImage(uint32_t width, uint32_t height, const Scene& scene, const Options& opt);
} // namespace specula

#endif  // SPECULA_RENDER_RENDERER_HPP_
