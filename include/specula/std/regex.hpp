#ifndef SPECULA_REGEX_HPP_
#define SPECULA_REGEX_HPP_

#include <re2/re2.h>

namespace specula {
namespace regex {
typedef re2::RE2 Regex;
typedef re2::Prog Prog;
typedef re2::Regexp Regexp;
} // namespace regex
} // namespace specula

#endif // SPECULA_REGEX_HPP_