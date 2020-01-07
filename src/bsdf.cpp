#include "bsdf.hpp"

#include <memory>

#include <glm/glm.hpp>

#include "ray.hpp"
#include "specula/material.hpp"

constexpr float pow2(const float &v) { return v * v; }
constexpr float pow3(const float &v) { return v * v * v; }
constexpr float pow4(const float &v) { return v * v * v * v; }
constexpr float pow5(const float &v) { return v * v * v * v * v; }

constexpr glm::vec3 normal_to_world(const glm::vec3 &xyz, const glm::vec3 &n) {
  glm::vec3 major_axis;
  if (glm::abs(n.x) < 0.57735026919f) {
    major_axis = glm::vec3(1.0f, 0.0f, 0.0f);
  } else if (glm::abs(n.y) < 0.57735026919f) {
    major_axis = glm::vec3(0.0f, 1.0f, 0.0f);
  } else {
    major_axis = glm::vec3(0.0f, 0.0f, 1.0f);
  }
  const glm::vec3 u = glm::normalize(glm::corss(n, major_axis));
  const glm::vec3 v = glm::cross(n, u);
  const glm::vec3 w = n;
  return u * xyz.x + v * xyz.y + w * xyz.w;
}

specula::ray specula::bsdf::sample(const ray &r,
                                   const std::shared_ptr<Material> &mat,
                                   const glm::vec3 &normal, const float &ep) {
  const auto [theta, phi] =
      D_sample_GGX(); // This is the micro normal with
                      // respect to the macro normal. We need to transform this
                      // to be in world space not macro normal space.
  const glm::vec3 h = normal_to_world(glm::vec3(std::sin(theta) * std::cos(phi),
                                                std::sin(theta) * std::sin(phi),
                                                std::cos(theta)),
                                      normal);
  return glm::reflect(r.d, h);
}
glm::vec3 specula::bsdf::evaluate(const glm::vec3 &L, const glm::vec3 &V,
                                  const glm::vec3 &N,
                                  const std::shared_ptr<Material> &mat) {
  const float NdotL = glm::dot(N, L); // cos theta_l
  const float NdotV = glm::dot(N, V); // cos theta_v
  if (NdotL < 0 || NdotV < 0)
    return glm::vec3(0.0f);

  glm::vec3 H = glm::normalize(L + V);
  float NdotH = glm::dot(N, H); // cos theta_h
  float LdotH = glm::dot(L, H); // cos theta_d
  float VdotH = glm::dot(V, H);
  float alpha = mat->roughness * mat->roughness;
  float fd90 = 0.5 + 2 * LdotH * LdotH * mat->roughness;
  return diff_disney() + (D_GGX(h) * F_schlick(v, h) * G_GGX(v) * G_GGX(l)) /
                             (4 * NdotL * NdotV);
}

glm::vec3 specular::bsdf::diff_disney() {
  const float fd90 = 0.5 + 2 * LdotH * LdotH * mat->roughness;
  return mat->base_color / M_PI * (1.0f + (fd90 - 1.0f) * pow5(1.0f - NdotL)) *
         (1.0f + (fd90 - 1.0f) * pow5(1.0f - NdotV));
}

float specular::bsdf::D_blinn_phong() {
  return 1.0f / (M_PI * alpha * alpha) *
         std::pow(NdotH, 1 / (alpha * alpha) - 2.0f);
}
float specular::bsdf::D_beckmann() {
  return 1.0f / (M_PI * alpha * alpha * pow4(NdotH)) *
         std::exp((NdotH * NdotH - 1.0f) / (alpha * alpha * NdotH * NdotH));
}
float specular::bsdf::D_GGX() {
  return alpha * alpha /
         (M_PI * pow2(NdotH * NdotH * (alpha * alpha - 1.0f) + 1.0f));
}
float specular::bsdf::D_GGX_aniso() {
  return 1.0f / (M_PI * alpha_x * alpha_y) * 1.0f /
         pow2(pow2(glm::dot(X, H) / alpha_x) + pow2(glm::dot(Y, H) / alpha_y) +
              pow2(NdotH));
}

float specular::bsdf::G_implicit() { return NdotL * NdotV; }
float specular::bsdf::G_neumann() {
  return NdotL * NdotV / std::max(NdotL, NdotV);
}
float specular::bsdf::G_cook_torrance() {
  return std::min(1.0f, std::min(2.0f * NdotH * NdotV / VdotH,
                                 2.0f * NdotH * NdotL / VdotH));
}
float specular::bsdf::G_kelemen() { return NdotL * NdotV / pow2(VdotH); }
float specular::bsdf::G_smith_beckmann() {
  const float c = NdotV / (alpha * std::sqrt(1.0f - NdotV * NdotV));
  return c >= 1.6f ? 1.0f : ((3.535f*c+2.181f*c*c)/(1.0f+2.276f*c+2.577f*c*c);
}
float specular::bsdf::G_GGX() {
  return (2.0f * NdotV) /
         (NdotV +
          std::sqrt(alpha * alpha + (1.0f - alpha * alpha) * NdotV * NdotV));
}
float specular::bsdf::G_schlick_beckmann() {
  const float k = alpha * std::sqrt(2.0f / M_PI);
  return NdotV / (NdotV * (1.0f - k) + k);
}
float specular::bsdf::G_schlick_GGX() {
  const float k = alpha / 2.0f;
  return NdotV / (NdotV * (1.0f - k) + k);
}

float specular::bsdf::F_none() { return F0; }
float specular::bsdf::F_schlick() {
  return F0 + (1.0f - F0) * pow5(1.0f - NdotH);
}
float specular::bsdf::F_cook_torrance() {
  const float eta = (1.0f + std::sqrt(F0)) / (1.0f - std::sqrt(F0));
  const float c = VdotH;
  const float g = std::sqrt(eta * eta + c * c - 1.0f);
  return 1.5 * pow2((g - c) / (g + c)) *
         (1.0f + pow2(((g + c) * c - 1.0f) / ((g - c) * c + 1.0f)));
}

std::array<float, 2> specular::bsdf::D_sample_GGX() {
  const float ep = frand();
  const float phi = frand(0.0f, 2.0f * M_PI);
  const float theta = std::atan(alpha * std::sqrt(ep / (1.0f - ep)));
  return std::array<float, 2>{theta, phi};
}
std::array<float, 2> speular::bsdf::D_sample_beckmann() {
  const float ep = frand();
  const float phi = frand(0.0f, 2.0f * M_PI);
  const float theta = std::atan(-(alpha * alpha) * std::log(1 - ep));
  return std::array<float, 2>{theta, phi};
}
std::array<float, 2> specular::bsdf::D_sample_blinn() {
  const float ep = frand();
  const float phi = frand(0.0f, 2.0f * M_PI);
  const float theta = 1.0f / std::acos(std::pow(ep, alpha + 1));
  return std::array<float, 2>{theta, phi};
}
