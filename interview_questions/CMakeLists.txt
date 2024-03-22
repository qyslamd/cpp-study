set (CMAKE_CXX_STANDARD 17)
set(target_name interview_questions)

set(source_files 
main.cpp
BasicAndClassic.cpp)

set(header_files 
utils.hpp
BasicAndClassic.h)

add_executable(${target_name} ${source_files} ${header_files})
