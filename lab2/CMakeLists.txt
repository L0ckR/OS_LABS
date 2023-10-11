set(CMAKE_CXX_STANDARD 17)


add_executable(lab2 main.cpp src/monte-carlo.cpp include/monte-carlo.hpp)

target_include_directories(lab2 PRIVATE include)


