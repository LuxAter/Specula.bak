#ifndef SPECULA_CORE_LIGHT_HPP_
#define SPECULA_CORE_LIGHT_HPP_

#include "core/geometry/normal.hpp"
#include "core/geometry/point.hpp"
#include "core/geometry/vector.hpp"
#include "core/interaction.hpp"
#include "core/medium.hpp"
#include "core/transform.hpp"
#include "specula/global.hpp"

namespace specula {
enum class LightFlags : int {
  DELTA_POSITION = 1,
  DELTA_DIRECTION = 2,
  AREA = 4,
  INFINITE = 8
};

inline bool is_delta_light(int flags) {
  return flags & (int)LightFlags::DELTA_POSITION ||
         flags & (int)LightFlags::DELTA_DIRECTION;
}

class Light {
public:
  Light(int flags, const Transform &light_to_world,
        const MediumInterface &medium_interface, int nsamples = 1);
  virtual ~Light();

  virtual Spectrum sample_li(const Interaction &ref, const Point2f &u,
                             Vector3f *wi, Float *pdf,
                             VisibilityTester *vis) const = 0;
  virtual Spectrum power() const = 0;
  virtual void preprocess(const Scene &scene) {}
  virtual Spectrum le(const RayDifferential &r) const;
  virtual Float pdf_li(const Interaction &ref, const Vector3f &wi) const = 0;
  virtual Spectrum sample_le(const Point2f &u1, const Point2f &u2, Float time,
                             Ray *ray, Normal3f *nlight, Float *pdf_pos,
                             Float *pdf_dir) const = 0;
  virtual void pdf_le(const Ray &ray, const Normal3f &nlight, Float *pdf_pos,
                      Float *pdf_dir) const = 0;

  const int flags;
  const int nsamples;
  const MediumInterface medium_interface;

protected:
  const Transform light_to_world, world_to_light;
};

class VisibilityTester {
public:
  VisibilityTester() {}
  VisibilityTester(const Interaction &p0, const Interaction &p1)
      : m_p0(p0), m_p1(p1) {}
  const Interaction &p0() const { return m_p0; }
  const Interaction &p1() const { return m_p1; }
  bool unoccluded(const Scene &scene) const;
  Spectrum tr(const Scene &scene, Sampler &sampler) const;

private:
  Interaction m_p0, m_p1;
};

class AreaLight : public Light {
public:
  AreaLight(const Transform &light_to_world, const MediumInterface &medium,
            int nsamples);
  virtual Spectrum l(const Interaction &inter, const Vector3f &w) const = 0;
};

} // namespace specula

#endif // SPECULA_CORE_LIGHT_HPP_
