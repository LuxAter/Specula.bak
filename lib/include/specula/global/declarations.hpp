#ifndef SPECULA_GLOBAL_DECLARATIONS_HPP_
#define SPECULA_GLOBAL_DECLARATIONS_HPP_

#include <cstdlib>

namespace specula {
class AreaLight;
class BRDF;
class BSDF;
class BSSRDF;
struct BSSRDFTable;
class BTDF;
template <typename T, std::size_t Size = 2> class BlockedArray;
template <typename T> class Bounds2;
template <typename T> class Bounds3;
class BxDF;
class Camera;
struct CameraSample;
template <std::size_t N> class CoefficientSpectrum;
struct Distribution1D;
class Distribution2D;
class Film;
class FilmTile;
class Filter;
class GeometricPrimitive;
class Integrator;
struct Interaction;
class Light;
class Material;
struct Matrix4x4;
class Medium;
class MediumInteraction;
struct MediumInterface;
class MemoryArena;
template <typename T> class Normal3;
class ParamSet;
template <typename T> struct ParamSetItem;
template <typename T> class Point2;
template <typename T> class Point3;
class Primitive;
class ProgressReporter;
class ProjectiveCamera;
class RGBSpectrum;
class RNG;
class Ray;
class RayDifferential;
class SampleIntegrator;
class SampledSpectrum;
class Sampler;
class Scene;
class SeparableBSSRDF;
class Shape;
class SurfaceInteraction;
class TabulatedBSSRDF;
template <typename T> class Texture;
class TextureParams;
class Transform;
class TransformedPrimitive;
template <typename T> class Vector2;
template <typename T> class Vector3;
class VisibilityTester;

#ifdef SPECULA_DOUBLE_PRECISION
typedef double Float;
#else
typedef float Float;
#endif
#ifdef SPECULA_SAMPLED_SPECTRUM
typedef SampledSpectrum Spectrum;
#else
typedef RGBSpectrum Spectrum;
#endif

} // namespace specula

#endif /* end of include guard: SPECULA_GLOBAL_DECLARATIONS_HPP_ */
