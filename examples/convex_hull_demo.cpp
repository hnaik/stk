/*
 * This file is part of the Computational Geometry Toolkit
 * Copyright (C) 2018 Harish G. Naik <harishgnaik@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <limits>
#include <unordered_set>
#include <utility>
#include <vector>

#include "stk/algorithms/convex_hull.h"
#include "stk/geometry/edge.h"
#include "stk/geometry/point.h"
#include "stk/io/csv.h"
#include "stk/utils.h"

using namespace stk;

using Point_type = stk::ds::Point2<double>;
using Point_container = Point_type::vector;

int main(int __attribute__((unused)) argc, char** argv)
{
    io::csv<> csv;
    csv.read(argv[1]);

    auto points = csv.table<Point_container>();
    const auto slow_hull =
        stk::algorithms::convex_hull::convex_hull_slow(points);
    std::cout << "Slow convex hull\n";
    for(const auto& p : slow_hull) {
        std::cout << p << "\n";
    }

    std::cout << "Convex hull\n";
    const auto hull = stk::algorithms::convex_hull::convex_hull(points);
    for(const auto& p : hull) {
        std::cout << p << "\n";
    }
}
