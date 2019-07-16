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

#include <cstdlib>
#include <iostream>

#include <chrono>
#include <thread>

#include "specula.hpp"
#include "version.hpp"

using namespace specula;

bool test_save(unsigned i) {
  image::Image img(500, 5000);
  return img.save(fmt::fmt("img/{}.{}", i, "png"));
}

int main(int argc, char *argv[]) {
  cli::ArgumentParser parser;
  parser.add_option("h,help", "Displays this help message");
  parser.add_option("f,frames", "Number of frames to render", cli::Value(50));
  cli::ParseResult args = parser.parse(argc, argv);

  if (args["help"].count > 0) {
    parser.display_usage();
    parser.display_help();
    return 0;
  }

  init();

  unsigned frames = args["frames"].as<unsigned>();

  info("Maximum number of threads for a thread pool: {}",
       std::thread::hardware_concurrency());
  time::time_point start = time::now();
  for (unsigned i = 0; i < frames; ++i) {
    test_save(i);
  }
  log(log::TIMER, "Took {}s to render {} frames",
      time::duration(time::now() - start).count(), frames);
  start = time::now();
  thread::Queue pool(test_save);
  for (unsigned i = 0; i < frames; ++i) {
    pool.push(i);
  }
  pool.wait();
  log(log::TIMER, "Took {}s to render {} frames",
      time::duration(time::now() - start).count(), frames);
  term();
  return 0;
}
