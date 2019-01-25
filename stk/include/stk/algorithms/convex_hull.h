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

#ifndef STK_ALGORITHMS_CONVEX_HULL_H
#define STK_ALGORITHMS_CONVEX_HULL_H

#include <type_traits>

namespace stk::algorithms::convex_hull {
/*!
 * Function to compute a convex hull of a set of points
 * \param points a container of points from which to construct the convex hull
 * \return a container of points that represent the convex hull
 */
template <typename PointContainer>
typename std::decay_t<PointContainer> convex_hull_slow(PointContainer&& points);

/*!
 * Function to compute a convex hull of a set of points
 * \param points a container of points from which to construct the convex hull
 * \return a container of points that represent the convex hull
 */
template <typename PointContainer>
typename std::decay_t<PointContainer> convex_hull(PointContainer&& points);

} // namespace stk::algorithms::convex_hull

#include "stk/algorithms/impl/convex_hull.ipp"

#endif // STK_ALGORITHMS_CONVEX_HULL_H
