cmake_minimum_required(VERSION 3.22)
project(stk)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -Wsign-conversion")

add_subdirectory(stk)

# function(add_example name)
#     add_executable(${name} ${name}.cpp)
#     target_link_libraries(${name} stk)
# endfunction(add_example)

#add_subdirectory(examples)

add_subdirectory(cmake)

include(CTest)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(test)
endif(BUILD_TESTING)
