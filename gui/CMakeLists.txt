# ##############################################################################
# SOURCE FILES
# ##############################################################################
set(SOURCES main.cpp)

# ##############################################################################
# TARGET
# ##############################################################################
add_executable(specula-gui ${SOURCES})
target_include_directories(specula-gui PUBLIC ${SPECULA_SOURCE_DIR}/gui)
set_target_properties(specula-gui PROPERTIES CXX_STANDARD 11
                      CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS OFF
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG "${SPECULA_BINARY_DIR}")
target_link_libraries(specula-gui specula::specula)

install(TARGETS specula-gui RUNTIME DESTINATION bin)
