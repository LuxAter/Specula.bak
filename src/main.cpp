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

#include <sol/sol.hpp>

#include "cli.hpp"
#include "lua_binding.hpp"

int main(int argc, char *argv[]) {
  args_t args = parse_args(argc, argv);
  if (!args.valid)
    return 0;
  specula::logger::initalize_logger(args.verbosity);
  LINFO("Specula v{}.{}.{}", SPECULA_VERSION_MAJOR, SPECULA_VERSION_MINOR,
        SPECULA_VERSION_PATCH);

  sol::state lua;
  lua.open_libraries();

  std::size_t render_calls = 0;
  load_bindings(lua);

  lua["render"] = sol::overload([render_calls, args]() mutable {
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
                        .frame(render_calls)
                        .sequence(true)
                        .build());
    render_calls++;
  });

  lua.script_file(args.script_path);

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
