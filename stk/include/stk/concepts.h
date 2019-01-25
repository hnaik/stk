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

#ifndef STK_CONCEPTS_H
#define STK_CONCEPTS_H

#include <iterator>

namespace stk {
template <typename T>
using inner_value_type = typename std::decay<T>::type::value_type;

// clang-format off
template <typename T>
concept bool Tensor = requires(T t){
    { t.norm1() } -> inner_value_type<T>;
    { t.norm2() } -> inner_value_type<T>;
    { t.norm_inf() } -> inner_value_type<T>;
    { t.abs() };
    { t.operator=(t) };

    // Disabled because return types are different for Vector and Matrix types
    // { t.dot(t) } -> inner_value_type<T>;
};

template <typename T>
concept bool Series = requires(T t){
//    { std::begin(t) };
//    { std::end(t) };
    { t.sum() } -> inner_value_type<T>;
};

// clang-format on

} // namespace stk

#endif // STK_CONCEPTS_H
