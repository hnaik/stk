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
#include "stk/opt/knapsack/solution.h"

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

    virtual solution<T> solve(const input<T>& input) = 0;
};

template <typename T>
class zero_one : public model<T> {
public:
    solution<T> solve(const input<T>& input) override;
};

template <typename T>
solution<T> zero_one<T>::solve(const input<T>& input)
{
    using value_type = typename input<T>::value_type;
    typename input<T>::container_type items{input.items()};

    std::sort(begin(items), end(items), efficiency_greater<T>());

    solution<T> solution{input.item_count()};
    value_type remaining_capacity = input.capacity();
    for(const auto& item : items) {
        if(remaining_capacity >= item.weight) {
            remaining_capacity -= item.weight;
            solution.z += item.value;

            solution.picked[item.index] = 1;
        }
    }

    return solution;
}

/*!
 * Bounded Knapsack
 */
template <typename T>
class bkp : public model<T> {
public:
    solution<T> solve(const input<T>& input) override;
};

template <typename T>
constexpr size_t floor_operation(T c, T w_bar, T w)
{
    auto frac = static_cast<double>(c - w_bar) / static_cast<double>(w);
    return static_cast<size_t>(std::floor(frac));
}

template <typename T>
solution<T> bkp<T>::solve(const input<T>& input)
{
    using value_type = typename input<T>::value_type;
    typename input<T>::container_type items{input.items()};

    std::sort(begin(items), end(items), efficiency_greater<T>());

    solution<T> soln{input.item_count()};

    value_type w_ = 0;
    for(const auto& item : items) {
        if((w_ + item.weight) <= input.capacity()) {
            value_type x =
                std::min(item.copies,
                         floor_operation(input.capacity(), w_, item.weight));
            w_ += item.weight * x;
            soln.z += item.value * x;

            soln.picked[item.index] = x;
        }
    }

    return soln;
}

template <typename T>
class solver_factory {
public:
    using value_type = T;

    inline solver_factory(std::string_view solver_id, std::string_view input_id)
        : solver_id_{solver_id}
        , input_id_{input_id}
    {
    }

    std::shared_ptr<input<value_type>> input_handle() const;

    std::shared_ptr<model<value_type>> solver_handle() const;

private:
    std::string_view solver_id_;
    std::string_view input_id_;
};

template <typename T>
std::shared_ptr<input<T>> solver_factory<T>::input_handle() const
{
    return create_input<T>(input_id_);
}

template <typename T>
std::shared_ptr<model<T>> solver_factory<T>::solver_handle() const
{
    if(solver_id_ == "zero_one") {
        return std::make_shared<zero_one<T>>();
    } else if(solver_id_ == "bkp") {
        return std::make_shared<bkp<T>>();
    }

    throw std::runtime_error{"unsupported solver type"};
}

} // namespace stk::opt::knapsack
#endif // STK_OPT_KNAPSACK_SOLVER_H
