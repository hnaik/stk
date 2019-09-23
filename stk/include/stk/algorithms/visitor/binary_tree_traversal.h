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

#ifndef STK_ALGORITHMS_VISITOR_BINARY_TREE_TRAVERSAL_H
#define STK_ALGORITHMS_VISITOR_BINARY_TREE_TRAVERSAL_H

namespace stk::algorithms::visitor {
template <typename T, typename Function>
void in_order(const T& tree, const typename T::vertex_type& vertex,
              Function&& visit)
{
    if(!tree.has_neighbors(vertex)) {
        visit(vertex);
        return;
    }

    auto itr = begin(tree.neighbors(vertex));
    in_order(tree, *itr, visit);
    visit(vertex);
    ++itr;
    in_order(tree, *itr, visit);
}

template <typename T, typename Function>
void pre_order(const T& tree, const typename T::vertex_type& vertex,
               Function&& visit)
{
    if(!tree.has_neighbors(vertex)) {
        visit(vertex);
        return;
    }

    visit(vertex);
    auto itr = begin(tree.neighbors(vertex));
    pre_order(tree, *itr, visit);
    ++itr;
    pre_order(tree, *itr, visit);
}

template <typename T, typename Function>
void post_order(const T& tree, const typename T::vertex_type& vertex,
                Function&& visit)
{
    if(!tree.has_neighbors(vertex)) {
        visit(vertex);
        return;
    }

    auto itr = begin(tree.neighbors(vertex));
    post_order(tree, *itr, visit);
    ++itr;
    post_order(tree, *itr, visit);
    visit(vertex);
}

} // namespace stk::algorithms::visitor

#endif // STK_ALGORITHMS_VISITOR_BINARY_TREE_TRAVERSAL_H
