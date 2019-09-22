#include <deque>
#include <iostream>
#include <optional>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

#include "stk/algorithms/visitor/visitor.h"
#include "stk/ds/graph/graph.h"

int main()
{
    using graph_type = stk::ds::graph::graph<std::string>;
    graph_type g;
    g.add_vertex("1", {"2", "3"});
    g.add_vertex("2", {"1", "5"});
    g.add_vertex("3", {"1", "4", "7"});
    g.add_vertex("4", {"3", "7"});
    g.add_vertex("5", {"2", "4", "6"});
    g.add_vertex("6", {"5"});
    g.add_vertex("7", {"3", "4", "8", "9", "10"});
    g.add_vertex("8", {"7"});
    g.add_vertex("9", {"7"});
    g.add_vertex("10", {"7"});

    using vertex_type = typename graph_type::vertex_type;
    const auto process = [](const vertex_type& v) { std::cout << v << " "; };

    stk::algorithms::visitor::dfs<graph_type> d{g};
    std::cout << "dfs: ";
    d.visit(process, "1");
    std::cout << "\n";

    stk::algorithms::visitor::bfs<graph_type> b{g};
    std::cout << "bfs: ";
    b.visit(process, "1");
    std::cout << "\n";
}
