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

#ifndef STK_LA_H
#define STK_LA_H

#include <utility>

#include "stk/concepts.h"

namespace stk::la {
template <typename T>
using inner_value_type = typename std::decay_t<T>::value_type;

template <Tensor T>
inline inner_value_type<T> norm1(T&& t)
{
    return t.norm1();
}

template <Tensor T>
inline inner_value_type<T> norm2(T&& t)
{
    return t.norm2();
}

template <Tensor T>
inline inner_value_type<T> norm_inf(T&& t)
{
    return t.norm_inf();
}

template <Tensor T>
inline inner_value_type<T> dot(T&& u, T&& v)
{
    return u.dot(v);
}

template <Tensor T>
inline inner_value_type<T> dist1(T&& u, T&& v)
{
    return (u - v).abs().norm1();
}

template <Tensor T>
inline inner_value_type<T> dist2(T&& u, T&& v)
{
    return (u - v).abs().norm2();
}

template <Tensor T>
inline inner_value_type<T> dist_inf(T&& u, T&& v)
{
    return (u - v).abs().norm_inf();
}

template <Tensor T>
T saxpy(const T& x, const T& y, inner_value_type<T> a)
{
    T s{y};
    s.saxpy(x, a);
    return s;
}

template <typename MatrixType>
inline MatrixType mul(const MatrixType& a, const MatrixType& b)
{
    return a * b;
}

template <typename MatrixType, typename VectorType>
void gaxpy(const MatrixType& a, const VectorType& x, VectorType& y)
{
    for(size_t i = 0; i < x.size(); ++i) {
        y.saxpy(a.col(i), x[i]);
    }
}

template <typename MatrixType, typename VectorType>
VectorType mul(const MatrixType& m, const VectorType& v)
{
    VectorType res{v.size()};
    gaxpy(m, v, res);
    return res;
}

template <typename MatrixType, typename VectorType>
inline VectorType gaxpy(const MatrixType& m, const VectorType& v)
{
    return mul(m, v);
}

template <typename MatrixType, typename VectorType>
VectorType gaxpy(const MatrixType& a, const VectorType& x, const VectorType& y)
{
    VectorType g{y};
    gaxpy(a, x, g);
    return g;
}

} // namespace stk::la

#endif // STK_LA_H
