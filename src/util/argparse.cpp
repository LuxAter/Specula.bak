#include "argparse.hpp"

#include <map>
#include <string>
#include <variant>
#include <vector>

#include <iostream>

namespace specula::argparse {
std::vector<Option> options_;
}  // namespace specula::argparse

void specula::argparse::add_argument(char short_name, std::string long_name,
                                     std::string help) {
  options_.push_back({short_name, long_name, help});
  options_.back().val = false;
  options_.back().type = BOOL;
}
void specula::argparse::add_argument(char short_name, std::string long_name,
                                     bool val, std::string help) {
  options_.push_back({short_name, long_name, help});
  options_.back().val = val;
  options_.back().type = BOOL;
}
void specula::argparse::add_argument(char short_name, std::string long_name,
                                     const char* val, std::string help) {
  options_.push_back({short_name, long_name, help});
  options_.back().val = std::string(val);
  options_.back().type = STRING;
}
void specula::argparse::add_argument(char short_name, std::string long_name,
                                     std::string val, std::string help) {
  options_.push_back({short_name, long_name, help});
  options_.back().val = val;
  options_.back().type = STRING;
}
void specula::argparse::add_argument(char short_name, std::string long_name,
                                     int val, std::string help) {
  options_.push_back({short_name, long_name, help});
  options_.back().val = val;
  options_.back().type = INT;
}
void specula::argparse::add_argument(char short_name, std::string long_name,
                                     double val, std::string help) {
  options_.push_back({short_name, long_name, help});
  options_.back().val = val;
  options_.back().type = DOUBLE;
}
std::map<std::string, specula::argparse::Variable> specula::argparse::parse(
    int argc, char** argv) {
  std::vector<std::string> args;
  for (int i = 1; i < argc; ++i) {
    std::string carg(argv[i]);
    if (carg.find('=') != std::string::npos) {
      if (carg[1] == '-') {
        args.push_back(carg.substr(0, carg.find('=')));
      } else {
        for (std::size_t j = 1; j < carg.find('='); ++j) {
          args.push_back(std::string("-") + carg[j]);
        }
      }
      args.push_back(carg.substr(carg.find('=') + 1));
    } else if (carg[1] == '-') {
      args.push_back(carg);
    } else if (carg[0] == '-') {
      for (std::size_t j = 1; j < carg.size(); ++j) {
        args.push_back(std::string("-") + carg[j]);
      }
    } else {
      args.push_back(carg);
    }
  }
  std::map<std::string, Variable> opts;
  for (auto& opt : options_) {
    opts[opt.long_name] = Variable{opt.type, opt.val};
  }
  for (std::size_t i = 0; i < args.size(); ++i) {
    for (auto& opt : options_) {
      if ((args[i][1] == opt.short_name && args[i].size() == 2) ||
          args[i] == "--" + opt.long_name) {
        if (opt.type == BOOL) {
          opts[opt.long_name].val = !std::get<bool>(opt.val);
        } else if (args.size() > i + 1) {
          if (opt.type == STRING) {
            opts[opt.long_name].val = args[i + 1];
          } else if (opt.type == INT) {
            opts[opt.long_name].val = std::stoi(args[i + 1]);
          } else if (opt.type == DOUBLE) {
            opts[opt.long_name].val = std::stod(args[i + 1]);
          }
          i++;
        } else {
          printf("Argument %s requires an argument!\n", args[i].c_str());
          exit(-1);
        }
        break;
      }
    }
  }
  return opts;
}
void specula::argparse::print_help() { exit(0); }
