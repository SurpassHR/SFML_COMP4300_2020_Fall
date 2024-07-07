file(GLOB SOURCES ./*.cpp)

set(assignment1_target "Assignment1")
add_executable(${assignment1_target} ${SOURCES})
set_target_properties(${assignment1_target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
target_link_libraries(${assignment1_target} PRIVATE sfml-graphics sfml-audio)
target_compile_features(${assignment1_target} PRIVATE cxx_std_17)