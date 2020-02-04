#ifndef SPECULA_REGEX_HPP_
#define SPECULA_REGEX_HPP_

#include <re2/re2.h>

namespace specula {
namespace regex {
  using namespace re2;
  typedef re2::RE2 Regex;
} // namespace regex
} // namespace specula

#endif // SPECULA_REGEX_HPP_
