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

#ifndef STK_ALGORITHMS_VISITOR_BASE_VISITOR_H
#define STK_ALGORITHMS_VISITOR_BASE_VISITOR_H

#include <deque>

namespace stk::algorithms::visitor {
template <typename Graph>
class base_visitor {
public:
    using graph_type = Graph;
    using vertex_set = typename graph_type::set;
    using vertex_type = typename graph_type::vertex_type;

    base_visitor(const graph_type& g)
        : g_{g}
    {
    }

    template <typename Function>
    void visit(Function f, const vertex_type& root)
    {
        cache_.push_back(root);

        while(!cache_.empty()) {
            const auto current = get_current_vertex();

            if(visited_.find(current) == end(visited_)) {
                f(current);
                visited_.insert(current);
            }
            process(current);
        }
    }

protected:
    bool visited(const vertex_type& vertex) const
    {
        return visited_.find(vertex) != end(visited_);
    }

    virtual void process(const vertex_type& vertex) = 0;

    virtual vertex_type get_current_vertex() = 0;

    graph_type g_;
    std::deque<vertex_type> cache_;
    vertex_set visited_;
};

} // namespace stk::algorithms::visitor

#endif // STK_ALGORITHMS_VISITOR_BASE_VISITOR_H
