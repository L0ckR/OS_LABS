set(CMAKE_CXX_STANDARD 17)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(lab2 main.cpp src/monte-carlo.cpp include/monte-carlo.hpp)

target_link_libraries(lab2 PRIVATE Threads::Threads)


target_include_directories(lab2 PRIVATE include)


