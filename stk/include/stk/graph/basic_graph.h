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

#ifndef STK_GRAPH_BASIC_GRAPH_H
#define STK_GRAPH_BASIC_GRAPH_H

#include <string>
#include <unordered_set>

#include "stk/graph/edge.h"
#include "stk/graph/vertex.h"

namespace stk::graph {

class basic_graph {
public:
    using vertex_type = vertex;
    using vertex_set = vertex_type::set;
    using edge_type = edge;
    using edge_set = edge_type::set;

    void add_vertex(const vertex_type& v);
    void add_edge(const edge_type& e);
    void add_edge(const vertex_type& v1, const vertex_type& v2);

    inline bool has_vertex(const vertex_type& v) const
    {
        // When we have a C++20 compliant compiler, we should replace this with:
        //     return v_.contains(v);
        return v_.find(v) != end(v_);
    }

    inline bool has_edge(const edge_type& e) const
    {
        // When we have C++20 compliant compiler, we should replace this with:
        //     return e_.contains(e);
        return e_.find(e) != std::end(e_);
    }

    inline bool has_edge(const vertex_type& v1, const vertex_type& v2) const
    {
        return has_edge(edge_type{v1, v2});
    }

    bool has_edge(const vertex_type::id_type& v1_id,
                  const vertex_type::id_type& v2_id) const;

    inline const edge_set& edges() const { return e_; }
    inline const vertex_set& vertices() const { return v_; }

    inline size_t vertex_count() const { return v_.size(); }
    inline size_t edge_count() const { return e_.size(); }

    friend std::ostream& operator<<(std::ostream& os, const basic_graph& g);

private:
    vertex_set v_;
    edge_set e_;
};

std::ostream& operator<<(std::ostream& os, const basic_graph& g)
{
    for(const auto& v : g.v_) {
        os << "[" << v << "] ";
        for(const auto& n : v.neighbors) {
            os << n;
        }
        os << "\n";
    }
    return os;
}

void basic_graph::add_vertex(const vertex_type& v) { v_.insert(v); }

void basic_graph::add_edge(const edge_type& e)
{
    e_.insert(e);

    auto ins_u = v_.insert(e.u);
    const_cast<vertex&>(*ins_u.first).neighbors.insert(e.v.id);

    auto ins_v = v_.insert(e.u);
    const_cast<vertex&>(*ins_v.first).neighbors.insert(e.u.id);
}

void basic_graph::add_edge(const vertex_type& v1, const vertex_type& v2)
{
    add_edge(edge_type{v1, v2});
}
} // namespace stk::graph

#endif // STK_GRAPH_BASIC_GRAPH_H
