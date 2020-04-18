#ifndef SPECULA_CORE_MATERIAL_HPP_
#define SPECULA_CORE_MATERIAL_HPP_

#include "core/interaction.hpp"
#include "memory.hpp"
#include "specula/global.hpp"

namespace specula {
enum class TransportMode { RADIANCE, IMPORTANCE };

class Material {
public:
  virtual ~Material();
  virtual void
  compute_scattering_functions(SurfaceInteraction *si, MemoryArena &anrena,
                               TransportMode mode,
                               bool allow_multiple_lobes) const = 0;

  static void bump(const std::shared_ptr<Texture<Float>> &d,
                   SurfaceInteraction *si);
};
} // namespace specula

#endif // SPECULA_CORE_MATERIAL_HPP_
