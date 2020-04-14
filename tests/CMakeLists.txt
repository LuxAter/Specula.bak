# ##############################################################################
# CATCH TOOLS
# ##############################################################################
add_library(unit-tests-main STATIC main.cpp)
target_link_libraries(unit-tests-main PUBLIC specula-warnings specula-options specula::specula Catch2::Catch2)
include(Catch)

# ##############################################################################
# UNIT-TESTS
# ##############################################################################
set(UNITTEST_SOURCE spectrum.cpp parallel.cpp sampling.cpp imageio.cpp)

add_executable(unit-tests ${UNITTEST_SOURCE})
target_include_directories(unit-tests PUBLIC ${SPECULA_SOURCE_DIR}/tests)
target_link_libraries(unit-tests PRIVATE unit-tests-main)

catch_discover_tests(unit-tests TEST_PREFIX "unittests." EXTRA_ARGS -s --reporter=xml --out=tests.xml)

# TODO: Add code coverage reporting using gcovr
