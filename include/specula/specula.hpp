#ifndef SPECULA_HPP_
#define SPECULA_HPP_

#include "log.hpp"

namespace specula {
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
