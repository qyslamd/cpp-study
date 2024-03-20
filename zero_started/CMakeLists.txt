project(thread_test1)

set(CMAKE_CXX_COMPLIER "c++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

FILE(GLOB ALL_SOURCES "*.cpp" "*.cxx" "*.cc")
FILE(GLOB ALL_HEADERS "*.h" "*.hpp" )
FILE(GLOB ALL_RES "*.qrc" "*.rc")

set(ALL_SRCS  ${ALL_SOURCES} ${ALL_HEADERS} )

add_executable(zero_started ${ALL_SRCS})
