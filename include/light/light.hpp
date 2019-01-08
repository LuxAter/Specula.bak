#ifndef SPECULA_LIGHT_LIGHT_HPP_
#define SPECULA_LIGHT_LIGHT_HPP_

#include <limits>
#include <vector>
#include <random>
#include <cmath>

#include "../color.hpp"
#include "../math/math.hpp"

namespace specula {
namespace light {
  enum LightType { POINT_LIGHT, DIRECTION_LIGHT, CIRCLE_LIGHT, RECT_LIGHT };
  class Light {
   public:
    Light(Color c = Color(1.0), double i = -1);
    Light(LightType type, Color c = Color(1.0), double i = -1);
    Light(LightType type, const math::vec3<double>& va, Color c = Color(1.0),
          double i = -1);
    Light(LightType type, const math::vec3<double>& va, const math::vec3<double>& vb,
          Color c = Color(1.0), double i = -1);
    Light(LightType type, const math::vec3<double>& va, const math::vec3<double>& vb,
          const double& r, std::size_t samples = 16, Color c = Color(1.0),
          double i = -1);
    Light(LightType type, const math::vec3<double>& va, const math::vec3<double>& vb,
          const double& w, const double& h, std::size_t samples = 16,
          Color c = Color(1.0), double i = -1);

    void Translate(const math::vec3<double>& trans);
    void SetPosition(const math::vec3<double>& pos);

    void SetDirection(const math::vec3<double>& dir);

    void Illuminate(const math::vec3<double>& p, math::vec3<double>& dir,
                    math::vec3<double>& val, double& dist);

    std::vector<math::vec3<double>> Sample();

    Color color;
    double intensity;

    LightType type_;
    math::vec3<double> direction_;
    math::vec3<double> position_;
    std::size_t samples_;
    double radius_, w_, h_;
  };
}  // namespace light
}  // namespace specula

#endif  // SPECULA_LIGHT_LIGHT_HPP_
