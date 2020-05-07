#ifndef SPECULA_CORE_LIGHTDISTRIB_HPP_
#define SPECULA_CORE_LIGHTDISTRIB_HPP_

#include "core/geometry/point.hpp"
#include "specula/global.hpp"

namespace specula {
class LightDistribution {
public:
  virtual ~LightDistribution();
  virtual const Distribution1D *lookup(const Point3f &p) const = 0;
};

class UniformLightDistribution : public LightDistribution {
public:
  UniformLightDistribution(const Scene &scene);
  const Distribution1D *lookup(const Point3f &p) const;

private:
  std::unique_ptr<Distribution1D> distrib;
};

class PowerLightDistribution : public LightDistribution {
public:
  PowerLightDistribution(const Scene &scene);
  const Distribution1D *lookup(const Point3f &p) const;

private:
  std::unique_ptr<Distribution1D> distrib;
};

class SpatialLightDistribution : public LightDistribution {
public:
  SpatialLightDistribution(const Scene &scene, int max_voxels = 64);
  ~SpatialLightDistribution();
  const Distribution1D *lookup(const Point3f &p) const;

private:
  struct HashEntry {
    std::atomic<uint64_t> packed_pos;
    std::atomic<Distribution1D *> distribution;
  };

  Distribution1D *compute_distribution(Point3i pi) const;

  const Scene &scene;
  int nvoxels[3];
  mutable std::unique_ptr<HashEntry[]> hash_table;
  size_t hash_table_size;
};

std::unique_ptr<LightDistribution>
create_light_sample_distribution(const std::string &name, const Scene &scene);

} // namespace specula

#endif // SPECULA_CORE_LIGHTDISTRIB_HPP_
