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

#ifndef STK_ALGORITHMS_LU_H
#define STK_ALGORITHMS_LU_H

#include "stk/ds/matrix.h"

namespace stk::algorithms {
template <typename T>
class lu {
public:
    using value_type = T;
    using vector_type = std::valarray<value_type>;
    using matrix_type = stk::ds::matrix<value_type>;

    // clang-format off
    /*!
     * Constructor from @c Matrix
     * \param m source @c Matrix
     */
    explicit lu(const matrix_type& m);
    // clang-format on

    /*!
     *
     * \param b
     * \return
     */
    vector_type solve(const vector_type& b);

    /*!
     *
     * \param b
     * \return
     */
    matrix_type solve(const matrix_type& b);

    /*!
     *
     * \return
     */
    matrix_type inverse();

    /*!
     *
     * \return
     */
    value_type det();

    /*!
     *
     * \param b
     */
    vector_type improve(const vector_type& b);

private:
    size_t n_;
    stk::ds::matrix<value_type> lu_;
    std::valarray<size_t> index_;
    const matrix_type& aref;
};

} // namespace stk::algorithms

#include "stk/algorithms/impl/lu.ipp"

#endif // STK_ALGORITHMS_LU_H
