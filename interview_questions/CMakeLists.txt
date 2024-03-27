set (CMAKE_CXX_STANDARD 17)
set(target_name interview_questions)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(all_srcs 
	main.cpp
	utils.cpp
	utils.h
	basic_and_classic/BasicAndClassic.cpp
	basic_and_classic/BasicAndClassic.h
	thread_usage/ThreadUsage.cpp
	thread_usage/ThreadUsage.hpp
	design_pattern/DesignPattern.cpp
	design_pattern/DesignPattern.h
	design_pattern/creational_patterns/abstract_factory.hpp
	design_pattern/creational_patterns/factory_method.hpp
	design_pattern/creational_patterns/builder.hpp)

message("sb " + ${all_srcs})

add_executable(${target_name} ${all_srcs})
