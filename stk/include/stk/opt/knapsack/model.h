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

/*
 * Adapted from:
 * Kellerer H., Pferschy U., Pisinger D. (2004) The Bounded Knapsack Problem.
 * In: Knapsack Problems. Springer, Berlin, Heidelberg
 */

#ifndef STK_OPT_KNAPSACK_SOLVER_H
#define STK_OPT_KNAPSACK_SOLVER_H

#include <algorithm>
#include <cmath>
#include <string_view>

#include <iostream>

#include "stk/opt/knapsack/input.h"
#include "stk/opt/knapsack/result.h"

namespace stk::opt::knapsack {
template <typename T>
double efficiency(const item<T>& item)
{
    return static_cast<double>(item.value) / static_cast<double>(item.weight);
}

template <typename T>
struct efficiency_greater {
    bool operator()(const item<T>& a, const item<T>& b)
    {
        return efficiency(a) > efficiency(b);
    }
};

template <typename T>
struct efficiency_lesser {
    bool operator()(const item<T>& a, const item<T>& b)
    {
        return efficiency(a) < efficiency(b);
    }
};

template <typename T>
class model {
public:
    virtual ~model() = default;

    virtual result<T> solve(const input<T>& input) = 0;
};

template <typename T>
class zero_one : public model<T> {
public:
    result<T> solve(const input<T>& input) override;
};

template <typename T>
result<T> zero_one<T>::solve(const input<T>& input)
{
    using value_type = typename input<T>::value_type;
    typename input<T>::container_type items{input.items()};

    std::sort(begin(items), end(items), efficiency_greater<T>());

    result<T> result{input.item_count()};
    value_type remaining_capacity = input.capacity();
    for(const auto& item : items) {
        if(remaining_capacity >= item.weight) {
            remaining_capacity -= item.weight;
            result.z += item.value;

            result.solution[item.index] = 1;
        }
    }

    return result;
}

/*!
 * Bounded Knapsack
 */
template <typename T>
class bkp : public model<T> {
public:
    result<T> solve(const input<T>& input) override;
};

template <typename T>
constexpr size_t floor_operation(T c, T w_bar, T w)
{
    auto frac = static_cast<double>(c - w_bar) / static_cast<double>(w);
    return static_cast<size_t>(std::floor(frac));
}

template <typename T>
result<T> bkp<T>::solve(const input<T>& input)
{
    using value_type = typename input<T>::value_type;
    typename input<T>::container_type items{input.items()};

    std::sort(begin(items), end(items), efficiency_greater<T>());

    result<T> res{input.item_count()};

    value_type w_ = 0;
    for(const auto& item : items) {
        if((w_ + item.weight) <= input.capacity()) {
            value_type x =
                std::min(item.copies,
                         floor_operation(input.capacity(), w_, item.weight));
            w_ += item.weight * x;
            res.z += item.value * x;

            res.solution[item.index] = x;
        }
    }

    return res;
}

template <typename T>
class branch_and_bound : public model<T> {
    result<T> solve(const input<T>& input) override;
};

template <typename T>
result<T> branch_and_bound<T>::solve(const input<T>& input)
{
    result<T> soln{input.item_count()};

    return soln;
}

} // namespace stk::opt::knapsack
#endif // STK_OPT_KNAPSACK_SOLVER_H
