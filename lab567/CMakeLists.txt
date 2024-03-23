set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-lzmq")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_compile_options(-Wno-error=deprecated-declarations -Wdeprecated-declarations)

add_executable(client src/client.cpp src/node_routine.cpp src/socket_routine.cpp include/node_routine.hpp include/socket_routine.hpp)
target_include_directories(client PRIVATE include)

add_executable(server src/server.cpp src/node_routine.cpp src/socket_routine.cpp include/node_routine.hpp include/socket_routine.hpp)
target_include_directories(server PRIVATE include)

target_link_libraries(client PRIVATE zmq)

target_link_libraries(server PRIVATE zmq)