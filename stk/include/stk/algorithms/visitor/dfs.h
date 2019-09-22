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
