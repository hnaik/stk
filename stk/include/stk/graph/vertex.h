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

#ifndef STK_GRAPH_VERTEX_H
#define STK_GRAPH_VERTEX_H

namespace stk::graph {
template <typename Id>
struct vertex_hasher;

template <typename Id = std::string>
struct vertex {
    using id_type = Id;
    using set = std::unordered_set<vertex, vertex_hasher<id_type>>;

    // we don't need to store the entire node here because that will lead to
    // a lot of wasted space. We can always look up the neighbors of those
    // vertices from the master list of vertices in the basic_graph.
    using neighbor_set = std::unordered_set<id_type>;

    template <typename T>
    vertex(const T& id_)
        : id{std::to_string(id_)}
    {
    }

    vertex(const std::string& id_)
        : id{id_}
    {
    }

    vertex(const vertex& v)
        : id{v.id}
        , neighbors{v.neighbors}
    {
    }

    vertex& operator=(const vertex& v)
    {
        id = v.id;
        neighbors = v.neighbors;
        return *this;
    }

    bool is_neighbor(const id_type& id) const
    {
        return neighbors.find(id) != end(neighbors);
    }

    std::string to_string() const { return std::to_string(id); }

    size_t hash() const;

    id_type id;
    neighbor_set neighbors;

    static size_t hash(const vertex& v) { return std::hash<id_type>{}(v.id); }
};

template <typename Id>
struct vertex_hasher {
    size_t operator()(const vertex<Id>& v) const;
};

} // namespace stk::graph

#include "stk/graph/impl/vertex.ipp"

#endif // STK_GRAPH_VERTEX_H
