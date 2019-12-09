#include "generator.hpp"

#include <map>
#include <regex>
#include <string>

#include <iostream>

#include "math.hpp"
#include "variant.hpp"

std::string specula::format(
    std::string fmt,
    const std::map<std::string, variant<float, glm::vec2, glm::vec3, glm::vec4>>
        &variables) {
  for (auto &var : variables) {
    std::regex key_regex("\\{\\{\\s*" + var.first + "(.[xyzw]+)?\\s*\\}\\}");
    std::smatch match;
    while (std::regex_search(fmt, match, key_regex)) {
      visit(
          [&](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            std::string rep = "";
            if constexpr (std::is_same_v<T, float>) {
              fmt.replace(match[0].first, match[0].second, std::to_string(arg));
            } else if constexpr (std::is_same_v<T, glm::vec2>) {
              std::string_view swizzle =
                  match[1].matched ? match[1].str().substr(1) : "";
              if (swizzle == "")
                rep = "(float2)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + ")";
              else if (swizzle == "x")
                rep = std::to_string(arg.x);
              else if (swizzle == "y")
                rep = std::to_string(arg.y);
              else if (swizzle == "xy")
                rep = "(float2)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + ")";
              else if (swizzle == "xx")
                rep = "(float2)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + ")";
              else if (swizzle == "yx")
                rep = "(float2)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + ")";
              else if (swizzle == "yy")
                rep = "(float2)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + ")";
            } else if constexpr (std::is_same_v<T, glm::vec3>) {
              std::string_view swizzle =
                  match[1].matched ? match[1].str().substr(1) : "";
              if (swizzle == "")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "x")
                rep = std::to_string(arg.x);
              else if (swizzle == "y")
                rep = std::to_string(arg.y);
              else if (swizzle == "z")
                rep = std::to_string(arg.z);
              else if (swizzle == "xx")
                rep = "(float2)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + ")";
              else if (swizzle == "xy")
                rep = "(float2)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + ")";
              else if (swizzle == "xz")
                rep = "(float2)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + ")";
              else if (swizzle == "yx")
                rep = "(float2)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + ")";
              else if (swizzle == "yy")
                rep = "(float2)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + ")";
              else if (swizzle == "yz")
                rep = "(float2)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.z) + ")";
              else if (swizzle == "zx")
                rep = "(float2)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + ")";
              else if (swizzle == "zy")
                rep = "(float2)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + ")";
              else if (swizzle == "zz")
                rep = "(float2)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + ")";
              else if (swizzle == "xxx")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "xxy")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "xxz")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "xyx")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "xyy")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "xyz")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "xzx")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "xzy")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "xzz")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "yxx")
                rep = "(float3)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "yxy")
                rep = "(float3)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "yxz")
                rep = "(float3)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "yyx")
                rep = "(float3)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "yyy")
                rep = "(float3)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "yyz")
                rep = "(float3)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "yzx")
                rep = "(float3)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "yzy")
                rep = "(float3)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "yzz")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "zxx")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "zxy")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "zxz")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "zyx")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "zyy")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "zyz")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "zzx")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "zzy")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "zzz")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.z) + ")";
            } else if constexpr (std::is_same_v<T, glm::vec4>) {
              std::string_view swizzle =
                  match[1].matched ? match[1].str().substr(1) : "";
              if (swizzle == "")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "x")
                rep = std::to_string(arg.x);
              else if (swizzle == "y")
                rep = std::to_string(arg.y);
              else if (swizzle == "z")
                rep = std::to_string(arg.z);
              else if (swizzle == "w")
                rep = std::to_string(arg.z);
              else if (swizzle == "xx")
                rep = "(float2)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + ")";
              else if (swizzle == "xy")
                rep = "(float2)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + ")";
              else if (swizzle == "xz")
                rep = "(float2)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + ")";
              else if (swizzle == "xw")
                rep = "(float2)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + ")";
              else if (swizzle == "yx")
                rep = "(float2)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + ")";
              else if (swizzle == "yy")
                rep = "(float2)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + ")";
              else if (swizzle == "yz")
                rep = "(float2)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.z) + ")";
              else if (swizzle == "yw")
                rep = "(float2)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.w) + ")";
              else if (swizzle == "zx")
                rep = "(float2)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + ")";
              else if (swizzle == "zy")
                rep = "(float2)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + ")";
              else if (swizzle == "zz")
                rep = "(float2)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + ")";
              else if (swizzle == "zw")
                rep = "(float2)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.w) + ")";
              else if (swizzle == "wx")
                rep = "(float2)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.x) + ")";
              else if (swizzle == "wy")
                rep = "(float2)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.y) + ")";
              else if (swizzle == "wz")
                rep = "(float2)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.z) + ")";
              else if (swizzle == "ww")
                rep = "(float2)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.w) + ")";
              else if (swizzle == "xxx")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "xxy")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "xxz")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "xxw")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.w) + ")";
              else if (swizzle == "xyx")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "xyy")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "xyz")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "xyw")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.w) + ")";
              else if (swizzle == "xzx")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "xzy")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "xzz")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "xzw")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.w) + ")";
              else if (swizzle == "xwx")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "xwy")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "xwz")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "xww")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.w) + ")";
              else if (swizzle == "yxx")
                rep = "(float3)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "yxy")
                rep = "(float3)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "yxz")
                rep = "(float3)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "yxw")
                rep = "(float3)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.w) + ")";
              else if (swizzle == "yyx")
                rep = "(float3)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "yyy")
                rep = "(float3)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "yyz")
                rep = "(float3)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "yyw")
                rep = "(float3)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.w) + ")";
              else if (swizzle == "yzx")
                rep = "(float3)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "yzy")
                rep = "(float3)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "yzz")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "yzw")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.w) + ")";
              else if (swizzle == "ywx")
                rep = "(float3)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "ywy")
                rep = "(float3)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "ywz")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "yww")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.w) + ")";
              else if (swizzle == "zxx")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "zxy")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "zxz")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "zxw")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.w) + ")";
              else if (swizzle == "zyx")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "zyy")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "zyz")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "zyw")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.w) + ")";
              else if (swizzle == "zzx")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "zzy")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "zzz")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "zzw")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.w) + ")";
              else if (swizzle == "zwx")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "zwy")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "zwz")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "zww")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.w) + ")";
              else if (swizzle == "wxx")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "wxy")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "wxz")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "wxw")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.w) + ")";
              else if (swizzle == "wyx")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "wyy")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "wyz")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "wyw")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.w) + ")";
              else if (swizzle == "wzx")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "wzy")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "wzz")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "wzw")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.w) + ")";
              else if (swizzle == "wwx")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.x) + ")";
              else if (swizzle == "wwy")
                rep = "(float3)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.y) + ")";
              else if (swizzle == "wwz")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.z) + ")";
              else if (swizzle == "www")
                rep = "(float3)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.w) + ")";
              else if (swizzle == "xxxx")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "xxxy")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "xxxz")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "xxxw")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "xxyx")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "xxyy")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "xxyz")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "xxyw")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "xxzx")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "xxzy")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "xxzz")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "xxzw")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "xxwx")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "xxwy")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "xxwz")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "xxww")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "xyxx")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "xyxy")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "xyxz")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "xyxw")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "xyyx")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "xyyy")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "xyyz")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "xyyw")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "xyzx")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "xyzy")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "xyzz")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "xyzw")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "xywx")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "xywy")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "xywz")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "xyww")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "xzxx")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "xzxy")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "xzxz")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "xzxw")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "xzyx")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "xzyy")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "xzyz")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "xzyw")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "xzzx")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "xzzy")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "xzzz")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "xzzw")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "xzwx")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "xzwy")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "xzwz")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "xzww")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "xwxx")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "xwxy")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "xwxw")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "xwxw")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "xwyx")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "xwyy")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "xwyz")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "xwyw")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "xwzx")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "xwzy")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "xwzz")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "xwzw")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "xwwx")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "xwwy")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "xwwz")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "xwww")
                rep = "(float4)(" + std::to_string(arg.x) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "yxxx")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "yxxy")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "yxxz")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "yxxw")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "yxyx")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "yxyy")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "yxyz")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "yxyw")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "yxzx")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "yxzy")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "yxzz")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "yxzw")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "yxwx")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "yxwy")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "yxwz")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "yxww")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "yyxx")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "yyxy")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "yyxz")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "yyxw")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "yyyx")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "yyyy")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "yyyz")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "yyyw")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "yyzx")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "yyzy")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "yyzz")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "yyzw")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "yywx")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "yywy")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "yywz")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "yyww")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "yzxx")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "yzxy")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "yzxz")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "yzxw")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "yzyx")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "yzyy")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "yzyz")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "yzyw")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "yzzx")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "yzzy")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "yzzz")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "yzzw")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "yzwx")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "yzwy")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "yzwz")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "yzww")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "ywxx")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "ywxy")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "ywxw")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "ywxw")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "ywyx")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "ywyy")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "ywyz")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "ywyw")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "ywzx")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "ywzy")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "ywzz")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "ywzw")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "ywwx")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "ywwy")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "ywwz")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "ywww")
                rep = "(float4)(" + std::to_string(arg.y) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "zxxx")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "zxxy")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "zxxz")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "zxxw")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "zxyx")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "zxyy")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "zxyz")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "zxyw")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "zxzx")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "zxzy")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "zxzz")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "zxzw")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "zxwx")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "zxwy")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "zxwz")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "zxww")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "zyxx")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "zyxy")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "zyxz")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "zyxw")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "zyyx")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "zyyy")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "zyyz")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "zyyw")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "zyzx")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "zyzy")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "zyzz")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "zyzw")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "zywx")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "zywy")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "zywz")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "zyww")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "zzxx")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "zzxy")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "zzxz")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "zzxw")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "zzyx")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "zzyy")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "zzyz")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "zzyw")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "zzzx")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "zzzy")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "zzzz")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "zzzw")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "zzwx")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "zzwy")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "zzwz")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "zzww")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "zwxx")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "zwxy")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "zwxw")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "zwxw")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "zwyx")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "zwyy")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "zwyz")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "zwyw")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "zwzx")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "zwzy")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "zwzz")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "zwzw")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "zwwx")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "zwwy")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "zwwz")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "zwww")
                rep = "(float4)(" + std::to_string(arg.z) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "wxxx")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "wxxy")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "wxxz")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "wxxw")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "wxyx")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "wxyy")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "wxyz")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "wxyw")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "wxzx")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "wxzy")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "wxzz")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "wxzw")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "wxwx")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "wxwy")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "wxwz")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "wxww")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.x) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "wyxx")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "wyxy")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "wyxz")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "wyxw")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "wyyx")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "wyyy")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "wyyz")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "wyyw")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "wyzx")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "wyzy")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "wyzz")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "wyzw")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "wywx")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "wywy")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "wywz")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "wyww")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.y) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "wzxx")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "wzxy")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "wzxz")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "wzxw")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "wzyx")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "wzyy")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "wzyz")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "wzyw")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "wzzx")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "wzzy")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "wzzz")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "wzzw")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "wzwx")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "wzwy")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "wzwz")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "wzww")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.z) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "wwxx")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "wwxy")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "wwxw")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "wwxw")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.x) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "wwyx")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "wwyy")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "wwyz")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "wwyw")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.y) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "wwzx")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "wwzy")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "wwzz")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "wwzw")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.z) +
                      "," + std::to_string(arg.w) + ")";
              else if (swizzle == "wwwx")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.x) + ")";
              else if (swizzle == "wwwy")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.y) + ")";
              else if (swizzle == "wwwz")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.z) + ")";
              else if (swizzle == "wwww")
                rep = "(float4)(" + std::to_string(arg.w) + "," +
                      std::to_string(arg.w) + "," + std::to_string(arg.w) +
                      "," + std::to_string(arg.w) + ")";
            }
            fmt.replace(match[0].first, match[0].second, rep);
          },
          var.second);
    }
  }
  return fmt;
}
