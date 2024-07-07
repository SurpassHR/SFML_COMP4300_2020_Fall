file(GLOB SOURCES ./*.cpp)

# 添加头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include/ECS_Practice)

set(ecs_target_name "ECS")
add_executable(${ecs_target_name} ${SOURCES})
set_target_properties(${ecs_target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
target_link_libraries(${ecs_target_name} PRIVATE sfml-graphics sfml-audio)
target_compile_features(${ecs_target_name} PRIVATE cxx_std_17)