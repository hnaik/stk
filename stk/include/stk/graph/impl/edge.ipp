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

namespace stk::graph {
template <typename Vertex>
bool operator==(const edge<Vertex>& e1, const edge<Vertex>& e2)
{
    return (e1.u == e2.u && e1.v == e2.v) || (e1.u == e2.v && e1.v == e2.u);
}

template <typename Vertex>
std::ostream& operator<<(std::ostream& os, const edge<Vertex>& e)
{
    os << "(" << e.u << "," << e.v << ")";
    return os;
}

template <typename Vertex>
size_t edge_hasher<Vertex>::operator()(const edge<vertex_type>& e) const
{
    return e.u.hash() ^ e.v.hash();
}

template <typename V, typename E>
std::ostream& operator<<(std::ostream& os, const basic_graph<V, E>& g)
{
    for(const auto& v : g.v_) {
        os << "[" << v << "] ";
        for(const auto& n : v.neighbors) {
            os << n;
        }
        os << "\n";
    }
    return os;
}

} // namespace stk::graph
