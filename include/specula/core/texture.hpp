#ifndef SPECULA_CORE_TEXTURE_HPP_
#define SPECULA_CORE_TEXTURE_HPP_

#include "core/geometry/vector.hpp"
#include "core/interaction.hpp"
#include "core/transform/transform.hpp"
#include "geometry.hpp"
#include "memory.hpp"
#include "spectrum.hpp"
#include "specula/global.hpp"
#include "transform.hpp"

namespace specula {
class TextureMapping2D {
public:
  virtual ~TextureMapping2D();
  virtual Point2f map(const SurfaceInteraction &si, Vector2f *dstdx,
                      Vector2f *dstdy) const = 0;
};

class UVMapping2D : public TextureMapping2D {
public:
  UVMapping2D(Float su = 1, Float sv = 1, Float du = 0, Float dv = 0);
  Point2f map(const SurfaceInteraction &si, Vector2f *dstdx,
              Vector2f *dstdy) const;

private:
  const Float su, sv, du, dv;
};

class SphericalMapping2D : public TextureMapping2D {
public:
  SphericalMapping2D(const Transform &world_to_texture)
      : world_to_texture(world_to_texture) {}
  Point2f map(const SurfaceInteraction &si, Vector2f *dstdx,
              Vector2f *dstdy) const;

private:
  Point2f sphere(const Point3f &p) const;
  const Transform world_to_texture;
};

class CylidricalMapping2D : public TextureMapping2D {
public:
  CylidricalMapping2D(const Transform &world_to_texture)
      : world_to_texture(world_to_texture) {}
  Point2f map(const SurfaceInteraction &si, Vector2f *dstdx,
              Vector2f *dstdy) const;

private:
  Point2f cylinder(const Point3f &p) const {
    Vector3f vec = normalize(world_to_texture(p) - Point3f(0, 0, 0));
    return Point2f((PI + std::atan2(vec.y, vec.x)) * INV_2PI, vec.z);
  }
  const Transform world_to_texture;
};

class PlanarMapping2D : public TextureMapping2D {
public:
  PlanarMapping2D(const Vector3f &vs, const Vector3f &vt, Float ds = 0,
                  Float dt = 0)
      : vs(vs), vt(vt), ds(ds), dt(dt) {}
  Point2f map(const SurfaceInteraction &si, Vector2f *dstdx,
              Vector2f *dstdy) const;

private:
  const Vector3f vs, vt;
  const Float ds, dt;
};

class TextureMapping3D {
public:
  virtual ~TextureMapping3D();
  virtual Point3f map(const SurfaceInteraction &si, Vector3f *dpdx,
                      Vector3f *dpdy) const = 0;
};

class IdentityMapping3D : public TextureMapping3D {
public:
  IdentityMapping3D(const Transform &world_to_texture)
      : world_to_texture(world_to_texture) {}
  Point3f map(const SurfaceInteraction &si, Vector3f *dpdx,
              Vector3f *dpdy) const;

private:
  const Transform world_to_texture;
};

template <typename T> class Texture {
public:
  virtual ~Texture() {}

  virtual T evaluate(const SurfaceInteraction &) const = 0;
};

Float lanczos(Float, Float tau = 2);
Float noise(Float x, Float y = 0.5f, Float z = 0.5f);
Float noise(const Point3f &p);
Float fbm(const Point3f &p, const Vector3f &dpdx, const Vector3f &dpdy,
          Float omega, int octaves);
Float turbulence(const Point3f &p, const Vector3f &dpdx, const Vector3f &dpdy,
                 Float omega, int octaves);

} // namespace specula

#endif // SPECULA_CORE_TEXTURE_HPP_
