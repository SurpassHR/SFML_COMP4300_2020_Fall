file(GLOB SOURCES
    gravity.cpp
)

foreach(source_file ${SOURCES})
    # 获取文件名（不带路径和扩展名）
    get_filename_component(target_name ${source_file} NAME_WE)
    # 添加可执行文件
    add_executable(${target_name} ${source_file})
    # 指定二进制输出位置
    set_target_properties(${target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
    # 链接sfml库
    target_link_libraries(${target_name} PRIVATE sfml-graphics sfml-audio)
    # 设置C++标准
    target_compile_features(${target_name} PRIVATE cxx_std_17)
endforeach()

add_subdirectory(Assignment1)
add_subdirectory(ECS)
add_subdirectory(Assignment2)