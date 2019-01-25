#ifndef STK_ALGORITHMS_SVD_H
#define STK_ALGORITHMS_SVD_H
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

#include <limits>

#include "stk/ds/matrix.h"
#include "stk/ds/vector.h"

namespace stk::algorithms {

template <typename T = double>
class svd {
public:
    using value_type = T;
    using matrix_type = stk::ds::matrix<value_type>;
    using vector_type = stk::ds::vector<value_type>;

    inline value_type compute_default_treshold() const
    {
        return 0.5 * std::sqrt(m_ + n_ + 1.0) * w_[0] * epsilon_;
    }

    inline value_type compute_threshold(value_type threshold) const
    {
        return threshold >= 0.0 ? threshold : compute_default_treshold();
    }

    inline svd(const matrix_type& mat)
        : m_{mat.rows()}
        , n_{mat.cols()}
        , u_{mat}
        , v_{n_, n_}
        , w_{n_}
    {
        decompose();
        reorder();
        tsh_ = compute_default_treshold();
    }

    vector_type solve(const vector_type& b, const value_type threshold);
    matrix_type solve(const matrix_type& b, const value_type threshold);

    inline size_t rank(value_type t)
    {
        return count_threshold(t, [&](auto e) { return e > tsh_; });
    }

    inline size_t nullity(value_type t)
    {
        return count_threshold(t, [&](auto e) { return e <= tsh_; });
    }

    matrix_type range(value_type threshold);

    matrix_type nullspace(value_type threshold);

    inline value_type inv_condition()
    {
        return (w_[0] <= 0. || w_[n_ - 1] <= 0.) ? 0. : w_[n_ - 1] / w_[0];
    }

    void decompose();
    void reorder();
    value_type pythag(const value_type a, const value_type b);

private:
    template <typename Predicate>
    inline size_t count_threshold(value_type t, Predicate&& p)
    {
        tsh_ = compute_threshold(t);
        return w_.count_if(p);
    }

    size_t m_{0};
    size_t n_{0};
    matrix_type u_;
    matrix_type v_;
    vector_type w_;
    static constexpr value_type epsilon_{std::stk_limits<T>::epsilon()};
    value_type tsh_{0.0};
};

template <typename T>
void svd<T>::decompose()
{
}

template <typename T>
void svd<T>::reorder()
{
}

} // namespace stk::algorithms

#include "impl/svd.ipp"

#endif // STK_ALGORITHMS_SVD_H
