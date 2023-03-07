cmake_minimum_required (VERSION 3.8)

project(thread_test1)

set(CMAKE_CXX_COMPLIER "c++")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

FILE(GLOB ALL_SOURCES "*.cpp" "*.cxx" "*.cc")
FILE(GLOB ALL_HEADERS "*.h" "*.hpp" )

set(ALL_SRCS  ${ALL_SOURCES} ${ALL_HEADERS} )

add_executable(thread_test1 ${ALL_SRCS})