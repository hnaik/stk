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

#ifndef STK_DS_GRAPH_GRAPH_H
#define STK_DS_GRAPH_GRAPH_H

#include <array>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace stk::ds::graph {
template <typename Vertex, typename VertexSet = std::unordered_set<Vertex>>
class graph {
public:
    using vertex_type = Vertex;
    using set = VertexSet;

    void add_vertex(const vertex_type& vertex, const set& neighbors);

    const set& neighbors(const vertex_type& vertex) const
    {
        return g_.at(vertex);
    }

    bool has_neighbors(const vertex_type& vertex) const
    {
        return g_.find(vertex) != end(g_) && g_.at(vertex).size() > 0;
    }

public:
    std::unordered_map<vertex_type, set> g_;
};

template <typename Vertex>
using bst = graph<Vertex, std::vector<Vertex>>;

} // namespace stk::ds::graph

#include "stk/ds/graph/impl/graph.ipp"

#endif // STK_DS_GRAPH_GRAPH_H
