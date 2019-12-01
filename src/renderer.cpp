#include "renderer.hpp"

#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include "filesystem.hpp"
#include "image/image.hpp"
#include "log.hpp"
#include "renderer_args.hpp"
#include "scene.hpp"

bool specula::render(const renderer_args_t &args) {
  LDEBUG("FILE: {}", args.file);
  fs::path file(args.file);
  std::string file_extension = file.extension().string();
  file.replace_extension("");
  if (args.sequence)
    file.append(std::to_string(args.frame));

  std::vector<std::shared_ptr<ObjectBase>> objects = scene::get_visible();
  if (objects.size() == 0) {
    LWARN("No visible object present in scene");
  }

  image::Image shaded(args.res_width, args.res_height);
  LDEBUG("WRITE: {} -> {}", file.string(),
         file.replace_extension(file_extension).string());
  shaded.write(file.replace_extension(file_extension));

  return true;
}
