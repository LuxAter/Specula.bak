#ifndef SPECULA_RENDER_CASTER_HPP_
#define SPECULA_RENDER_CASTER_HPP_

#include "../color.hpp"
#include "../scene.hpp"
#include "basic/vector.hpp"
#include "options.hpp"

namespace specula {
Color CastRay(const estl::base::Vec3d& start, const estl::base::Vec3d& dir,
              const Scene& scene, const Options& opt, const uint32_t& depth = 0);
}  // namespace specula

#endif  // SPECULA_RENDER_CASTER_HPP_
