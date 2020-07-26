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

#include <cassert>
#include <iomanip>

namespace stk::ds {
template <typename U>
std::ostream& operator<<(std::ostream& os, const std::valarray<U>& v)
{
    const size_t default_precision = os.precision();
    os << "[ ";
    for(const auto& e : v) {
        os << std::setw(8) << std::right << std::setprecision(4) << std::fixed
           << e << " ";
    }
    os << ']';

    os << std::setprecision(default_precision) << std::defaultfloat;

    return os;
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const matrix<U>& m)
{
    const auto default_precision = os.precision();
    for(std::size_t i = 0; i < m.row_count_; ++i) {
        os << (i == 0 ? "[ " : " ");
        for(std::size_t j = 0; j < m.col_count_; ++j) {
            os << std::setw(12) << std::right << std::setprecision(4)
               << std::fixed << m.v_[i * m.col_count_ + j] << "  ";
        }
        os << (i == m.row_count_ - 1 ? ']' : '\n');
    }

    os << std::setprecision(default_precision) << std::defaultfloat;

    return os;
}

template <typename T>
matrix<T> matrix<T>::transpose() const
{
    matrix t{col_count_, row_count_};
    for(size_t i = 0; i < row_count_; ++i) {
        for(size_t j = 0; j < col_count_; ++j) {
            t(j, i) = get(i, j);
        }
    }

    return t;
}

template <typename T>
/* static */ matrix<T> matrix<T>::prod(const matrix<T>& a, const matrix<T>& b)
{
    assert(a.cols() == b.rows());

    matrix<T> m{a.rows(), b.cols()};
    for(size_t i = 0; i < a.rows(); ++i) {
        for(size_t j = 0; j < b.cols(); ++j) {
            for(size_t k = 0; k < a.cols(); ++k) {
                m(i, j) += a(i, k) * b(k, j);
            }
        }
    }
    return m;
}

template <typename U>
matrix<U> operator+(const matrix<U>& a, const matrix<U>& b)
{
    matrix<U> r(a.row_count_, a.col_count_);
    r.v_ = a.v_ + b.v_;
    return r;
}

template <typename U>
matrix<U> operator-(const matrix<U>& a, const matrix<U>& b)
{
    matrix<U> r(a.row_count_, a.col_count_);
    r.v_ = a.v_ - b.v_;
    return r;
}

template <typename U>
matrix<U> operator*(const matrix<U>& a, const matrix<U>& b)
{
    return matrix<U>::prod(a, b);
}

template <typename U>
bool operator==(const matrix<U>& a, const matrix<U>& b)
{
    if(a.v_.size() != b.v_.size())
        return false;

    for(size_t i = 0; i < a.v_.size(); ++i) {
        if(a.v_[i] != b.v_[i])
            return false;
    }

    return true;
}

template <typename U>
bool operator!=(const matrix<U>& a, const matrix<U>& b)
{
    return !(a == b);
}

template <typename T>
matrix<T>& matrix<T>::operator+=(const matrix<T>& m)
{
    v_ += m.v_;
    return *this;
}

template <typename T>
matrix<T>& matrix<T>::operator-=(const matrix<T>& m)
{
    v_ -= m.v_;
    return *this;
}

template <typename T>
matrix<T> matrix<T>::eye(size_t dim)
{
    matrix<T> m{dim, dim};
    m.zero();

    for(std::size_t i = 0; i < dim; ++i) {
        m(i, i) = 1.0;
    }

    return m;
}

template <typename T>
typename matrix<T>::value_type matrix<T>::norm1() const
{
    throw std::runtime_error{"unimplemeted"};
}

template <typename T>
typename matrix<T>::value_type matrix<T>::norm2() const
{
    throw std::runtime_error{"unimplemeted"};
}

template <typename T>
typename matrix<T>::value_type matrix<T>::norm_inf() const
{
    throw std::runtime_error{"unimplemeted"};
}

} // namespace stk::ds
