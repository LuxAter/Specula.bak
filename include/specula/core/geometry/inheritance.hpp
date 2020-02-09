#ifndef SPECULA_CORE_GEOMETRY_INHERITANCE_HPP_
#define SPECULA_CORE_GEOMETRY_INHERITANCE_HPP_

#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

#define GLM_FUNC1(name, func, arg1)                                            \
  template <typename T>                                                        \
  inline auto name(const T &arg1)                                              \
      ->typename std::enable_if<                                               \
          std::is_base_of<GlmInheritance, T>::value &&                         \
              std::is_same<typename T::glm_type,                               \
                           decltype(glm::func(arg1.get_glm()))>::value,        \
          T>::type {                                                           \
    return glm::func(arg1.get_glm());                                          \
  }                                                                            \
  template <typename T>                                                        \
  inline auto name(const T &arg1)                                              \
      ->typename std::enable_if<                                               \
          std::is_base_of<GlmInheritance, T>::value &&                         \
              !std::is_same<typename T::glm_type,                              \
                            decltype(glm::func(arg1.get_glm()))>::value,       \
          decltype(glm::func(arg1.get_glm()))>::type {                         \
    return glm::func(arg1.get_glm());                                          \
  }                                                                            \
  template <typename T>                                                        \
  inline auto name(const T &arg1)                                              \
      ->typename std::enable_if<!std::is_base_of<GlmInheritance, T>::value,    \
                                decltype(glm::func(arg1))>::type {             \
    return glm::func(arg1);                                                    \
  }

#define GLM_FUNC2(name, func, arg1, arg2)                                      \
  template <typename T, typename U>                                            \
  inline auto name(const T &arg1, const U &arg2)                               \
      ->typename std::enable_if<                                               \
          std::is_base_of<GlmInheritance, T>::value &&                         \
              std::is_base_of<GlmInheritance, U>::value &&                     \
              std::is_same<typename T::glm_type,                               \
                           decltype(glm::func(arg1.get_glm(),                  \
                                              arg2.get_glm()))>::value,        \
          T>::type {                                                           \
    return glm::func(arg1.get_glm(), arg2.get_glm());                          \
  }                                                                            \
  template <typename T, typename U>                                            \
  inline auto name(const T &arg1, const U &arg2)                               \
      ->typename std::enable_if<                                               \
          std::is_base_of<GlmInheritance, T>::value &&                         \
              std::is_base_of<GlmInheritance, U>::value &&                     \
              !std::is_same<typename T::glm_type,                              \
                            decltype(glm::func(arg1.get_glm(),                 \
                                               arg2.get_glm()))>::value,       \
          decltype(glm::func(arg1.get_glm(), arg2.get_glm()))>::type {         \
    return glm::func(arg1.get_glm(), arg2.get_glm());                          \
  }                                                                            \
  template <typename T, typename U>                                            \
  inline auto name(const T &arg1, const U &arg2)                               \
      ->typename std::enable_if<!std::is_base_of<GlmInheritance, T>::value &&  \
                                    std::is_base_of<GlmInheritance, U>::value, \
                                decltype(                                      \
                                    glm::func(arg1, arg2.get_glm()))>::type {  \
    return glm::func(arg1, arg2.get_glm());                                    \
  }                                                                            \
  template <typename T, typename U>                                            \
  inline auto name(const T &arg1, const U &arg2)                               \
      ->typename std::enable_if<                                               \
          std::is_base_of<GlmInheritance, T>::value &&                         \
              !std::is_base_of<GlmInheritance, U>::value &&                    \
              std::is_same<typename T::glm_type,                               \
                           decltype(glm::func(arg1.get_glm(), arg2))>::value,  \
          T>::type {                                                           \
    return glm::func(arg1.get_glm(), arg2);                                    \
  }                                                                            \
  template <typename T, typename U>                                            \
  inline auto name(const T &arg1, const U &arg2)                               \
      ->typename std::enable_if<                                               \
          std::is_base_of<GlmInheritance, T>::value &&                         \
              !std::is_base_of<GlmInheritance, U>::value &&                    \
              !std::is_same<typename T::glm_type,                              \
                            decltype(glm::func(arg1.get_glm(), arg2))>::value, \
          decltype(glm::func(arg1.get_glm(), arg2))>::type {                   \
    return glm::func(arg1.get_glm(), arg2);                                    \
  }                                                                            \
  template <typename T, typename U>                                            \
  inline auto name(const T &arg1, const U &arg2)                               \
      ->                                                                       \
      typename std::enable_if<!std::is_base_of<GlmInheritance, T>::value &&    \
                                  !std::is_base_of<GlmInheritance, U>::value,  \
                              decltype(glm::func(arg1, arg2))>::type {         \
    return glm::func(arg1, arg2);                                              \
  }

#define GLM_FUNC3(name, func, arg1, arg2, arg3)                                \
  template <typename T, typename U, typename V>                                \
  inline auto name(const T &arg1, const U &arg2, const V &arg3)                \
      ->typename std::enable_if<                                               \
          std::is_base_of<GlmInheritance, T>::value &&                         \
              std::is_base_of<GlmInheritance, U>::value &&                     \
              std::is_base_of<GlmInheritance, V>::value &&                     \
              std::is_same<typename T::glm_type,                               \
                           decltype(glm::func(arg1.get_glm(), arg2.get_glm(),  \
                                              arg3.get_glm()))>::value,        \
          T>::type {                                                           \
    return glm::func(arg1.get_glm(), arg2.get_glm(), arg3.get_glm());          \
  }                                                                            \
  template <typename T, typename U, typename V>                                \
  inline auto name(const T &arg1, const U &arg2, const V &arg3)                \
      ->typename std::enable_if<                                               \
          std::is_base_of<GlmInheritance, T>::value &&                         \
              std::is_base_of<GlmInheritance, U>::value &&                     \
              std::is_base_of<GlmInheritance, V>::value &&                     \
              !std::is_same<typename T::glm_type,                              \
                            decltype(glm::func(arg1.get_glm(), arg2.get_glm(), \
                                               arg3.get_glm()))>::value,       \
          decltype(glm::func(arg1.get_glm(), arg2.get_glm(),                   \
                             arg3.get_glm()))>::type {                         \
    return glm::func(arg1.get_glm(), arg2.get_glm(), arg3.get_glm());          \
  }                                                                            \
  template <typename T, typename U, typename V>                                \
  inline auto name(const T &arg1, const U &arg2, const V &arg3)                \
      ->                                                                       \
      typename std::enable_if<!std::is_base_of<GlmInheritance, T>::value &&    \
                                  std::is_base_of<GlmInheritance, U>::value && \
                                  std::is_base_of<GlmInheritance, V>::value,   \
                              decltype(glm::func(arg1, arg2.get_glm(),         \
                                                 arg3.get_glm()))>::type {     \
    return glm::func(arg1, arg2.get_glm(), arg3.get_glm());                    \
  }                                                                            \
  template <typename T, typename U, typename V>                                \
  inline auto name(const T &arg1, const U &arg2, const V &arg3)                \
      ->typename std::enable_if<                                               \
          std::is_base_of<GlmInheritance, T>::value &&                         \
              !std::is_base_of<GlmInheritance, U>::value &&                    \
              std::is_base_of<GlmInheritance, V>::value &&                     \
              std::is_same<typename T::glm_type,                               \
                           decltype(glm::func(arg1.get_glm(), arg2,            \
                                              arg3.get_glm()))>::value,        \
          T>::type {                                                           \
    return glm::func(arg1.get_glm(), arg2, arg3.get_glm());                    \
  }                                                                            \
  template <typename T, typename U, typename V>                                \
  inline auto name(const T &arg1, const U &arg2, const V &arg3)                \
      ->typename std::enable_if<                                               \
          std::is_base_of<GlmInheritance, T>::value &&                         \
              !std::is_base_of<GlmInheritance, U>::value &&                    \
              std::is_base_of<GlmInheritance, V>::value &&                     \
              !std::is_same<typename T::glm_type,                              \
                            decltype(glm::func(arg1.get_glm(), arg2,           \
                                               arg3.get_glm()))>::value,       \
          decltype(glm::func(arg1.get_glm(), arg2, arg3.get_glm()))>::type {   \
    return glm::func(arg1.get_glm(), arg2, arg3.get_glm());                    \
  }                                                                            \
  template <typename T, typename U, typename V>                                \
  inline auto name(const T &arg1, const U &arg2, const V &arg3)                \
      ->typename std::enable_if<                                               \
          std::is_base_of<GlmInheritance, T>::value &&                         \
              std::is_base_of<GlmInheritance, U>::value &&                     \
              !std::is_base_of<GlmInheritance, V>::value &&                    \
              std::is_same<typename T::glm_type,                               \
                           decltype(glm::func(arg1.get_glm(), arg2.get_glm(),  \
                                              arg3))>::value,                  \
          T>::type {                                                           \
    return glm::func(arg1.get_glm(), arg2.get_glm(), arg3);                    \
  }                                                                            \
  template <typename T, typename U, typename V>                                \
  inline auto name(const T &arg1, const U &arg2, const V &arg3)                \
      ->typename std::enable_if<                                               \
          std::is_base_of<GlmInheritance, T>::value &&                         \
              std::is_base_of<GlmInheritance, U>::value &&                     \
              !std::is_base_of<GlmInheritance, V>::value &&                    \
              !std::is_same<typename T::glm_type,                              \
                            decltype(glm::func(arg1.get_glm(), arg2.get_glm(), \
                                               arg3))>::value,                 \
          decltype(glm::func(arg1.get_glm(), arg2.get_glm(), arg3))>::type {   \
    return glm::func(arg1.get_glm(), arg2.get_glm(), arg3);                    \
  }                                                                            \
  template <typename T, typename U, typename V>                                \
  inline auto name(const T &arg1, const U &arg2, const V &arg3)                \
      ->typename std::enable_if<                                               \
          !std::is_base_of<GlmInheritance, T>::value &&                        \
              !std::is_base_of<GlmInheritance, U>::value &&                    \
              std::is_base_of<GlmInheritance, V>::value,                       \
          decltype(glm::func(arg1, arg2, arg3.get_glm()))>::type {             \
    return glm::func(arg1, arg2, arg3.get_glm());                              \
  }                                                                            \
  template <typename T, typename U, typename V>                                \
  inline auto name(const T &arg1, const U &arg2, const V &arg3)                \
      ->                                                                       \
      typename std::enable_if<!std::is_base_of<GlmInheritance, T>::value &&    \
                                  std::is_base_of<GlmInheritance, U>::value && \
                                  !std::is_base_of<GlmInheritance, V>::value,  \
                              decltype(glm::func(arg1, arg2.get_glm(),         \
                                                 arg3))>::type {               \
    return glm::func(arg1, arg2.get_glm(), arg3);                              \
  }                                                                            \
  template <typename T, typename U, typename V>                                \
  inline auto name(const T &arg1, const U &arg2, const V &arg3)                \
      ->typename std::enable_if<                                               \
          std::is_base_of<GlmInheritance, T>::value &&                         \
              !std::is_base_of<GlmInheritance, U>::value &&                    \
              !std::is_base_of<GlmInheritance, V>::value &&                    \
              std::is_same<typename T::glm_type,                               \
                           decltype(                                           \
                               glm::func(arg1.get_glm(), arg2, arg3))>::value, \
          T>::type {                                                           \
    return glm::func(arg1.get_glm(), arg2, arg3);                              \
  }                                                                            \
  template <typename T, typename U, typename V>                                \
  inline auto name(const T &arg1, const U &arg2, const V &arg3)                \
      ->typename std::enable_if<                                               \
          std::is_base_of<GlmInheritance, T>::value &&                         \
              !std::is_base_of<GlmInheritance, U>::value &&                    \
              !std::is_base_of<GlmInheritance, V>::value &&                    \
              !std::is_same<typename T::glm_type,                              \
                            decltype(glm::func(arg1.get_glm(), arg2,           \
                                               arg3))>::value,                 \
          decltype(glm::func(arg1.get_glm(), arg2, arg3))>::type {             \
    return glm::func(arg1.get_glm(), arg2, arg3);                              \
  }                                                                            \
  template <typename T, typename U, typename V>                                \
  inline auto name(const T &arg1, const U &arg2, const V &arg3)                \
      ->typename std::enable_if<                                               \
          !std::is_base_of<GlmInheritance, T>::value &&                        \
              !std::is_base_of<GlmInheritance, U>::value &&                    \
              !std::is_base_of<GlmInheritance, V>::value,                      \
          decltype(glm::func(arg1, arg2, arg3))>::type {                       \
    return glm::func(arg1, arg2, arg3);                                        \
  }

#define GLM_GET_4TH_ARG(arg1, arg2, arg3, arg4, ...) arg4
#define GLM_FUNC_CHOOSER(...)                                                  \
  GLM_GET_4TH_ARG(__VA_ARGS__, GLM_FUNC3, GLM_FUNC2, GLM_FUNC1, )
#define GLM_FUNC_NAME(name, func, ...)                                         \
  GLM_FUNC_CHOOSER(__VA_ARGS__)(name, func, __VA_ARGS__)
#define GLM_FUNC(func, ...)                                                    \
  GLM_FUNC_CHOOSER(__VA_ARGS__)(func, func, __VA_ARGS__)

namespace specula {
class GlmInheritance {};
} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_INHERITANCE_HPP_