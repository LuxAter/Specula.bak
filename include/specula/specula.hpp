#ifndef SPECULA_HPP_
#define SPECULA_HPP_

#include <array>

#include "core.hpp"
#include "image.hpp"
#include "object.hpp"
#include "scene.hpp"
#include "shader/material.hpp"
#include "version.hpp"

namespace specula {
std::array<unsigned, 3> get_version();
} // namespace specula

#endif // SPECULA_HPP_
