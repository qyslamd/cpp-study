set(CMAKE_CXX_STANDARD 17)

set(target_name zero_started)

#FILE(GLOB ALL_SOURCES "*.cpp" "*.cxx" "*.cc")
#FILE(GLOB ALL_HEADERS "*.h" "*.hpp" )
#FILE(GLOB ALL_RES "*.qrc" "*.rc")

set(source_files main.cpp)

set(header_files zero_started.hpp
                 thread_usage.hpp)

set(ALL_SRCS  ${source_files} ${header_files} )

add_executable(${target_name} ${ALL_SRCS})
