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
  image::Image albedo(0, 0), depth(0, 0), normal(0, 0);
  if (args.render_albedo || args.denoise)
    albedo = image::Image(args.res_width, args.res_height);
  if (args.render_depth || args.denoise)
    depth = image::Image(args.res_width, args.res_height);
  if (args.render_normal || args.denoise)
    normal = image::Image(args.res_width, args.res_height);

  // RENDER THINGS

  fs::path shaded_file = file;
  shaded.write(shaded_file.replace_extension(file_extension));
  if (args.render_albedo) {
    fs::path albedo_file = file;
    albedo.write(
        albedo_file.concat("-albedo").replace_extension(file_extension));
  }
  if (args.render_depth) {
    fs::path depth_file = file;
    depth.normalize();
    depth.write(depth_file.concat("-depth").replace_extension(file_extension));
  }
  if (args.render_normal) {
    fs::path normal_file = file;
    normal.abs();
    normal.normalize();
    normal.write(
        normal_file.concat("-normal").replace_extension(file_extension));
  }

  return true;
}
