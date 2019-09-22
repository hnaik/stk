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
