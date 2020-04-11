#ifndef SPECULA_CORE_CAMERA_HPP_
#define SPECULA_CORE_CAMERA_HPP_

#include "specula/global.hpp"
#include "geometry.hpp"

namespace specula
{
  struct CameraSample {
    Point2f film;
    Point2f lens;
    Float time;
  };
} /* specula */ 

#endif /* end of include guard: SPECULA_CORE_CAMERA_HPP_ */
