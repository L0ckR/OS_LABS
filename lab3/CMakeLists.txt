set(CMAKE_CXX_STANDARD 17)


add_executable(lab3 main.cpp src/parent.cpp src/utils.cpp include/utils.hpp)

target_include_directories(lab3 PRIVATE include)


add_executable(fm_child1 src/child1.cpp src/utils.cpp include/utils.hpp)

target_include_directories(fm_child1 PRIVATE include)


add_executable(fm_child2 src/child2.cpp src/utils.cpp include/utils.hpp)

target_include_directories(fm_child2 PRIVATE include)


add_dependencies(lab3 fm_child1 fm_child2)