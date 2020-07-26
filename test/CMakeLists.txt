function(add_stk_test name)
    set(target test_${name})
    add_executable(${target} ${target}.cpp)
    target_link_libraries(${target}
        stk
        gtest_main
        gtest
        pthread)
    add_test(NAME ${target} COMMAND ${target})
endfunction(add_stk_test)

add_stk_test(la)
#add_stk_test(lu)
add_stk_test(matrix)
add_stk_test(stat)
add_stk_test(vector)

add_subdirectory(opt)
