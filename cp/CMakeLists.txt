add_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)
include(FetchContent)

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG origin/master # Can be a tag (yaml-cpp-x.x.x), a commit hash, or a branch name (master)
)
FetchContent_GetProperties(yaml-cpp)

if(NOT yaml-cpp_POPULATED)
  message(STATUS "Fetching yaml-cpp...")
  FetchContent_Populate(yaml-cpp)
  add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
endif()

include_directories(BEFORE SYSTEM ${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR}/include)

add_library(cp_lib src/job_dag.cpp src/job_exec.cpp)
target_include_directories(cp_lib PUBLIC include)
target_link_libraries(cp_lib yaml-cpp)

add_executable(cp_main main.cpp)
target_include_directories(cp_main PUBLIC include)
target_link_libraries(cp_main cp_lib)