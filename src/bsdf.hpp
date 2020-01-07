#ifndef SPECULA_BSDF_HPP_
#define SPECULA_BSDF_HPP_

#include <memory>

#include <glm/glm.hpp>

#include "ray.hpp"
#include "specula/material.hpp"

#include "specular/enum.hpp"

namespace specula {
  enum BxDFType {
    BSDF_REFLECTION = 1 << 0,
    BSDF_TRANSMISSION = 1 << 1,
    BSDF_DIFFUSE = 1 << 2,
    BSDF_GLOSSY = 1 << 3,
    BSDF_
  }
  class BxDF {
    public:
      virtual ~BxDf(){}
      Bxdf(BxDfType)
  };
} // namespace specula

#endif // SPECULA_BSDF_HPP_
