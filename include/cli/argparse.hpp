#ifndef SPECULA_CLI_ARGPARSE_HPP_
#define SPECULA_CLI_ARGPARSE_HPP_

#include <map>
#include <string>
#include <vector>

namespace specula {
namespace cli {
struct Value {
  enum ValueType { BOOL, NUMBER, STRING };
  Value() : type_(BOOL), value(), implicit_value(), count(0) {}
  Value(const ValueType &type)
      : type_(type), value(), implicit_value(), count(0) {}
  Value(const char *def)
      : type_(STRING), value(def), implicit_value(), count(0) {}
  Value(const char *imp, const char *def)
      : type_(STRING), value(def), implicit_value(imp), count(0) {}
  Value(const std::string &def)
      : type_(STRING), value(def), implicit_value(), count(0) {}
  Value(const std::string &imp, const std::string &def)
      : type_(STRING), value(def), implicit_value(imp), count(0) {}
  Value(const int &def)
      : type_(NUMBER), value(std::to_string(def)), implicit_value(), count(0) {}
  Value(const int &imp, const int &def)
      : type_(NUMBER), value(std::to_string(def)),
        implicit_value(std::to_string(imp)), count(0) {}
  Value(const double &def)
      : type_(NUMBER), value(std::to_string(def)), implicit_value(), count(0) {}
  Value(const double &imp, const double &def)
      : type_(NUMBER), value(std::to_string(def)),
        implicit_value(std::to_string(imp)), count(0) {}
  Value(const bool &def)
      : type_(BOOL), value(std::to_string(def)), implicit_value(), count(0) {}
  Value(const bool &imp, const bool &def)
      : type_(BOOL), value(std::to_string(def)),
        implicit_value(std::to_string(imp)), count(0) {}

  Value implicit(const char *val) {
    this->implicit_value = val;
    return *this;
  }
  Value implicit(const std::string &val) {
    this->implicit_value = val;
    return *this;
  }
  Value implicit(const int &val) {
    this->implicit_value = std::to_string(val);
    return *this;
  }
  Value implicit(const double &val) {
    this->implicit_value = std::to_string(val);
    return *this;
  }
  Value implicit(const bool &val) {
    this->implicit_value = std::to_string(val);
    return *this;
  }

  bool valdate() {
    if (type_ == BOOL) {
      if (value == "0" || value == "1")
        return true;
      else
        return false;
    }
    return true;
  }
  template <typename _T>
  typename std::enable_if<std::is_floating_point<_T>::value, _T>::type
  as() const {
    return static_cast<_T>(stold(value));
  }
  template <typename _T>
  typename std::enable_if<std::is_unsigned<_T>::value, _T>::type as() const {
    return static_cast<_T>(stoull(value));
  }
  template <typename _T>
  typename std::enable_if<
      std::is_integral<_T>::value && !std::is_unsigned<_T>::value, _T>::type
  as() const {
    return static_cast<_T>(stoll(value));
  }
  template <typename _T>
  typename std::enable_if<std::is_same<_T, std::string>::value, _T>::type
  as() const {
    return value;
  }
  template <typename _T>
  typename std::enable_if<
      !std::is_floating_point<_T>::value && !std::is_integral<_T>::value &&
          !std::is_unsigned<_T>::value && !std::is_same<_T, std::string>::value,
      _T>::type
  as() const {
    return _T(value);
  }

  ValueType type_;
  std::string value, implicit_value;
  int count;
};

class ArgumentParser {
public:
  void add_option(const std::string &name, std::string help = "",
                  Value val = Value(false), bool positional = false);
  void add_option(const std::string &name, std::string help,
                  Value::ValueType type, bool positional = false);
  std::map<std::string, Value> parse(int argc, char *argv[]);
  void display_usage();
  void display_help();

private:
  std::string exe_;
  std::map<char, std::string> name_map_;
  std::map<std::string, Value> options_;
  std::map<std::string, std::string> help_;
  std::vector<std::string> positional_;
};

typedef std::map<std::string, Value> ParseResult;

} // namespace cli
} // namespace specula

#endif // SPECULA_CLI_ARGPARSE_HPP_
