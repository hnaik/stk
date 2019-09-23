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

#include "stk/graph/vertex.h"

namespace stk::graph {
struct edge_hasher;

struct edge {
    using set = std::unordered_set<edge, edge_hasher>;

    vertex u;
    vertex v;
    size_t w;
};

struct edge_hasher {
    size_t operator()(const edge& e) const
    {
        vertex_hasher hasher;
        return hasher(e.u) ^ hasher(e.v);
    }
};

bool operator==(const edge& e1, const edge& e2)
{
    return (e1.u == e2.u && e1.v == e2.v) || (e1.u == e2.v && e1.v == e2.u);
}

std::ostream& operator<<(std::ostream& os, const edge& e)
{
    os << "(" << e.u << "," << e.v << ")";
    return os;
}

} // namespace stk::graph

#endif // STK_GRAPH_EDGE_H
