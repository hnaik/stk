#ifndef STK_DS_GRAPH_GRAPH_H
#define STK_DS_GRAPH_GRAPH_H

#include <unordered_map>
#include <unordered_set>

namespace stk::ds::graph {
template <typename Vertex>
class graph {
public:
    using vertex_type = Vertex;
    using set = std::unordered_set<vertex_type>;

    void add_vertex(const vertex_type& vertex, const set& neighbors)
    {
        for(const auto& neighbor : neighbors) {
            g_[vertex].insert(neighbor);
        }
    }

    const set& neighbors(const vertex_type& vertex) const
    {
        return g_.at(vertex);
    }

public:
    std::unordered_map<vertex_type, set> g_;
};

} // namespace stk::ds::graph

#endif // STK_DS_GRAPH_GRAPH_H
