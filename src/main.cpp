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

int main() {
  init();
  time::time_point start = time::now();
  time::sleep(1.2);
  time::time_point stop = time::now();
  time::duration diff = stop - start;
  log(log::TIMER, "Slept for %lfs", diff.count());
  term();
  return 0;
}
