#include "render/caster.hpp"

#include <random>

#include "render/options.hpp"

#include "basic/vector.hpp"
#include "color.hpp"
#include "scene.hpp"

using namespace estl::base;

static std::random_device rd_;
static std::mt19937 generator_(rd_());
static std::uniform_real_distribution<double> distribution_(-M_PI / 2.0,
                                                            M_PI / 2.0);

specula::Color specula::CastRay(const estl::base::Vec3d& start,
                                const estl::base::Vec3d& dir,
                                const Scene& scene, const Options& opt,
                                const uint32_t& depth) {
  if (depth > opt.max_depth) {
    return {0.0, 0.0, 0.0};
  }
  Color hit_color = {0.0, 0.0, 0.0};
  IntersectData isec;
  if (scene.Trace(start, dir, isec)) {
    // return isec.mat.diffuse;
    // if (isec.mat.emisivity != 0) {
    //   hit_color = Mix(isec.mat.emmisive, isec.mat.emisivity, isec.mat.diffuse);
    // } else {
    //   hit_color = isec.mat.diffuse;
    // }
    // return hit_color;
    // Need to reimplement lights/Direct lighting
    // Color direct_lighting;
    // for(auto light : scene.lights){
    //   Vec3d light_dir;
    //   IntersectData shaddow_isect;
    //
    // }
    Color indirect_color;
    uint32_t N = opt.sample_count;
    double theta, phi;
    double p = 1.0 / (2.0 * M_PI);
    double BRDF = 0.5 / M_PI;
    theta = atan(isec.normal.y / isec.normal.x);
    phi = atan(sqrt(pow(isec.normal.x, 2) + pow(isec.normal.y, 2)) /
               isec.normal.z);
    for (uint32_t N = 0; N < opt.sample_count; ++N) {
      double r_theta = theta + distribution_(generator_);
      double r_phi = phi + distribution_(generator_);
      double s_phi = sin(r_phi);
      Vec3d new_dir = {s_phi * cos(r_theta), s_phi * sin(r_theta), cos(r_phi)};
      double cos_theta = Dot(new_dir, isec.normal);
      indirect_color =
          indirect_color + (CastRay(isec.point, new_dir, scene, opt, depth + 1));
      // std::cout << indirect_color.r << "\n";
      // std::cout << r_theta << "," << r_phi << "\n";
    }
    if (isec.mat.emisivity != 0) {
      hit_color = Mix(isec.mat.emmisive, isec.mat.emisivity, Mix(isec.mat.diffuse, 0.5, indirect_color));
    } else {
      hit_color = indirect_color;
      // hit_color = Mix(isec.mat.diffuse, 0.5, indirect_color);
    }
  }
  return hit_color;
}
