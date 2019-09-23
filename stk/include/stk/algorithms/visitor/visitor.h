#ifndef STK_ALGORITHMS_VISITOR_VISITOR_H
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

#define STK_ALGORITHMS_VISITOR_VISITOR_H

#include "stk/algorithms/visitor/base_visitor.h"
#include "stk/algorithms/visitor/bfs.h"
#include "stk/algorithms/visitor/dfs.h"

namespace stk::algorithms::visitor {

template <typename Graph>
using visitor = base_visitor<Graph>;

} // namespace stk::algorithms::visitor

#endif // STK_ALGORITHMS_VISITOR_VISITOR_H
