cmake_minimum_required(VERSION 3.20)
include(FetchContent)

project(OS_LABS C CXX)

enable_testing()

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options( -Wall -Wextra -pedantic -Werror)
endif()

include(FindThreads)

#add LAB1
add_subdirectory(lab1)

#add LAB2
add_subdirectory(lab2)

#add LAB3
add_subdirectory(lab3)

#add LAB4
add_subdirectory(lab4)

#add LAB567
add_subdirectory(lab567)

#add CP
add_subdirectory(cp)

#add TESTS
add_subdirectory(tests)