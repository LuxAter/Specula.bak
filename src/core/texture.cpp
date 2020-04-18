#include "specula/core/texture.hpp"
#include "core/geometry/vector.hpp"
#include "core/interaction.hpp"
#include "global/compiler.hpp"
#include "global/functions.hpp"

namespace specula {
static SPECULA_CONSTEXPR int noise_perm_size = 256;
static int noise_perm[2 * noise_perm_size] = {
    151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140,
    36, 103, 30, 69, 142,
    // Remainder of the noise permutation table
    8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62,
    94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174,
    20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 77,
    146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55,
    46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76,
    132, 187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100,
    109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147,
    118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28,
    42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101,
    155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232,
    178, 185, 112, 104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12,
    191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31,
    181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254,
    138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66,
    215, 61, 156, 180, 151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194,
    233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6,
    148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32,
    57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74,
    165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60,
    211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25,
    63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135,
    130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226,
    250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59,
    227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2,
    44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19,
    98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251,
    34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249,
    14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115,
    121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72,
    243, 141, 128, 195, 78, 66, 215, 61, 156, 180};

inline Float grad(int x, int y, int z, Float dx, Float dy, Float dz) {
  int h = noise_perm[noise_perm[noise_perm[x] + y] + z];
  h &= 15;
  Float u = h < 8 || h == 12 || h == 13 ? dx : dy;
  Float v = h < 4 || h == 12 || h == 13 ? dy : dz;
  return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
}
inline Float noise_weight(Float t) {
  Float t3 = t * t * t;
  Float t4 = t3 * t;
  return 6 * t4 * t - 15 * t4 + 10 * t3;
}
} // namespace specula

specula::TextureMapping2D::~TextureMapping2D() {}

specula::UVMapping2D::UVMapping2D(Float su, Float sv, Float du, Float dv)
    : su(su), sv(sv), du(du), dv(dv) {}
specula::Point2f specula::UVMapping2D::map(const SurfaceInteraction &si,
                                           Vector2f *dstdx,
                                           Vector2f *dstdy) const {
  *dstdx = Vector2f(su * si.dudx, sv * si.dvdx);
  *dstdy = Vector2f(su * si.dudy, sv * si.dvdy);
  return Point2f(su * si.uv[0] + du, sv * si.uv[1] + dv);
}

specula::Point2f specula::SphericalMapping2D::map(const SurfaceInteraction &si,
                                                  Vector2f *dstdx,
                                                  Vector2f *dstdy) const {
  Point2f st = sphere(si.p);
  const Float delta = 0.1f;
  Point2f st_deltax = sphere(si.p + delta * si.dpdx);
  *dstdx = (st_deltax - st) / delta;
  Point2f st_deltay = sphere(si.p + delta * si.dpdy);
  *dstdy = (st_deltay - st) / delta;

  if ((*dstdx)[1] > 0.5f)
    (*dstdx)[1] = 1 - (*dstdx)[1];
  else if ((*dstdx)[1] < -0.5f)
    (*dstdx)[1] = -((*dstdx)[1] + 1);
  if ((*dstdy)[1] > 0.5f)
    (*dstdy)[1] = 1 - (*dstdy)[1];
  else if ((*dstdy)[1] < -0.5f)
    (*dstdy)[1] = -((*dstdy)[1] + 1);
  return st;
}

specula::Point2f specula::SphericalMapping2D::sphere(const Point3f &p) const {
  Vector3f vec = normalize(world_to_texture(p) - Point3f(0, 0, 0));
  Float theta = spherical_theta(vec), phi = spherical_phi(vec);
  return Point2f(theta * INV_PI, phi * INV_2PI);
}

specula::Point2f specula::CylidricalMapping2D::map(const SurfaceInteraction &si,
                                                   Vector2f *dstdx,
                                                   Vector2f *dstdy) const {
  Point2f st = cylinder(si.p);
  const Float delta = 0.01f;
  Point2f st_deltax = cylinder(si.p + delta * si.dpdx);
  *dstdx = (st_deltax - st) / delta;
  Point2f st_deltay = cylinder(si.p + delta * si.dpdy);
  *dstdy = (st_deltay - st) / delta;

  if ((*dstdx)[1] > 0.5f)
    (*dstdx)[1] = 1 - (*dstdx)[1];
  else if ((*dstdx)[1] < -0.5f)
    (*dstdx)[1] = -((*dstdx)[1] + 1);
  if ((*dstdy)[1] > 0.5f)
    (*dstdy)[1] = 1 - (*dstdy)[1];
  else if ((*dstdy)[1] < -0.5f)
    (*dstdy)[1] = -((*dstdy)[1] + 1);
  return st;
}

specula::Point2f specula::PlanarMapping2D::map(const SurfaceInteraction &si,
                                               Vector2f *dstdx,
                                               Vector2f *dstdy) const {
  Vector3f vec(si.p);
  *dstdx = Vector2f(dot(si.dpdx, vs), dot(si.dpdx, vt));
  *dstdy = Vector2f(dot(si.dpdy, vs), dot(si.dpdy, vt));
  return Point2f(ds + dot(vec, vs), dt + dot(vec, vt));
}

specula::TextureMapping3D::~TextureMapping3D() {}

specula::Point3f specula::IdentityMapping3D::map(const SurfaceInteraction &si,
                                                 Vector3f *dpdx,
                                                 Vector3f *dpdy) const {
  *dpdx = world_to_texture(si.dpdx);
  *dpdy = world_to_texture(si.dpdy);
  return world_to_texture(si.p);
}

specula::Float specula::lanczos(Float x, Float tau) {
  x = std::abs(x);
  if (x < 1e-4f)
    return 1;
  else if (x > 1.0f)
    return 0;
  x *= PI;
  Float s = std::sin(x * tau) / (x * tau);
  Float lanczos = std::sin(x) / x;
  return s * lanczos;
}
specula::Float specula::noise(Float x, Float y, Float z) {
  int ix = std::floor(x), iy = std::floor(y), iz = std::floor(z);
  Float dx = x - ix, dy = y - iy, dz = z - iz;
  ix &= noise_perm_size - 1;
  iy &= noise_perm_size - 1;
  iz &= noise_perm_size - 1;

  Float w000 = grad(ix, iy, iz, dx, dy, dz);
  Float w100 = grad(ix + 1, iy, iz, dx - 1, dy, dz);
  Float w010 = grad(ix, iy + 1, iz, dx, dy - 1, dz);
  Float w001 = grad(ix, iy, iz + 1, dx, dy, dz - 1);
  Float w110 = grad(ix + 1, iy + 1, iz, dx - 1, dy - 1, dz);
  Float w101 = grad(ix + 1, iy, iz + 1, dx - 1, dy, dz - 1);
  Float w011 = grad(ix, iy + 1, iz + 1, dx, dy - 1, dz - 1);
  Float w111 = grad(ix + 1, iy + 1, iz + 1, dx - 1, dy - 1, dz - 1);

  Float wx = noise_weight(dx), wy = noise_weight(dy), wz = noise_weight(dz);
  Float x00 = lerp(wx, w000, w100);
  Float x10 = lerp(wx, w010, w110);
  Float x01 = lerp(wx, w001, w101);
  Float x11 = lerp(wx, w011, w111);
  Float y0 = lerp(wy, x00, x10);
  Float y1 = lerp(wy, x01, x11);
  return lerp(wz, y0, y1);
}
specula::Float specula::noise(const Point3f &p) { return noise(p.x, p.y, p.z); }
specula::Float specula::fbm(const Point3f &p, const Vector3f &dpdx,
                            const Vector3f &dpdy, Float omega, int octaves) {
  Float len2 = std::max(dpdx.length_squared(), dpdy.length_squared());
  Float n = clamp(-1 - 0.5f * log2(len2), 0, octaves);
  int nint = std::floor(n);
  Float sum = 0, lambda = 1, o = 1;
  for (int i = 0; i < nint; ++i) {
    sum += o * noise(lambda * p);
    lambda *= 1.99f;
    o *= omega;
  }
  Float npartial = n - nint;
  sum += o * smooth_step(npartial, 0.3f, 0.7f) * noise(lambda * p);
  return sum;
}
specula::Float specula::turbulence(const Point3f &p, const Vector3f &dpdx,
                                   const Vector3f &dpdy, Float omega,
                                   int octaves) {
  Float len2 = std::max(dpdx.length_squared(), dpdy.length_squared());
  Float n = clamp(-1 - 0.5f * log2(len2), 0, octaves);
  int nint = std::floor(n);
  Float sum = 0, lambda = 1, o = 1;
  for (int i = 0; i < nint; ++i) {
    sum += o * std::abs(noise(lambda * p));
    lambda *= 1.99f;
    o *= omega;
  }
  Float npartial = n - nint;
  sum += o * lerp(smooth_step(npartial, 0.3f, 0.7f), 0.2f,
                  std::abs(noise(lambda * p)));
  for (int i = nint; i < octaves; ++i) {
    sum += o * 0.2f;
    o *= omega;
  }
  return sum;
  return sum;
}
