cmake_minimum_required(VERSION 3.13)

project(stk)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(!MSVC)
    set(CMAKE_CXX_FLAGS "-fconcepts -Wall -Werror")
endif()

add_subdirectory(stk)

function(add_example name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} stk)
endfunction(add_example)

add_subdirectory(examples)

set(ENABLE_TESTS false CACHE BOOL "Enable unittests")

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif(ENABLE_TESTS)
