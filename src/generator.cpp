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
      std::cout << match.size() << "?\n";
      std::cout << match[0].str() << ':' << match[0].matched << '\n';
      std::cout << match[1].str() << ':' << match[1].matched << '\n';
      // TODO add visit to format correctly for every type
      fmt.replace(match[0].first, match[0].second, "REP");
    }
  }
  return fmt;
}
