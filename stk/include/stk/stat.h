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

#include <algorithm>
#include <cmath>
#include <type_traits>
#include <utility>

#include <stk/concepts.h>
#include <stk/ds/vector.h>

namespace stk::stat {
template <typename T>
inner_value_type<T> sum(T&& series)
{
    return series.sum();
}

template <typename T>
size_t count(T&& series)
{
    return series.size();
}

template <typename T>
size_t dim(T&& series)
{
    return count(series);
}

template <typename T>
inner_value_type<T> mean(T&& series)
{
    return sum(series) / count(series);
}

template <typename T>
inner_value_type<T> var(T&& s)
{
    const auto p = static_cast<inner_value_type<T>>(2);
    return sum(pow(s - mean(s), p)) / count(s);
}

template <typename T>
inner_value_type<T> sd(T&& series)
{
    return std::sqrt(var(series));
}

template <typename T>
inner_value_type<T> median(T&& s)
{
    return s.median();
}

template <typename T>
inner_value_type<T> mean_abs_deviation(T&& s)
{
    return sum((s - mean(s)).abs()) / count(s);
}

namespace detail {
template <typename T>
inner_value_type<T> compute_inner(T&& s, size_t exp)
{
    const auto exp_ = static_cast<inner_value_type<T>>(exp);
    return sum(pow(((s - mean(s)) / sd(s)), exp_)) / count(s);
}
} // namespace detail

template <typename T>
inner_value_type<T> skew(T&& s)
{
    return detail::compute_inner(s, 3);
}

template <typename T>
inner_value_type<T> kurtosis(T&& s)
{
    return detail::compute_inner(s, 4) - static_cast<inner_value_type<T>>(3);
}

template <typename T>
struct moments {
    T mean{};
    T mean_abs_deviation{};
    T stddev{};
    T variance{};
    T skew{};
    T kurtosis{};
};

template <typename T>
moments<typename T::value_type> compute_moments(const T& v)
{
    using value_type = typename T::value_type;
    moments<value_type> m;

    m.mean = mean(v);
    m.variance = var(v);
    m.stddev = sd(v);
    m.mean_abs_deviation = mean_abs_deviation(v);
    m.skew = skew(v);
    m.kurtosis = kurtosis(v);

    return m;
}
} // namespace stk::stat
#endif // STK_STAT_H
