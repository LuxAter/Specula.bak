#include "specula/core/lightdistrib.hpp"
#include "specula/core/sampling.hpp"

specula::LightDistribution::~LightDistribution() {}

specula::UniformLightDistribution::UniformLightDistribution(
    const Scene &scene) {
  // TODO
  // std::vector<Float> prob(scene.lights.size(), Float(1));
  // distrib.reset(new Distribution1D(&prob[0], int(prob.size())));
}
const specula::Distribution1D *
specula::UniformLightDistribution::lookup(const Point3f &p) const {
  return distrib.get();
}

// TODO
// specula::PowerLightDistribution::PowerLightDistribution(const Scene& scene) :
// disrib(compute_light_power_distribution(scene)) {}

const specula::Distribution1D *
specula::PowerLightDistribution::lookup(const Point3f &p) const {
  return distrib.get();
}

namespace specula {
static const uint64_t invalid_packed_pos = 0xffffffffffffffff;
} // namespace specula

specula::SpatialLightDistribution::SpatialLightDistribution(const Scene &scene,
                                                            int max_voxels)
    : scene(scene) {
    }
