cmake_minimum_required (VERSION 2.8.11)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++1y")

#set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)
#set_property(GLOBAL PROPERTY CXX_STANDARD 14)

#set(cxx_standard -std=c++14)


project (colony)

add_subdirectory(lib/gtest-1.7.0)
#enable_testing()

add_subdirectory(src)
