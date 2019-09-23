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

#ifndef STK_ALGORITHMS_VISITOR_BFS_H
#define STK_ALGORITHMS_VISITOR_BFS_H

#include "stk/algorithms/visitor/base_visitor.h"

namespace stk::algorithms::visitor {
template <typename Graph>
class bfs : public base_visitor<Graph> {
public:
    using graph_type = typename base_visitor<Graph>::graph_type;
    using vertex_type = typename graph_type::vertex_type;

    bfs(const graph_type& g)
        : base_visitor<graph_type>{g}
    {
    }

protected:
    void process(const vertex_type& vertex) override
    {
        for(const auto& neighbor : this->g_.neighbors(vertex)) {
            if(!this->visited(neighbor)) {
                this->cache_.push_back(neighbor);
            }
        }
    }

    vertex_type get_current_vertex() override
    {
        const auto current = this->cache_.front();
        this->cache_.pop_front();
        return current;
    }
};

} // namespace stk::algorithms::visitor
#endif // STK_ALGORITHMS_VISITOR_BFS_H
