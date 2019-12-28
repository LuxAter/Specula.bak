#ifndef SPECULA_CORE_HPP_
#define SPECULA_CORE_HPP_

#include <cmath>
#include <optional>
#include <thread>

#include "scene.hpp"

#define BUILD_VAR_OPT(name, type)                                              \
  inline RenderArgsBuilder &name(const std::optional<type> &v) {               \
    if (v)                                                                     \
      data.name = v.value();                                                   \
    return *this;                                                              \
  }                                                                            \
  inline RenderArgsBuilder &name(const type &v) {                              \
    data.name = v;                                                             \
    return *this;                                                              \
  }

namespace specula {
struct RenderArgs {
  std::string file;
  unsigned long frame, spp, bounces, tile_size, threads, res_width, res_height;
  float time_max, epsilon;
  bool sequence;
};
class RenderArgsBuilder {
public:
  RenderArgsBuilder()
      : data{"out.png", 0,    64,
             10,        64,   std::thread::hardware_concurrency(),
             1000,      1000, 1e3f,
             1e-5f,     false} {}

  BUILD_VAR_OPT(file, std::string);
  BUILD_VAR_OPT(frame, unsigned long);
  BUILD_VAR_OPT(spp, unsigned long);
  BUILD_VAR_OPT(bounces, unsigned long);
  BUILD_VAR_OPT(tile_size, unsigned long);
  BUILD_VAR_OPT(threads, unsigned long);
  BUILD_VAR_OPT(res_width, unsigned long);
  BUILD_VAR_OPT(res_height, unsigned long);
  BUILD_VAR_OPT(time_max, unsigned long);
  BUILD_VAR_OPT(epsilon, unsigned long);
  BUILD_VAR_OPT(sequence, bool);

  inline RenderArgs build() const { return data; }

private:
  RenderArgs data;
};
bool render(const Scene &scene, const RenderArgs &args);
} // namespace specula

#endif /* end of include guard: SPECULA_CORE_HPP_ */
