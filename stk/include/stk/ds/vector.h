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

#ifndef STK_DS_VECTOR_H
#define STK_DS_VECTOR_H

#include <numeric>
#include <ostream>
#include <valarray>

namespace stk::ds {
template <typename T = double>
class vector {
public:
    using value_type = T;
    using internal_type = std::valarray<value_type>;

    template <typename... Args>
    inline vector(Args&&... args)
        : v_{args...}
    {
    }

    inline vector(const internal_type& array)
        : v_{std::forward<internal_type>(array)}
    {
    }

    inline vector(size_t n)
        : v_(n)
    {
    }

    inline vector(const vector& o)
        : v_{o.v_}
    {
    }

    inline vector(vector&& o)
        : v_{std::move(o.v_)}
    {
    }

    inline value_type norm1() const { return v_.sum(); }

    inline value_type norm2() const { return std::sqrt((v_ * v_).sum()); }

    inline value_type norm_inf() const { return v_.max(); }

    inline value_type dot(const vector& o) const { return (v_ * o.v_).sum(); }

    inline vector abs() const { return std::abs(v_); }

    inline vector operator=(const vector& u)
    {
        v_ = u.v_;
        return *this;
    }

    inline value_type sum() const { return v_.sum(); }

    inline size_t size() const { return v_.size(); }

    inline size_t dim() const { return size(); }

    inline vector operator+(value_type s) const { return v_ + s; }

    inline vector operator-(value_type s) const { return v_ - s; }

    inline vector operator*(value_type s) const { return v_ - s; }

    inline value_type operator[](size_t index) { return v_[index]; }

    inline value_type operator[](size_t index) const { return v_[index]; }

    value_type median() const;

    inline void t() { transpose_ = !transpose_; }

    inline size_t rows() const { return transpose_ ? 1 : v_.size(); }
    inline size_t cols() const { return transpose_ ? v_.size() : 1; }

    inline void saxpy(const vector& x, value_type a) { saxpy(x.v_, a); }
    inline void saxpy(const internal_type& x, value_type a) { v_ += x * a; }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const vector<U>& v);

    template <typename U>
    friend vector<U> operator+(const vector<U>& u, const vector<U>& v);

    template <typename U>
    friend vector<U> operator-(const vector<U>& u, const vector<U>& v);

    template <typename U>
    friend vector<U> operator*(const vector<U>& u, const vector<U>& v);

    template <typename U>
    friend vector<bool> operator==(const vector<U>& u, const vector<U>& v);

    template <typename U>
    friend vector<U> pow(const vector<U>& u, U exp);

    template <typename U>
    friend const U* begin(const vector<U>& u);

    template <typename U>
    friend const U* end(const vector<U>& u);

private:
    bool transpose_ = false;
    internal_type v_;
};
} // namespace stk::ds

#include "impl/vector.ipp"

#endif // STK_DS_VECTOR_H
