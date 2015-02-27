set(EXECUTABLE_OUTPUT_PATH ..)

add_executable (colony main.cpp)

add_executable (runtests runtests.cpp)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries (runtests LINK_PUBLIC gtest)
