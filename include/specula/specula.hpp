#ifndef SPECULA_HPP_
#define SPECULA_HPP_

#include "version.hpp"
#include "log.hpp"
#include "fs.hpp"
#include "fmt.hpp"
#include "cl.hpp"
#include "image/image.hpp"
#include "primatives/primatives.hpp"

namespace specula {
inline void version(unsigned &major, unsigned &minor, unsigned &patch) {
  major = SPECULA_VERSION_MAJOR;
  patch = SPECULA_VERSION_MINOR;
  patch = SPECULA_VERSION_PATCH;
}
} // namespace specula

#endif // SPECULA_HPP_
