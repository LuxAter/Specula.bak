# ##############################################################################
# CATCH TOOLS
# ##############################################################################
add_library(unit-tests-main STATIC main.cpp)
target_link_libraries(unit-tests-main PUBLIC specula-warnings specula-options
                                             specula::specula Catch2::Catch2)
include(Catch)

# ##############################################################################
# UNIT-TESTS
# ##############################################################################
set(UNITTEST_SOURCE spectrum.cpp parallel.cpp sampling.cpp imageio.cpp)

add_executable(unit-tests ${UNITTEST_SOURCE})
target_include_directories(unit-tests PUBLIC ${SPECULA_SOURCE_DIR}/tests)
target_link_libraries(unit-tests PRIVATE unit-tests-main)

catch_discover_tests(
  unit-tests
  TEST_PREFIX
  "unittests."
  EXTRA_ARGS
  -s
  --reporter=xml
  --out=tests.xml)

# ##############################################################################
# COVERAGE
# ##############################################################################
if(SPECULA_ENABLE_COVERAGE)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    find_program(GCOV gcov QUIET)
  else()
    find_program(GCOV llvm-cov)
    set(GCOV "${GCOV} gcov")
  endif()
  if(GCOV)
    find_program(GCOVR gcovr)
    message("GCOVR: ${GCOVR}")
    file(MAKE_DIRECTORY "${SPECULA_BINARY_DIR}/coverage/")
    add_custom_target(
      coverage
      COMMAND unit-tests
      COMMAND
        ${GCOVR} --gcov-executable "${GCOV}" -r "${SPECULA_SOURCE_DIR}"
        --exclude "${SPECULA_SOURCE_DIR}/extern" --exclude
        "${SPECULA_SOURCE_DIR}/tests" --html coverage.html --html-detail
        --html-title "Code Coverage Report"
      DEPENDS unit-tests
      WORKING_DIRECTORY "${SPECULA_BINARY_DIR}/coverage/")
  endif()
endif()
# TODO: Add code coverage reporting using gcovr
