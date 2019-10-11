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
