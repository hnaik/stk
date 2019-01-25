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

#include <ostream>

#include "stk/geometry/point.h"

namespace stk::ds::edge {
template <typename Point>
typename edge<Point>::Point_placement
edge<Point>::placement(const Point& r) const
{
    const auto det = determinant(p, q, r);
    if(stk::utils::almost_equal(det, 0.0))
        return Point_placement::on;
    if(det < 0.0)
        return Point_placement::right;

    return Point_placement::left;
}

template <typename PointContainer>
std::vector<edge<typename PointContainer::value_type>>
make_from_points(PointContainer&& points)
{
    std::vector<edge<typename PointContainer::value_type>> edges;
    for(const auto& p : points) {
        for(const auto& q : points) {
            if(p == q)
                continue;
            edges.emplace_back(p, q);
        }
    }

    return edges;
}

template <typename Point>
std::ostream& operator<<(std::ostream& out, const edge<Point>& edge)
{
    out << edge.p << "->" << edge.q;
    return out;
}

} // namespace stk::ds::edge
