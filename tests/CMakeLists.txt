FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        matplotplusplus
        GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
        GIT_TAG origin/master
) # or whatever tag you want

FetchContent_GetProperties(matplotplusplus)
if(NOT matplotplusplus_POPULATED)
    FetchContent_Populate(matplotplusplus)
    add_subdirectory(${matplotplusplus_SOURCE_DIR} ${matplotplusplus_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

set(CMAKE_CXX_STANDARD 17)      

#add LAB1

add_executable(lab1_test lab1_test.cpp ../lab1/src/parent.cpp ../lab1/include/parent.hpp
        ../lab1/src/utils.cpp ../lab1/include/utils.hpp)

target_link_libraries(lab1_test PRIVATE GTest::GTest)
target_include_directories(lab1_test PRIVATE ../lab1/include)


#add LAB2

find_package(Threads REQUIRED)

add_executable(lab2_test lab2_test.cpp ../lab2/src/monte-carlo.cpp ../lab2/include/monte-carlo.hpp)

target_link_libraries(lab2_test PUBLIC matplot)

target_link_libraries(lab2_test PRIVATE GTest::GTest)
target_link_libraries(lab2_test PRIVATE Threads::Threads)

target_include_directories(lab2_test PRIVATE ../lab2/include)

#add LAB3

add_executable(lab3_test lab3_test.cpp ../lab3/src/parent.cpp ../lab3/include/parent.hpp
        ../lab3/src/utils.cpp ../lab3/include/utils.hpp)

target_link_libraries(lab3_test PRIVATE GTest::GTest)
target_include_directories(lab3_test PRIVATE ../lab3/include)

#add LAB4
add_executable(lab4_test1 lab4_test1.cpp ../lab4/include/implementations.hpp 
        ../lab4/src/implementation1.cpp)
target_link_libraries(lab4_test1 PRIVATE GTest::GTest)
target_include_directories(lab4_test1 PRIVATE ../lab4/include)

add_executable(lab4_test2 lab4_test2.cpp ../lab4/include/implementations.hpp 
        ../lab4/src/implementation2.cpp)
target_link_libraries(lab4_test2 PRIVATE GTest::GTest)
target_include_directories(lab4_test2 PRIVATE ../lab4/include)
# Lab 5-7

set(CMAKE_CXX_FLAGS "-lzmq")
add_compile_options(-Wno-error=deprecated-declarations -Wdeprecated-declarations)

add_executable(lab567_test lab567_test.cpp ../lab567/src/node_routine.cpp ../lab567/src/socket_routine.cpp)
target_link_libraries(lab567_test PRIVATE GTest::GTest)
target_include_directories(lab567_test PRIVATE ../lab567/include)

target_link_libraries(lab567_test PRIVATE zmq)

#add CP
add_executable(cp_test cp_test.cpp)
target_include_directories(cp_test PRIVATE ${CMAKE_SOURCE_DIR}/cp/include)
target_include_directories(cp_test PRIVATE ${CMAKE_SOURCE_DIR}/cp/lib)
target_link_libraries(cp_test PRIVATE cp_lib GTest::GTest)