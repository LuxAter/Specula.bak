#ifndef SPECULA_HPP_
#define SPECULA_HPP_

#include <algorithm>
#include <cinttypes>
#include <cmath>
#include <memory>
#include <string>
#include <vector>

#include "log.hpp"
#include "preprocessor.hpp"

namespace specula {

#ifdef SPECULA_DOUBLE_PERCISION
typedef double Float;
#else
typedef float Float;
#endif
typedef int Int;
/**
 * @brief Get the current version of Specula
 *
 * @param major Major version
 * @param minor Minor version
 * @param patch Patch version
 */
void get_version(unsigned &major, unsigned &minor, unsigned &patch);
} // namespace specula

#endif // SPECULA_HPP_
