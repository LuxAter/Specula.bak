#include "specula/core.hpp"

#include <cmath>
#include <filesystem>
#include <optional>
#include <thread>

#include "specula/image.hpp"
#include "specula/log.hpp"
#include "specula/scene.hpp"
#include "specula/thread.hpp"

#include "cpu_render.hpp"

bool specula::render(const Scene &scene, const RenderArgs &args) {
  std::filesystem::path file(args.file);
  const std::string file_extension = file.extension().string();
  file.replace_extension("");
  if (args.sequence)
    file.append(std::to_string(args.frame));
  file.replace_extension(file_extension);

  std::vector<std::shared_ptr<Object>> objects = scene.get_visible();
  if (objects.size() == 0) {
    LWARN("No visible objects present in scene");
  }
  bool render_status = false;
  std::shared_ptr<Image> img =
      std::make_shared<Image>(args.res_width, args.res_height);
#ifdef __GPU__
  if (std::any_of(
          objects.begin(), objects.end(),
          [](const std::shared_ptr<Object> &o) { return !o->gpu_enabled(); })) {
    LERROR("Not all objects are GPU enabled, defaulting to CPU renderer");
    if (std::any_of(objects.begin(), objects.end(),
                    [](const std::shared_ptr<Object> &o) {
                      return !o->cpu_enabled();
                    })) {
      LERROR("Not all objects are CPU enabled, aborting");
      return false;
    } else {
      cpu::render(img, scene, args);
    }
  } else {
  }
#else
  if (std::any_of(
          objects.begin(), objects.end(),
          [](const std::shared_ptr<Object> &o) { return !o->cpu_enabled(); })) {
    LERROR("Not all objects are CPU enabled, aborting");
    return false;
  } else {
    cpu::render(img, scene, args);
  }
#endif
  img->write(file.string());
  return render_status;
}