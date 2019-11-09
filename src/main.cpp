/* Copyright (C)
 * 2019 - Arden Rasmussen
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#include "cli/cli.hpp"
#include "image/image.hpp"
#include "log.hpp"
#include "math/math.hpp"
#include "object/object.hpp"
#include "renderer.hpp"
#include "version.hpp"

#include <sol/sol.hpp>

int main(int argc, char *argv[]) {
  int ret = 0;
  if ((ret = specula::cli::parse_args(argc, argv)) > 0) {
    return ret;
  } else if (ret == -1) {
    return 0;
  }
  specula::logger::initalize_logger(specula::cli::verbosity);
  LINFO("Specula v{}.{}.{}", SPECULA_VERSION_MAJOR, SPECULA_VERSION_MINOR,
        SPECULA_VERSION_PATCH);

  std::vector<std::shared_ptr<specula::object::Object>> objs;
  std::vector<std::shared_ptr<specula::object::Object>> *objs_ptr = &objs;

  sol::state lua;
  std::size_t render_calls = 0;
  std::size_t *render_calls_ptr = &render_calls;

  lua.new_usertype<specula::object::Object>(
      "Object", "translate", &specula::object::Object::translate);

  lua.new_usertype<specula::object::Sphere>(
      "Sphere", "new", sol::factories([objs_ptr](const float &radius) {
        objs_ptr->push_back(std::make_shared<specula::object::Sphere>(radius));
        return std::dynamic_pointer_cast<specula::object::Sphere>(
            objs_ptr->back());
      }),
      "radius", &specula::object::Sphere::radius, sol::base_classes,
      sol::bases<specula::object::Object>());

  lua.set_function("render", [render_calls_ptr, objs]() -> bool {
    specula::fs::path file(specula::cli::output_path);
    specula::fs::path file_name = file.filename().replace_extension(""),
                      file_extension = file.extension();
    file.remove_filename();
    file.append(file_name.string());
    file.append(
        fmt::format("{}{}", *render_calls_ptr, file_extension.string()));
    (*render_calls_ptr)++;
    return specula::renderer::render_frame(file, objs, specula::cli::spp,
                                           specula::cli::fov,
                                           specula::cli::resolution);
  });

  lua.script_file(specula::cli::script_source);

  if (render_calls == 0) {
    return specula::renderer::render_frame(
        specula::fs::path(specula::cli::output_path), objs, specula::cli::spp,
        specula::cli::fov, specula::cli::resolution);
  }

  return 0;
}
