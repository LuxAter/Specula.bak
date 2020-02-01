#ifndef SPECULA_VARIANT_HPP_
#define SPECULA_VARIANT_HPP_

#include <mpark/variant.hpp>
namespace specula {
template <typename... Types> using variant = mpark::variant<Types...>;
} // namespace specula

#endif // SPECULA_VARIANT_HPP_