#include "specula/core/light.hpp"
#include "core/geometry/common.hpp"

specula::Light::Light(int flags, const Transform &light_to_world,
                      const MediumInterface &medium_interface, int nsamples)
    : flags(flags), nsamples(std::max(1, nsamples)),
      medium_interface(medium_interface), light_to_world(light_to_world),
      world_to_light(inverse(light_to_world)) {}
specula::Light::~Light() {}

bool specula::VisibilityTester::unoccluded(const Scene &scene) const {
  // TODO: Implement scene
  // return !scene.intersect(m_p0.spawn_ray_to(m_p1));
  return false;
}
specula::Spectrum specula::VisibilityTester::tr(const Scene &scene,
                                                Sampler &sampler) const {
  Ray ray(m_p0.spawn_ray_to(m_p1));
  Spectrum tr(1.0f);
  return Spectrum(1.0f);
  // TODO: Implement scene
  // while (true) {
  // SurfaceInteraction isect;
  // bool hit_surface = scene.intersect(ray, &isect);
  // if (hit_surface && isect.primitive->get_material() != nullptr)
  // return Spectrum(0.0f);
  // if (ray.medium)
  // tr *= ray.medium->tr(ray, sampler);
  // if (!hit_surface)
  // break;
  // ray = isect.spawn_ray_to(p1);
  // }
  return tr;
}

specula::Spectrum specula::Light::le(const RayDifferential &ray) const {
  return Spectrum(0.0f);
}
specula::AreaLight::AreaLight(const Transform &light_to_world,
                              const MediumInterface &medium, int nsamples)
    : Light((int)LightFlags::AREA, light_to_world, medium, nsamples) {}
