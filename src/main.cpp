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
#include "script/script.hpp"
#include "version.hpp"

int main(int argc, char *argv[]) {
  int ret = 0;
  if ((ret = specula::cli::parse_args(argc, argv)) > 0) {
    return ret;
  } else if (ret == -1) {
    return 0;
  }
  specula::log::initalize_logger(specula::cli::verbosity);
  LINFO("Specula v{}.{}.{}", SPECULA_VERSION_MAJOR, SPECULA_VERSION_MINOR,
        SPECULA_VERSION_PATCH);

  std::shared_ptr<specula::script::Script> script =
      specula::script::load_script(specula::cli::script_source);

  specula::image::Image img(specula::cli::resolution);
  img.write(specula::cli::output_path);
  return 0;
}
