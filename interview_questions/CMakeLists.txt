set (CMAKE_CXX_STANDARD 17)
set(target_name interview_questions)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(all_srcs 
	main.cpp
	utils.cpp
	utils.h
	basic_and_classic/BasicAndClassic.cpp
	basic_and_classic/BasicAndClassic.h
	pointers/pointers_basic.cpp
	pointers/pointers_basic.h
	thread_usage/ThreadUsage.cpp
	thread_usage/ThreadUsage.hpp
	design_pattern/DesignPattern.cpp
	design_pattern/DesignPattern.h
	design_pattern/creational_patterns/abstract_factory.hpp
	design_pattern/creational_patterns/factory_method.hpp
	design_pattern/creational_patterns/builder.hpp
	design_pattern/creational_patterns/singleton.hpp
	design_pattern/creational_patterns/prototype_or_clone.hpp
	design_pattern/structual_patterns/adapter.hpp
	data_structure_and_algorithms/data_structure_algorithm.cpp
	data_structure_and_algorithms/data_structure_algorithm.h
	data_structure_and_algorithms/queue/array_make_queue.cpp
	data_structure_and_algorithms/queue/array_make_queue.h)
add_executable(${target_name} ${all_srcs})
