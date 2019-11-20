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

#ifndef SPECULA_VARIANT_HPP_
#define SPECULA_VARIANT_HPP_
#if defined(__cplusplus) && __cplusplus >= 201703L && defined(__has_include)
#if __has_include(<variant>)
#define MPARK_USE_STD_VARIANT
#include <variant>
namespace specula {
template <typename... _ARGS> using variant = std::variant<_ARGS...>;
template <typename _R, typename... _ARGS> inline _R visit(_ARGS... args) {
  return std::visit(args...);
}
} // namespace specula
#endif
#endif
#ifndef MPARK_USE_STD_VARIANT
#include <mpark/variant.hpp>
namespace specula {
template <typename... _ARGS> using variant = mpark::variant<_ARGS...>;
template <typename _R, typename... _ARGS> inline _R visit(_ARGS... args) {
  return mpark::visit(args...);
}
} // namespace specula
#endif
#endif // SPECULA_VARIANT_HPP_
