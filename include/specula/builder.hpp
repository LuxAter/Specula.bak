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

#define GET_VAR(class, type, name, default)                                    \
public:                                                                        \
  inline type &get_##name() { return name##_; }                                \
  inline const type &get_##name() const { return name##_; }                    \
                                                                               \
protected:                                                                     \
  type name##_ = default;

#define GET_PVAR(class, type, name, default)                                   \
public:                                                                        \
  inline type &get_##name() { return name; }                                   \
  inline const type &get_##name() const { return name; }                       \
  type name = default;

#endif // SPECULA_BUILDER_HPP_