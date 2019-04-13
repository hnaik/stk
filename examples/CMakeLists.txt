add_example(convex_hull_demo)
add_example(lu_dcmp)
add_example(valmat)

if(!MSVC)
    # because the example uses getopt
    add_example(knapsack)
endif()
