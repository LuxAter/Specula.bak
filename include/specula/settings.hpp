#ifndef SPECULA_SETTINGS_HPP_
#define SPECULA_SETTINGS_HPP_

#include <thread>

#include "builder.hpp"
#include "enum.hpp"

namespace specula {
ENUM(RenderPass, SHADED, ALBEDO, NORMAL, DEPTH, OBJECT_INDEX, MATERIAL_INDEX);
ENUM(Integrator, PATH_TRACING, BRANCHED_PATH_TRACING);
ENUM(Sampler, NONE, JITTER, SOBOL, MULTI_JITTER);
class Settings {
public:
  BUILD_PVAR(Settings, RenderPass, pass, SHADED);
  BUILD_PVAR(Settings, Integrator, integrator, PATH_TRACING);
  BUILD_PVAR(Settings, Sampler, sampler, JITTER);
  BUILD_PVAR(Settings, bool, tiling, true);
  BUILD_PVAR(Settings, unsigned, spp, 16);
  BUILD_PVAR(Settings, unsigned, bounces, 16);
  BUILD_PVAR(Settings, float, roulette_prob, 0.05f);
  BUILD_PVAR(Settings, unsigned, size, 32);
  BUILD_PVAR(Settings, unsigned, width, 848);
  BUILD_PVAR(Settings, unsigned, height, 480);
  BUILD_PVAR(Settings, float, epsilon, 1e-3f);
  BUILD_PVAR(Settings, float, max_dist, 1e3f);
  BUILD_PVAR(Settings, unsigned, threads, std::thread::hardware_concurrency());
};
} // namespace specula

#endif // SPECULA_SETTINGS_HPP_
