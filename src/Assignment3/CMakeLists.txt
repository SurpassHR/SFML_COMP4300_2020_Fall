FILE(GLOB SRC *.cpp) # learned from CMake Practice that you better using CAPITAL cmake key word

SET(assignment3_target "Assignment3")
ADD_EXECUTABLE(${assignment3_target} ${SRC})
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
TARGET_LINK_LIBRARIES(${assignment3_target} PRIVATE sfml-graphics Public)
TARGET_COMPILE_FEATURES(${assignment3_target} PRIVATE cxx_std_17)