#ifndef STK_ALGORITHMS_VISITOR_VISITOR_H
#define STK_ALGORITHMS_VISITOR_VISITOR_H

#include "stk/algorithms/visitor/base_visitor.h"
#include "stk/algorithms/visitor/bfs.h"
#include "stk/algorithms/visitor/dfs.h"

namespace stk::algorithms::visitor {

template <typename Graph>
using visitor = base_visitor<Graph>;

} // namespace stk::algorithms::visitor

#endif // STK_ALGORITHMS_VISITOR_VISITOR_H
