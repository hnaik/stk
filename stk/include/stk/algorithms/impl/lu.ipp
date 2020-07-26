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

#include "stk/utils.h"

namespace stk::algorithms {

template <typename T>
lu<T>::lu(const lu<T>::matrix_type& m)
    : n_{m.rows()}
    , lu_{m}
    , index_(n_)
    , aref{m}
{
    const value_type tiny = std::numeric_limits<value_type>::denorm_min();
    size_t i_max = 0;
    vector_type vv(n_);
    value_type d = 1.0;

    value_type big;
    for(size_t i = 0; i < n_; ++i) {
        big = 0.0;
        for(size_t j = 0; j < n_; ++j) {
            if(double value; (value = abs(lu_(i, j))) > big) {
                big = value;
            }

            if(big == 0.0) {
                throw std::runtime_error{"Singular matrix in LU decomposition"};
            }

            vv[i] = 1.0 / big;
        }
    }

    for(size_t k = 0; k < n_; ++k) {
        big = 0.0;
        for(size_t i = k; i < n_; ++i) {
            if(double temp = vv[i] * abs(lu_(i, k)); temp > big) {
                big = temp;
                i_max = i;
            }
        }

        if(k != i_max) {
            for(size_t j = 0; j < n_; j++) {
                std::swap(lu_(i_max, j), lu_(k, j));
            }

            d = -d;
            vv[i_max] = vv[k];
        }

        index_[k] = i_max;
        if(stk::utils::almost_equal(lu_(k, k), 0.0)) {
            lu_(k, k) = tiny;
        }

        for(size_t i = k + 1; i < n_; ++i) {
            double temp = lu_(i, k) /= lu_(k, k);
            for(size_t j = k + 1; j < n_; ++j) {
                lu_(i, j) -= (temp * lu_(k, j));
            }
        }
    }
}

template <typename T>
typename lu<T>::vector_type lu<T>::solve(const typename lu<T>::vector_type& b)
{
    vector_type x{b};
    value_type sum{0.0};

    int ii = 0;
    for(size_t i = 0; i < n_; ++i) {
        size_t ip = index_[i];
        sum = x[ip];
        x[ip] = x[i];

        if(ii != 0) {
            for(int j = static_cast<int>(ii - 1); j < i; j++) {
                sum -= lu_(i, j) * x[j];
            }
        } else if(sum != 0.0) {
            ii = i + 1;
        }
        x[i] = sum;
    }

    for(int i = n_ - 1; i >= 0; --i) {
        sum = x[i];
        for(int j = i + 1; j < static_cast<int>(n_); ++j) {
            sum -= lu_(i, j) * x[j];
        }

        x[i] = sum / lu_(i, i);
    }

    return x;
}

template <typename T>
typename lu<T>::matrix_type lu<T>::solve(const typename lu<T>::matrix_type& b)
{
    matrix_type x{b.rows(), b.cols()};
    for(size_t j = 0; j < b.cols(); ++j) {
        x.col(j) = solve(b.col(j));
    }

    return x;
}

template <typename T>
typename lu<T>::matrix_type lu<T>::inverse()
{
    return solve(matrix_type::eye(lu_.rows()));
}

template <typename T>
typename lu<T>::value_type lu<T>::det()
{
    value_type det = 1.0;
    for(size_t i = 0; i < n_; ++i) {
        det *= lu_(i, i);
    }

    return det;
}

template <typename T>
typename lu<T>::vector_type lu<T>::improve(const typename lu<T>::vector_type& b)
{
    vector_type x(n_);
    vector_type err(n_);
    for(size_t i = 0; i < n_; ++i) {
        value_type sdp = -b[i];
        for(size_t j = 0; j < n_; ++j) {
            sdp += static_cast<value_type>(aref(i, j)) *
                   static_cast<value_type>(x[j]);
        }
        err[i] = sdp;
    }

    err = solve(err);

    x -= err;

    return x;
}

} // namespace stk::algorithms
