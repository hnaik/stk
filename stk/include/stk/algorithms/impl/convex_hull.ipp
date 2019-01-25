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

#include <type_traits>

#include "stk/geometry/edge.h"

#include <iostream>

namespace stk::algorithms::convex_hull {
template <typename PointContainer>
typename std::decay_t<PointContainer> convex_hull_slow(PointContainer&& points)
{
    using Container = typename std::decay<PointContainer>::type;
    using Edge_type = ds::edge::edge<typename Container::value_type>;
    std::vector<Edge_type> edges;
    auto all_pairs =
        ds::edge::make_from_points(std::forward<Container>(points));
    for(auto& pq : all_pairs) {
        for(const auto& r : points) {
            if(r == pq.p || r == pq.q)
                continue;

            if(pq.placement(r) == Edge_type::Point_placement::left) {
                pq.valid = false;
            }
        }

        if(pq.valid) {
            edges.push_back(pq);
        }
    }

    Container hull;
    for(const auto& e : edges) {
        // We need the size() check because calling back() on empty vector
        // causes crash
        if(hull.size() == 0 || hull.back() != e.p) {
            hull.push_back(e.p);
        }
    }

    return hull;
}

template <typename PointContainer>
typename std::decay_t<PointContainer> convex_hull(PointContainer&& points)
{
    if(points.size() <= 3) {
        return points;
    }

    // This only works for 2D points now
    using container_type = typename std::decay<PointContainer>::type;
    using point_type = typename container_type::value_type;

    auto begin = std::begin(points);
    auto end = std::end(points);

    std::sort(begin, end);

    std::cout << "first point: " << points[0] << "\n";

    const auto pivot = std::stable_partition(
        begin, end, [=](auto p) { return p.y() > points[0].y(); });

    container_type hull(begin, begin + 2);

    [[maybe_unused]] const auto check_last_three =
        [](point_type p1, point_type p2, point_type p3) {

        };

    for(auto itr = begin + 2; itr < pivot; ++itr) {
        auto pi = itr;
        hull.push_back(*pi);
        //        while(std::distance(itr, pivot) > 2 &&
        //              check_last_three(*pi, *(pi - 1), *(pi - 2))) {
        //        }
    }

    return hull;
} // namespace stk::algorithms::convex_hull
} // namespace stk::algorithms::convex_hull
