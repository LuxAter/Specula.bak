#ifndef SPECULA_BUILDER_HPP_
#define SPECULA_BUILDER_HPP_

#define BUILD_VAR(class, type, name, default)                                  \
public:                                                                        \
  inline class &set_##name(const type &v) {                                    \
    name##_ = v;                                                               \
    return *this;                                                              \
  }                                                                            \
  inline type &get_##name() { return name##_; }                                \
  inline const type &get_##name() const { return name##_; }                    \
                                                                               \
protected:                                                                     \
  type name##_ = default;

#define BUILD_PVAR(class, type, name, default)                                 \
public:                                                                        \
  inline class &set_##name(const type &v) {                                    \
    name = v;                                                                  \
    return *this;                                                              \
  }                                                                            \
  inline type &get_##name() { return name; }                                   \
  inline const type &get_##name() const { return name; }                       \
  type name = default;

#define PBUILD_VAR(class, type, name, default)                                 \
public:                                                                        \
  inline std::shared_ptr<class> set_##name(const type &v) {                    \
    name##_ = v;                                                               \
    return shared_from_this();                                                 \
  }                                                                            \
  inline type &get_##name() { return name##_; }                                \
  inline const type &get_##name() const { return name##_; }                    \
                                                                               \
protected:                                                                     \
  type name##_ = default;

#define PBUILD_PVAR(class, type, name, default)                                \
public:                                                                        \
  inline std::shared_ptr<class> set_##name(const type &v) {                    \
    name = v;                                                                  \
    return shared_from_this();                                                 \
  }                                                                            \
  inline type &get_##name() { return name; }                                   \
  inline const type &get_##name() const { return name; }                       \
  type name = default;

#endif // SPECULA_BUILDER_HPP_