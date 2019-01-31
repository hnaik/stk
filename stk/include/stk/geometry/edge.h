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

#ifndef STK_GEOMETRY_EDGE_H
#define STK_GEOMETRY_EDGE_H

#include <ostream>
#include <vector>

#include "stk/utils.h"

namespace stk::geometry {
/*!
 *
 * \param a
 * \param b
 * \param q
 * \return
 */
template <typename Point>
double det(const Point& a, const Point& b, const Point& q)
{
    // https://stackoverflow.com/questions/1560492/how-to-tell-whether-a-point-is-to-the-right-or-left-side-of-a-line
    return ((b.x() - a.x()) * (q.y() - a.y()) -
            (b.y() - a.y()) * (q.x() - a.x()));
}

/*!
 *
 */
template <typename Point>
struct edge {
    /*!
     *
     */
    enum class Point_placement
    {
        left,
        right,
        on
    };

    /*!
     *
     * \param p_
     * \param q_
     * \param valid_
     */
    inline edge(Point p_, Point q_, bool valid_ = true)
        : p{p_}
        , q{q_}
        , valid{valid_}
    {
    }

    /*!
     *
     * \param r
     * \return
     */
    Point_placement placement(const Point& r) const;

    Point p;
    Point q;
    bool valid;
};

/*!
 *
 */
template <typename PointContainer>
std::vector<edge<typename PointContainer::value_type>>
edges_from_points(PointContainer&& points);

/*!
 *
 */
template <typename Point>
std::ostream& operator<<(std::ostream& out, const edge<Point>& edge);

} // namespace stk::geometry

#include "stk/geometry/impl/edge.ipp"

#endif // STK_GEOMETRY_EDGE_H
