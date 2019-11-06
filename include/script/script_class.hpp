#ifndef SPECULA_SCRIPT_CLASS_HPP_
#define SPECULA_SCRIPT_CLASS_HPP_

#include <string>

#include "../filesystem.hpp"

namespace specula {
  namespace script {
    class Script{
      public:
        Script(const fs::path& script_path): script_path_(script_path){}
        virtual ~Script(){}
        virtual bool exec();
      protected:
        fs::path script_path_;
      private:
    };
  } // namespace script
} // namespace specula

#endif  // SPECULA_SCRIPT_CLASS_HPP_
