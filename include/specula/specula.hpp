/**
 * @file specula.hpp
 * @brief Main include file
 * @version 0.1
 * @date 2020-01-20
 *
 * @copyright Copyright (c) 2020
 *
 * Include this file into other projects to use the Specula library. No other
 * files need to be included for Specula to work.
 *
 */
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
