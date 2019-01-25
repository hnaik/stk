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

#include <ostream>

namespace stk::geometry {
/*!
 *
 */
template <typename T, size_t N>
std::ostream& operator<<(std::ostream& out, const point<T, N>& p)
{
    out << "(";
    for(size_t i = 0; i < N; ++i) {
        out << p.v_[i];
        if(i < (N - 1)) {
            out << ",";
        }
    }
    out << ")";

    return out;
}

/*!
 *
 */
template <typename T, size_t N>
bool operator<(const point<T, N>& a, const point<T, N>& b)
{
    for(size_t i = 0; i < N; ++i) {
        if(a.v_[i] < b.v_[i]) {
            return true;
        } else if(a.v_[i] > b.v_[i]) {
            break;
        }
    }

    return false;
}

/*!
 *
 */
template <typename T, size_t N>
bool operator==(const point<T, N>& a, const point<T, N>& b)
{
    for(size_t i = 0; i < N; ++i) {
        if(!utils::almost_equal(a.v_[i], b.v_[i])) {
            return false;
        }
    }

    return true;
}

/*!
 *
 */
template <typename T, size_t N>
bool operator!=(const point<T, N>& a, const point<T, N>& b)
{
    return !(a == b);
}
} // namespace stk::geometry
