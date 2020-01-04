#include "specula/specula.hpp"

#include <array>
#include <filesystem>

#include "specula/version.hpp"

#include "cpu_renderer.hpp"

std::array<unsigned, 3> specula::get_version() {
  return {SPECULA_VERSION_MAJOR, SPECULA_VERSION_MINOR, SPECULA_VERSION_PATCH};
}

bool specula::render(const std::string &file_path, const unsigned &frame,
                     const Settings &settings, const Scene &scene) {
  std::filesystem::path fp(file_path);
  const std::filesystem::path ext = fp.extension();
  fp.replace_extension("");
  fp.append(std::to_string(frame));
  fp.replace_extension(ext);
  LTRACE("Render to file sequence \"{}\"", fp.string());
  return render(settings, scene).write(fp.string());
}
bool specula::render(const std::string &file_path, const Settings &settings,
                     const Scene &scene) {
  LTRACE("Render to file \"{}\"", file_path);
  return render(settings, scene).write(file_path);
}
specula::Image specula::render(const Settings &settings, const Scene &scene) {
  LINFO("Specula v{}.{}.{}", SPECULA_VERSION_MAJOR, SPECULA_VERSION_MINOR,
        SPECULA_VERSION_PATCH);
  LINFO("Render Settings: pass: {}", RenderPass_strings[settings.get_pass()]);
  LINFO("                 spp: {}", settings.get_spp());
  LINFO("                 bounces: {}", settings.get_bounces());
  LINFO("                 tile size: {}", settings.get_size());
  LINFO("                 image width: {}", settings.get_width());
  LINFO("                 image height: {}", settings.get_height());
  for(auto & obj : scene.objects) {
    obj->construct();
  }
  return cpu::render(&settings, &scene);
}
