#ifndef SPECULA_OPENCL_HPP_
#define SPECULA_OPENCL_HPP_

#include "geometry/geometry.hpp"
#include "primatives/primatives.hpp"

namespace specula {
namespace opencl {
void log_info();
std::function<std::vector<intersect>(std::vector<ray>)>
generate_function(std::vector<std::shared_ptr<specula::Primative>> objs);
} // namespace opencl
} // namespace specula

#endif // SPECULA_OPENCL_HPP_
