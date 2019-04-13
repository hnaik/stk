add_example(convex_hull_demo)
add_example(graph_adjacency)
add_example(graph_search)
add_example(lu_dcmp)
add_example(tree_traversal)
add_example(valmat)

if(!MSVC)
    # because the example uses getopt
    add_example(knapsack)
endif()
