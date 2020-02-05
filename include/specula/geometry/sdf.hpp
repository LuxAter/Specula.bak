#ifndef SPECULA_SDF_HPP_
#define SPECULA_SDF_HPP_

#include <map>
#include <string>
#include <variant>

#include <fmt/format.h>
#include <glm/glm.hpp>

namespace specula {
namespace geometry {
template <typename... T> class Sdf {
public:
  Sdf() : kernel_source(), args() {}
  virtual ~Sdf() {}

  std::string get_opencl() const;

protected:
  std::string format_source_str() const {
    std::string formatted = kernel_source;
    for (auto& argument : args) {
      formatted =
          fmt::format(formatted, fmt::arg(argument.first, argument.second));
    }
    return formatted;
  }
  std::string kernel_source;
  std::map<std::string, std::variant<T...>> args;
};
} // namespace geometry
} // namespace specula

#endif // SPECULA_SDF_HPP_