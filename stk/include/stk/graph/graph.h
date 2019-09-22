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

#ifndef STK_GRAPH_GRAPH_H
#define STK_GRAPH_GRAPH_H

#include <string>

#include "stk/graph/basic_graph.h"
#include "stk/graph/edge.h"
#include "stk/graph/vertex.h"

namespace stk::graph {
using vertex_type = vertex<std::string>;
using edge_type = edge<vertex_type>;
using graph = basic_graph<vertex_type, edge_type>;
} // namespace stk::graph

#endif // STK_GRAPH_GRAPH_H
