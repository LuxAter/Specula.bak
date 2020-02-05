#ifndef SPECULA_FILESYSTEM_HPP_
#define SPECULA_FILESYSTEM_HPP_

#include <functional>

#include <ghc/filesystem.hpp>

namespace specula {
namespace fs {
using namespace ghc::filesystem;
} // namespace fs
} // namespace specula

namespace std {
template <> struct hash<specula::fs::path> {
  std::size_t operator()(const specula::fs::path& p) const noexcept {
    return specula::fs::hash_value(p);
  }
};
} // namespace std

#endif // SPECULA_FILESYSTEM_HPP_
