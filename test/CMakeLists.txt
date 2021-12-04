enable_testing()

include(GoogleTest)

function(stk_test name)
    add_executable(test_${name} test_${name}.cpp)
    target_link_libraries(test_${name} stk gtest_main)
    gtest_discover_tests(test_${name})
endfunction(stk_test)

stk_test(la)
# stk_test(lu)
stk_test(matrix)
stk_test(stat)
stk_test(vector)

add_subdirectory(opt)
