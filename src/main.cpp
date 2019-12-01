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

#include "specula.hpp"

#include "cli.hpp"

int main(int argc, char *argv[]) {
  args_t args = parse_args(argc, argv);
  if (!args.valid)
    return 0;
  specula::logger::initalize_logger(args.verbosity);
  LINFO("Specula v{}.{}.{}", SPECULA_VERSION_MAJOR, SPECULA_VERSION_MINOR,
        SPECULA_VERSION_PATCH);
  specula::set_camera_fov(args.fov);

  specula::Sphere sph(2.0f);
  std::cout << sph.radius << ":" << sph.get_float("radius") << ":"
            << specula::scene::objects.front()->get_float("radius") << "\n";
  sph.radius = 3.0f;
  std::cout << sph.radius << ":" << sph.get_float("radius") << ":"
            << specula::scene::objects.front()->get_float("radius") << "\n";
  sph.get_float("radius") = 4.0f;
  std::cout << sph.radius << ":" << sph.get_float("radius") << ":"
            << specula::scene::objects.front()->get_float("radius") << "\n";
  specula::scene::objects.front()->get_float("radius") = 5.0f;
  std::cout << sph.radius << ":" << sph.get_float("radius") << ":"
            << specula::scene::objects.front()->get_float("radius") << "\n";
  return 0;
}
