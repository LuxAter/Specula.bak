/**
 * @file declarations.hpp
 * @brief Forward declarations for all types.
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2020-03-30
 * @ingroup global global-declarations
 */
#ifndef SPECULA_GLOBAL_DECLARATIONS_HPP_
#define SPECULA_GLOBAL_DECLARATIONS_HPP_

/**
 * @defgroup global-declarations Global Declarations
 * @ingroup global
 *
 * All forward declarations and a select few type declarations for specialized
 * types defined at compile time.
 */

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
template <typename T> class Matrix4x4;
class Medium;
class MediumInteraction;
struct MediumInterface;
class MemoryArena;
template <typename T> class Normal2;
template <typename T> class Normal3;
class ParamSet;
template <typename T> struct ParamSetItem;
template <typename T> class Point2;
template <typename T> class Point3;
class Primitive;
class ProgressReporter;
class ProjectiveCamera;
class RGBSpectrum;
class Rng;
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

/**
 * @brief Common integer type
 * @ingroup global-declarations
 */
typedef int Int;
/**
 * @brief Common unsigned integer type
 * @ingroup global-declarations
 */
typedef unsigned UInt;
#ifdef SPECULA_DOUBLE_PRECISION
/**
 * @brief Common floating point type
 * @ingroup global-declarations
 *
 * If ``SPECULA_DOUBLE_PRECISION`` is defined in the preprocessor, then this
 * will be  representative of ``double`` otherwise it is ``float``.
 *
 */
typedef double Float;
#else
/**
 * @brief Common floating point type
 * @ingroup global-declarations
 *
 * If ``SPECULA_DOUBLE_PRECISION`` is defined in the preprocessor, then this
 * will be  representative of ``double`` otherwise it is ``float``.
 *
 */
typedef float Float;
#endif

#ifdef SPECULA_SAMPLED_SPECTRUM
/**
 * @brief General spectrum type.
 * @ingroup global-declarations
 *
 * If ``SPECULA_SAMPLED_SPECTRUM`` is defined in the preprocessor, then this
 * will be representative of ``SampledSpectrum``, otherwise it is
 * ``RGBSpectrum``.
 */
typedef SampledSpectrum Spectrum;
#else
/**
 * @brief General spectrum type.
 * @ingroup global-declarations
 *
 * If ``SPECULA_SAMPLED_SPECTRUM`` is defined in the preprocessor, then this
 * will be representative of ``SampledSpectrum``, otherwise it is
 * ``RGBSpectrum``.
 */
typedef RGBSpectrum Spectrum;
#endif

} // namespace specula

#endif /* end of include guard: SPECULA_GLOBAL_DECLARATIONS_HPP_ */
