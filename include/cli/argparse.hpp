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
#ifndef SPECULA_CLI_ARGPARSE_HPP_
#define SPECULA_CLI_ARGPARSE_HPP_

#include <regex>
#include <string>

#include <CLI/CLI.hpp>

#include "../util/util.hpp"

namespace specula {
namespace cli {
extern std::string lua_source;
extern std::string output_path;
extern Size<std::size_t> resolution;

int parse_args(int argc, char *argv[]);
} // namespace cli
} // namespace specula

#endif // SPECULA_CLI_ARGPARSE_HPP_
