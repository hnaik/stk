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

#ifndef STK_ALGORITHMS_VISITOR_DFS_H
#define STK_ALGORITHMS_VISITOR_DFS_H

#include <optional>

#include "stk/algorithms/visitor/base_visitor.h"

namespace stk::algorithms::visitor {
template <typename Graph>
class dfs : public base_visitor<Graph> {
public:
    using graph_type = typename base_visitor<Graph>::graph_type;
    using vertex_type = typename graph_type::vertex_type;

    dfs(const graph_type& g)
        : base_visitor<graph_type>{g}
    {
    }

protected:
    void process(const vertex_type& vertex) override
    {
        const auto neighbor = get_unvisited_neighbor(vertex);

        if(neighbor) {
            this->cache_.push_back(*neighbor);
        } else {
            this->cache_.pop_back();
        }
    }

    vertex_type get_current_vertex() override { return this->cache_.back(); }

private:
    std::optional<vertex_type> get_unvisited_neighbor(const vertex_type& vertex)
    {
        for(const auto& neighbor : this->g_.neighbors(vertex)) {
            if(!this->visited(neighbor)) {
                return neighbor;
            }
        }

        return std::nullopt;
    }
};

} // namespace stk::algorithms::visitor

#endif // STK_ALGORITHMS_VISITOR_DFS_H
