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

#include <iomanip>

namespace stk::ds {
template <typename U>
std::ostream& operator<<(std::ostream& os, const vector<U>& v)
{
    os << "[ ";
    for(const auto& e : v.v_) {
        os << std::setprecision(4) << std::fixed << e << " ";
    }
    os << "]";

    return os;
}

template <typename U>
vector<U> operator+(const vector<U>& u, const vector<U>& v)
{
    return u.v_ + v.v_;
}

template <typename U>
vector<U> operator-(const vector<U>& u, const vector<U>& v)
{
    return u.v_ - v.v_;
}

template <typename U>
vector<U> operator*(const vector<U>& u, const vector<U>& v)
{
    return u.v_ * v.v_;
}

template <typename U>
vector<bool> operator==(const vector<U>& u, const vector<U>& v)
{
    return u.v_ == v.v_;
}

template <typename U>
vector<U> pow(const vector<U>& u, U exp)
{
    return std::pow(u.v_, exp);
}

template <typename U>
const U* begin(const vector<U>& u)
{
    return std::begin(u.v_);
}

template <typename U>
const U* end(const vector<U>& u)
{
    return std::end(u.v_);
}

template <typename T>
typename vector<T>::value_type vector<T>::median() const
{
    internal_type v{v_};
    std::nth_element(begin(v), begin(v) + v.size() / 2, end(v));
    return v[v.size() / 2];
}

} // namespace stk::ds
