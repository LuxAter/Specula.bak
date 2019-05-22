#ifndef SPECULA_UTIL_ARGPARSE_HPP_
#define SPECULA_UTIL_ARGPARSE_HPP_

#include <map>
#include <string>
#include <variant>
#include <vector>

namespace specula {
namespace argparse {
  enum OptType { BOOL, STRING, INT, DOUBLE };
  struct Option {
    char short_name;
    std::string long_name;
    std::string help;
    std::variant<bool, std::string, int, double> val;
    OptType type;
  };
  struct Variable {
    bool get_bool() { return std::get<bool>(val); }
    std::string get_string() { return std::get<std::string>(val); }
    int get_int() { return std::get<int>(val); }
    double get_double() { return std::get<double>(val); }

    OptType type;
    std::variant<bool, std::string, int, double> val;
  };
  void add_argument(char short_name, std::string long_name, std::string help);
  void add_argument(char short_name, std::string long_name, bool val,
                    std::string help = "");
  void add_argument(char short_name, std::string long_name, const char* val,
                    std::string help);
  void add_argument(char short_name, std::string long_name, std::string val,
                    std::string help);
  void add_argument(char short_name, std::string long_name, int val,
                    std::string help = "");
  void add_argument(char short_name, std::string long_name, double val,
                    std::string help = "");
  std::map<std::string, Variable> parse(int argc, char** argv);
  void print_help();
  extern std::vector<Option> options_;
}  // namespace argparse
}  // namespace specula

#endif  // SPECULA_UTIL_ARGPARSE_HPP_
