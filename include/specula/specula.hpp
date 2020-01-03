#ifndef SPECULA_HPP_
#define SPECULA_HPP_

#include <array>

#include "image.hpp"
#include "log.hpp"
#include "scene.hpp"
#include "settings.hpp"
#include "version.hpp"

namespace specula {
std::array<unsigned, 3> get_version();

bool render(const std::string &file_path, const unsigned &frame,
            const Settings &settings, const Scene &scene);
bool render(const std::string &file_path, const Settings &settings,
            const Scene &scene);
Image render(const Settings &settings, const Scene &scene);
} // namespace specula

#endif // SPECULA_HPP_
