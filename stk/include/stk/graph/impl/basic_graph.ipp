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

namespace stk::graph {
template <typename Vertex, typename Edge>
void basic_graph<Vertex, Edge>::add_vertex(const vertex_type& v)
{
    v_.insert(v);
}

template <typename Vertex, typename Edge>
void basic_graph<Vertex, Edge>::add_edge(const edge_type& e)
{
    e_.insert(e);

    auto ins_u = v_.insert(e.u);
    const_cast<vertex_type&>(*ins_u.first).neighbors.insert(e.v.id);

    auto ins_v = v_.insert(e.u);
    const_cast<vertex_type&>(*ins_v.first).neighbors.insert(e.u.id);
}

template <typename Vertex, typename Edge>
void basic_graph<Vertex, Edge>::add_edge(const vertex_type& v1,
                                         const vertex_type& v2)
{
    add_edge(edge_type{v1, v2});
}

} // namespace stk::graph
