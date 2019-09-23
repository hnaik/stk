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

#include <unordered_map>
#include <unordered_set>

namespace stk::ds::graph {
template <typename Vertex>
class graph {
public:
    using vertex_type = Vertex;
    using set = std::unordered_set<vertex_type>;

    void add_vertex(const vertex_type& vertex, const set& neighbors)
    {
        for(const auto& neighbor : neighbors) {
            g_[vertex].insert(neighbor);
        }
    }

    const set& neighbors(const vertex_type& vertex) const
    {
        return g_.at(vertex);
    }

public:
    std::unordered_map<vertex_type, set> g_;
};

} // namespace stk::ds::graph

#endif // STK_DS_GRAPH_GRAPH_H
