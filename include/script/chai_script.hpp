#ifndef SPECULA_SCRIPT_CHAI_HPP_
#define SPECULA_SCRIPT_CHAI_HPP_

#include <string_view>

#include <chaiscript/chaiscript.hpp>

#include "script_class.hpp"
#include "../filesystem.hpp"

namespace specula {
namespace script {
class ChaiScript : public Script {
  public:
  ChaiScript(const fs::path &script_path);
  ~ChaiScript() {}
  virtual bool exec();
  private:
  chaiscript::ChaiScript chai_;
};
} // namespace script
} // namespace specula

#endif // SPECULA_SCRIPT_CHAI_HPP_
