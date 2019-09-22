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

#ifndef STK_GRAPH_EDGE_H
#define STK_GRAPH_EDGE_H

#include <unordered_set>

namespace stk::graph {
template <typename Vertex>
struct edge_hasher;

template <typename Vertex>
struct edge {
    using vertex_type = Vertex;
    using set = std::unordered_set<edge, edge_hasher<vertex_type>>;

    vertex_type u;
    vertex_type v;
    size_t w;
};

template <typename Vertex>
struct edge_hasher {
    using vertex_type = Vertex;
    size_t operator()(const edge<vertex_type>& e) const;
};

} // namespace stk::graph

#include "stk/graph/impl/edge.ipp"
#endif // STK_GRAPH_EDGE_H
