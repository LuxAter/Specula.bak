# ##############################################################################
# SOURCE FILES
# ##############################################################################
set(SOURCES main.cpp)

# ##############################################################################
# TARGET
# ##############################################################################
add_executable(specula-cli ${SOURCES})
target_include_directories(specula-cli PUBLIC ${SPECULA_SOURCE_DIR}/cli)
set_target_properties(specula-cli PROPERTIES CXX_STANDARD 11
                      CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS OFF
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG "${SPECULA_BINARY_DIR}")
target_link_libraries(specula-cli specula::specula)

install(TARGETS specula-cli RUNTIME DESTINATION bin)
