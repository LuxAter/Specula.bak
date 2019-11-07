#ifndef SPECULA_RENDERER_HPP_
#define SPECULA_RENDERER_HPP_

#include <vector>
#include <memory>

#include "filesystem.hpp"

#include "util/util.hpp"
#include "object/object.hpp"

namespace specula {
  namespace renderer {
    bool render_frame(const fs::path& file, std::vector<std::shared_ptr<object::Object>>& objs, 
  } // namespace renderer
} // namespace specula

#endif  // SPECULA_RENDERER_HPP_
