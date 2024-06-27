file(GLOB SOURCES ./*.cpp)

# 添加头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include/Assignment2)

set(assignment2_target "Assignment2")
add_executable(${assignment2_target} ${SOURCES})
set_target_properties(${assignment2_target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
target_link_libraries(${assignment2_target} PRIVATE sfml-graphics sfml-audio)
target_compile_features(${assignment2_target} PRIVATE cxx_std_17)

add_subdirectory(components)