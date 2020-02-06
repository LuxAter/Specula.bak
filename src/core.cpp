#include "specula/core.hpp"

#include "specula/dev.hpp"
#include "specula/gpu.hpp"
#include "specula/image.hpp"

#include <glm/glm.hpp>

using namespace glm;

bool specula::initialize() {
  logger::initialize_core_logger();
  return gpu::initialize();
}

specula::Image specula::render() {
  return specula::Image({500, 500}, {0.2, 0.7, 0.4});
}
