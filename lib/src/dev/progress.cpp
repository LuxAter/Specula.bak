#include "specula/dev/progress.hpp"
#include <string_view>

namespace specula {
std::vector<std::function<void(const std::size_t &, const std::string_view &,
                               const std::string_view &, const std::size_t &,
                               const std::size_t &, const float &)>>
    progress_reporter_default_callbacks;
}
