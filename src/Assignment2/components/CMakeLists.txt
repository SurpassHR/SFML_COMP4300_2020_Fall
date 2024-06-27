target_include_directories(${assignment2_target} PRIVATE ${CMAKE_SOURCE_DIR}/include/Assignment2/components)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
target_sources(${assignment2_target} PRIVATE ${SOURCES})