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

#ifndef STK_DS_MATRIX_H
#define STK_DS_MATRIX_H

#include <cassert>
#include <cstddef>
#include <ostream>
#include <string_view>
#include <valarray>

#include <iostream>

namespace stk::ds {
template <typename T = double>
class matrix {
public:
    using value_type = T;
    using internal_type = std::valarray<value_type>;

    /*!
     *
     * \param m
     * \param n
     */
    inline matrix(std::size_t m, std::size_t n)
        : v_(m * n)
        , row_count_{m}
        , col_count_{n}
    {
    }

    /*!
     * \tparam Args...
     * \param args...
     */
    template <typename... Args>
    inline matrix(Args&&... args)
        : v_{args...}
        , row_count_{1}
    {
        // We need to initialize here instead of the initializer list because
        // the only way to do that would be to use a sizeof...(args) which will
        // return 1 when an already initialized container of valarray is passed
        // instead of the number of elements in the array
        col_count_ = v_.size();
    }

    /*!
     *
     * \return
     */
    inline std::size_t size() const { return v_.size(); }

    /*!
     *
     */
    inline void zero() { v_ = 0; }

    /*!
     *
     * \param m
     * \param n
     */
    inline void reshape(std::size_t m, std::size_t n)
    {
        assert((m * n) == v_.size());
        row_count_ = m;
        col_count_ = n;
    }

    /*!
     *
     * \param r
     * \return
     */
    inline std::slice_array<value_type> row(size_t r)
    {
        return v_[std::slice(r * col_count_, col_count_, 1)];
    }

    inline std::slice_array<value_type> operator()(size_t r, std::string_view)
    {
        return row(r);
    }

    /*!
     *
     * \param r
     * \return
     */
    inline internal_type row(std::size_t r) const
    {
        return v_[std::slice(r * col_count_, col_count_, 1)];
    }

    inline internal_type operator()(std::size_t r, std::string_view) const
    {
        return row(r);
    }

    /*!
     *
     * \param c
     * \return
     */
    inline std::slice_array<value_type> col(std::size_t c)
    {
        return v_[std::slice(c, row_count_, col_count_)];
    }

    inline std::slice_array<value_type> operator()(std::string_view,
                                                   std::size_t c)
    {
        return col(c);
    }

    /*!
     *
     * \param c
     * \return
     */
    inline std::valarray<value_type> col(std::size_t c) const
    {
        return v_[std::slice(c, row_count_, col_count_)];
    }

    inline internal_type operator()(std::string_view, std::size_t c) const
    {
        return col(c);
    }

    /*!
     *
     * \param r
     * \param c
     * \return
     */
    inline value_type& get(std::size_t r, std::size_t c)
    {
        return v_[r * col_count_ + c];
    }

    /*!
     *
     * \param r
     * \param c
     * \return
     */
    inline const value_type& get(std::size_t r, std::size_t c) const
    {
        return v_[r * col_count_ + c];
    }

    /*!
     *
     * \param r
     * \param c
     * \return
     */
    inline value_type& operator()(std::size_t r, std::size_t c)
    {
        return get(r, c);
    }

    /*!
     *
     * \param r
     * \param c
     * \return
     */
    inline const value_type& operator()(std::size_t r, std::size_t c) const
    {
        return get(r, c);
    }

    /*!
     *
     * \param v
     */
    inline void operator=(const std::valarray<value_type>& v) { v_ = v; }

    /*!
     *
     * \return
     */
    inline std::size_t rows() const { return row_count_; }

    /*!
     *
     * \return
     */
    inline std::size_t cols() const { return col_count_; }

    /*!
     *
     * \return
     */
    matrix transpose() const;

    /*!
     *
     * \param a
     * \param b
     * \return
     */
    static matrix prod(const matrix& a, const matrix& b);

    value_type norm1() const;

    value_type norm2() const;

    value_type norm_inf() const;

    matrix dot(const matrix& m) const;

    matrix abs() const;

    /*!
     *
     * \param m
     * \return
     */
    matrix& operator+=(const matrix& m);

    /*!
     *
     * \param m
     * \return
     */
    matrix& operator-=(const matrix& m);

    /*!
     *
     */
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const matrix<U>& m);

    /*!
     *
     */
    template <typename U>
    friend matrix<U> operator+(const matrix<U>& a, const matrix<U>& b);

    /*!
     *
     */
    template <typename U>
    friend matrix<U> operator-(const matrix<U>& a, const matrix<U>& b);

    /*!
     *
     */
    template <typename U>
    friend matrix<U> operator*(const matrix<U>& a, const matrix<U>& b);

    /*!
     *
     */
    template <typename U>
    friend bool operator==(const matrix<U>& a, const matrix<U>& b);

    /*!
     *
     */
    template <typename U>
    friend bool operator!=(const matrix<U>& a, const matrix<U>& b);

    /*!
     *
     * \param dim
     * \return
     */
    static matrix eye(size_t dim);

private:
    std::valarray<value_type> v_;
    std::size_t row_count_{0};
    std::size_t col_count_{0};
};

/*!
 *
 */
template <typename U>
std::ostream& operator<<(std::ostream& os, const std::valarray<U>& v);

} // namespace stk::ds

#include "stk/ds/impl/matrix.ipp"

#endif // STK_DS_MATRIX_H
