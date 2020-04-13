# ##############################################################################
# SOURCE FILES
# ##############################################################################
set(SOURCES main.cpp spectrum.cpp parallel.cpp sampling.cpp imageio.cpp)

# ##############################################################################
# CATCH TOOLS
# ##############################################################################
include(Catch)

# ##############################################################################
# TARGET
# ##############################################################################
add_executable(unit-tests ${SOURCES})
target_include_directories(unit-tests PUBLIC ${SPECULA_SOURCE_DIR}/tests)
set_target_properties(
  unit-tests
  PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS OFF
             RUNTIME_OUTPUT_DIRECTORY_DEBUG "${SPECULA_BINARY_DIR}")
target_link_libraries(unit-tests specula::specula Catch2::Catch2)

catch_discover_tests(unit-tests)
