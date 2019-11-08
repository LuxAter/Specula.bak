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
#include "object/object.hpp"
#include "math/math.hpp"
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

  specula::mat<double, 2> mat2(1.0, 2.0, 3.0, 4.0);

  std::vector<std::shared_ptr<specula::object::Object>> objs;
  std::vector<std::shared_ptr<specula::object::Object>> *objs_ptr = &objs;

  sol::state lua;

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

  lua.script_file(specula::cli::script_source);

  LDEBUG("OBJS: {}", objs.size());
  for (auto &obj : objs) {
    LDEBUG("RAD {}",
           std::dynamic_pointer_cast<specula::object::Sphere>(obj)->radius);
  }

  specula::image::Image img(specula::cli::resolution);
  img.write(specula::cli::output_path);
  return 0;
}
