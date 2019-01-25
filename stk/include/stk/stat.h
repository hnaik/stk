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

#ifndef STK_STAT_H
#define STK_STAT_H

#include <cmath>
#include <type_traits>

#include <algorithm>
#include <vector>

#include "concepts.h"

namespace stk::stat {
template <Series T>
inner_value_type<T> sum(T&& series)
{
    return series.sum();
}

template <Series T>
size_t count(T&& series)
{
    return series.size();
}

template <Series T>
size_t dim(T&& series)
{
    return count(series);
}

template <Series T>
inner_value_type<T> mean(T&& series)
{
    return sum(series) / static_cast<inner_value_type<T>>(count(series));
}

template <Series T>
inner_value_type<T> var(T&& s)
{
    return sum(pow(s - mean(s), 2.0)) / count(s);
}

template <Series T>
inner_value_type<T> sd(T&& series)
{
    return std::sqrt(var(series));
}

template <Series T>
inner_value_type<T> median(T&& s)
{
    return s.median();
}
} // namespace stk::stat
#endif // STK_STAT_H
