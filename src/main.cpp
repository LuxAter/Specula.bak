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

#include "generator.hpp"
#include "specula.hpp"

#include "cli.hpp"

int main(int argc, char *argv[]) {
  args_t args = parse_args(argc, argv);
  if (!args.valid)
    return 0;
  specula::logger::initalize_logger(args.verbosity);
  LINFO("Specula v{}.{}.{}", SPECULA_VERSION_MAJOR, SPECULA_VERSION_MINOR,
        SPECULA_VERSION_PATCH);

  // Cornell Box
  specula::set_camera_pos(2.78, 2.73, -8.00);
  specula::set_camera_direction(0.0, 0.0, 1.0);
  specula::set_camera_up(0.0, 1.0, 0.0);

  specula::Material light = specula::Material::Emissive();
  specula::Material white = specula::Material::Diffuse(1.0, 1.0, 1.0);
  specula::Material red = specula::Material::Diffuse(1.0, 0.0, 0.0);
  specula::Material green = specula::Material::Diffuse(0.0, 1.0, 0.0);
  specula::Material blue = specula::Material::Diffuse(0.0, 0.0, 1.0);
  specula::Material mirror = specula::Material::Specular();
  specula::Material glass = specula::Material::Transparent(1.5);

  specula::Plane(0.0, 1.0, 0.0, 0.0)->set_material(white);    // FLOOR
  specula::Plane(0.0, -1.0, 0.0, 5.5)->set_material(light);   // CEILING
  specula::Plane(0.0, 0.0, 1.0, 8.1)->set_material(white);    // FRONT WALL
  specula::Plane(0.0, 0.0, -1.0, 5.592)->set_material(green); // BACK WALL
  specula::Plane(1.0, 0.0, 0.0, 0.0)->set_material(blue);     // RIGHT WALL
  specula::Plane(-1.0, 0.0, 0.0, 5.528)->set_material(red);   // LEFT WALL

  // specula::Box(1.0, 1.0, 1.0)
  //     ->translate(2.75, 1.5, 1.0)
  //     ->set_material(glass);
  specula::Sphere(2.0)
      ->translate(3.528, 2.0, 3.592)
      ->set_material(glass); // LARGE SPHERE
  specula::Sphere(1.0)
      ->translate(1.0, 1.0, 0.5)
      ->set_material(glass); // SMALL SPHERE

  specula::render(specula::RendererArgs()
                      .file(args.output_path)
                      .spp(args.spp)
                      .min_bounces(args.min_bounces)
                      .tile_size(args.tile_size)
                      .threads(args.threads)
                      .res_width(args.res_width)
                      .res_height(args.res_height)
                      .albedo(args.render_albedo)
                      .normal(args.render_normal)
                      .depth(args.render_depth)
                      .denoise(args.denoise)
                      .fov(args.fov)
                      .build());

  return 0;
}
