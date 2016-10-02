set(EXECUTABLE_OUTPUT_PATH ..)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++1y")

file(GLOB colony_SRC "map/*.cpp" "map/*.h")
add_executable (colony main.cpp ${colony_SRC})
include_directories(.)

file(GLOB test_SRC "test/*.cpp")
add_executable (runtests runtests.cpp ${test_SRC} ${colony_SRC})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries (runtests LINK_PUBLIC gtest)
