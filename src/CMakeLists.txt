set(EXECUTABLE_OUTPUT_PATH ..)

file(GLOB colony_SRC "map/*.cpp" "map/*.h")
add_executable (colony main.cpp ${colony_SRC})
set_property(TARGET colony PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET colony PROPERTY CXX_STANDARD 14)
include_directories(.)

file(GLOB test_SRC "test/*.cpp")
add_executable (runtests runtests.cpp ${test_SRC} ${colony_SRC})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries (runtests LINK_PUBLIC gtest)
