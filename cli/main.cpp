#include "specula/dev/prof.hpp"
#include <specula/specula.hpp>

#include <chrono>
#include <thread>

// #define FUNC_OBJ(FUNC, obj, x) FUNC(obj, x);
// #define FUNC_NO_OBJ(FUNC, obj, x) FUNC(x);
// #define FUNC_OBJ_LIST(FUNC, obj, x) ,FUNC(obj, x)
// #define FUNC_NO_OBJ_LIST(FUNC, obj, x) ,FUNC(x)

// #define EVAL0(CALLER, FUNC, obj, ...)
// #define EVAL1(CALLER, FUNC, obj, ...) CALLER(FUNC, obj, __VA_ARGS__)
// #define EVAL2(CALLER, FUNC, obj, x, ...) CALLER(FUNC, obj, x) EVAL1(CALLER, FUNC, obj, __VA_ARGS__)
// #define EVAL3(CALLER, FUNC, obj, x, ...) CALLER(FUNC, obj, x) EVAL2(CALLER, FUNC, obj, __VA_ARGS__)
// #define EVAL4(CALLER, FUNC, obj, x, ...) CALLER(FUNC, obj, x) EVAL3(CALLER, FUNC, obj, __VA_ARGS__)
// #define EVAL5(CALLER, FUNC, obj, x, ...) CALLER(FUNC, obj, x) EVAL4(CALLER, FUNC, obj, __VA_ARGS__)
// #define EVAL6(CALLER, FUNC, obj, x, ...) CALLER(FUNC, obj, x) EVAL5(CALLER, FUNC, obj, __VA_ARGS__)
// #define EVAL7(CALLER, FUNC, obj, x, ...) CALLER(FUNC, obj, x) EVAL6(CALLER, FUNC, obj, __VA_ARGS__)
// #define EVAL8(CALLER, FUNC, obj, x, ...) CALLER(FUNC, obj, x) EVAL7(CALLER, FUNC, obj, __VA_ARGS__)
// #define EVAL9(CALLER, FUNC, obj, x, ...) CALLER(FUNC, obj, x) EVAL8(CALLER, FUNC, obj, __VA_ARGS__)
// #define EVAL10(CALLER, FUNC, obj, x, ...) CALLER(FUNC, obj, x) EVAL9(CALLER, FUNC, obj, __VA_ARGS__)

// #define GET_MACRO(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, NAME, ...) NAME

// #define FOR_EACH(FUNC, ...) GET_MACRO(_0 __VA_OPT__(,) __VA_ARGS__, EVAL10, EVAL9, EVAL8, EVAL7, EVAL6, EVAL5, EVAL4, EVAL3, EVAL2, EVAL1, EVAL0)(FUNC_NO_OBJ, FUNC, _0, __VA_ARGS__)
// #define FOR_EACH_OBJ(FUNC, obj, ...) GET_MACRO(_0 __VA_OPT__(,) __VA_ARGS__, EVAL10, EVAL9, EVAL8, EVAL7, EVAL6, EVAL5, EVAL4, EVAL3, EVAL2, EVAL1, EVAL0)(FUNC_OBJ, FUNC, obj, __VA_ARGS__)
// #define FOR_EACH_LIST(FUNC, ...) GET_MACRO(_0 __VA_OPT__(,) __VA_ARGS__, EVAL10, EVAL9, EVAL8, EVAL7, EVAL6, EVAL5, EVAL4, EVAL3, EVAL2, EVAL1, EVAL0)(FUNC_NO_OBJ_LIST, FUNC, _0, __VA_ARGS__)
// #define FOR_EACH_OBJ_LIST(FUNC, obj, ...) GET_MACRO(_0 __VA_OPT__(,) __VA_ARGS__, EVAL10, EVAL9, EVAL8, EVAL7, EVAL6, EVAL5, EVAL4, EVAL3, EVAL2, EVAL1, EVAL0)(FUNC_OBJ_LIST, FUNC, obj, __VA_ARGS__)

// void pnt(char ch) { std::printf(">>%c<<\n", ch);}
// void pntch(char* str, int id) { std::printf("[%d]->%c\n", id, str[id]);}

int main(int argc, char *argv[]) {
  // char* str = "Hello World!";
  // FOR_EACH(pnt, 'a', 'b', 'c');
  // FOR_EACH_OBJ(pntch, str, 0, 2, 3, 5);
  PROF_BEGIN("Logging", "Init");
  PROF_COUNT("Test", 0);
  specula::logger::register_sink<specula::logger::DailyFileSink>("logs/log", 03,
                                                                 00);
  specula::logger::register_sink<specula::logger::StderrColorSink>();
  specula::logger::initialize_core_logger();
  specula::logger::initialize_logger("CLI");
  PROF_END();
  PROF_COUNT("Test", 1);

  PROF_BEGIN("Versioning", "Init");
  PROF_COUNT("Test", 2);
  LINFO("Specula Version {}.{}.{}", SPECULA_VERSION_MAJOR,
        SPECULA_VERSION_MINOR, SPECULA_VERSION_PATCH);
  LCINFO("CLI", "Specula-CLI Version {}.{}.{}", 0, 0, 0);
  PROF_COUNT("Test", 3);
  PROF_END();

  return 0;
}
