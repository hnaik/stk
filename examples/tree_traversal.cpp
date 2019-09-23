/*
 * This file is part of the STK library
 * Copyright (C) 2018 Harish G. Naik <harishgnaik@gmail.com>
 *
 * STK library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <vector>

#include "stk/algorithms/visitor/binary_tree_traversal.h"
#include "stk/ds/graph/graph.h"

struct VisitingObject {
    template <typename Vertex>
    void operator()(Vertex v)
    {
        std::cout << v << " ";
    }
};

int main()
{
    using vertex_type = std::string;
    stk::ds::graph::bst<vertex_type> tree;

    tree.add_vertex("8", {"4", "12"});
    tree.add_vertex("4", {"2", "6"});
    tree.add_vertex("2", {"1", "3"});
    tree.add_vertex("6", {"5", "7"});
    tree.add_vertex("12", {"10", "14"});
    tree.add_vertex("10", {"9", "11"});
    tree.add_vertex("14", {"13", "15"});

    const auto visit = [](vertex_type v) { std::cout << v << " "; };

    namespace visitor = stk::algorithms::visitor;

    VisitingObject visit_object;
    visitor::in_order(tree, "8", visit_object);
    std::cout << "\n";
    visitor::pre_order(tree, "8", visit);
    std::cout << "\n";
    visitor::post_order(tree, "8", visit);
    std::cout << "\n";
}
