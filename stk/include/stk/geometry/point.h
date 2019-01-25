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

#ifndef STK_GEOMETRY_POINT_H
#define STK_GEOMETRY_POINT_H

#include <functional>
#include <numeric>
#include <ostream>
#include <type_traits>
#include <unordered_set>
#include <valarray>
#include <vector>

#include "stk/utils.h"

namespace stk::geometry {
/*!
 * Class to represent a point
 */
template <typename T, size_t N = 3>
class point {
public:
    static constexpr size_t dim_count = N;
    using vector = std::vector<point>;

    /// Default constructor
    inline point()
        : v_{N}
    {
    }

    /*!
     * Constructor taking a variable number of coordinate values
     * \tparam Args... variadic arguments
     * \param[in] coordinate values
     */
    template <typename... Args>
    inline point(Args... args)
        : v_{args...}
    {
    }

    /*!
     * Constructor to create point from a vector of values
     * \param[in] v @c vector of values
     */
    explicit inline point(const std::vector<T>& v)
        : v_{v.data(), v.size()}
    {
    }

    /*!
     * Accessor function for first dimension, X, for convenience
     * \return value of the first dimension
     */
    inline T x() const { return v_[0]; }

    /*!
     * Accessor function for second dimension, Y, for convenience
     * \return value of the second dimension
     */
    inline T y() const { return v_[1]; }

    /*!
     * Accessor function for third dimension, Z, for convenience. This function
     * is generated only if the point has more than 2 dimensions, else gets
     * erased
     * \tparam U value_type (=T)
     * \tparam M number of dimensions (=N)
     * \return value of the third dimension
     */
    template <typename U = T, size_t M = N>
    inline typename std::enable_if_t<(M > 2), U> z() const
    {
        return v_[2];
    }

    /*!
     * Setter function for the first dimension X
     * \param x value to set the first dimension
     */
    inline void set_x(T x) { v_[0] = x; }

    /*!
     * Setter function for the second dimension Y
     * \param y value to set the second dimension
     */
    inline void set_y(T y) { v_[1] = y; }

    /*!
     * Setter function for the third dimension Z. This function is generated
     * only if the point has more than 2 dimensions, else gets erased
     * \param y value to set the third dimension
     */
    template <typename U = T, size_t M = N>
    inline typename std::enable_if_t<(M > 2)> set_z(U z)
    {
        v_[2] = z;
    }

    /*!
     *
     */
    template <typename U, size_t M>
    friend std::ostream& operator<<(std::ostream& out, const point<U, M>& p);

    /*!
     *
     */
    template <typename U, size_t M>
    friend bool operator<(const point<U, M>& a, const point<U, M>& b);

    /*!
     *
     */
    template <typename U, size_t M>
    friend bool operator==(const point<U, M>& a, const point<U, M>& b);

    /*!
     *
     */
    template <typename U, size_t M>
    friend bool operator!=(const point<U, M>& a, const point<U, M>& b);

    /*!
     *
     */
    template <typename U, size_t M>
    friend U determinant(const point<U, M>& a, const point<U, M>& b,
                         const point<U, M>& c);

private:
    std::valarray<T> v_;
};

template <typename T = double>
using Point2 = point<T, 2>;

template <typename T = double>
using Point3 = point<T, 3>;

/*!
 *
 */
template <typename T, size_t N>
std::ostream& operator<<(std::ostream& out, const point<T, N>& p);

/*!
 *
 */
template <typename T, size_t N>
bool operator<(const point<T, N>& a, const point<T, N>& b);

/*!
 *
 */
template <typename T, size_t N>
bool operator==(const point<T, N>& a, const point<T, N>& b);

/*!
 *
 */
template <typename T, size_t N>
bool operator!=(const point<T, N>& a, const point<T, N>& b);

template <typename U, size_t M>
U determinant(const point<U, M>& a, const point<U, M>& b, const point<U, M>& c)
{
    return ((b.x() - a.x()) * (c.y() - a.y()) -
            (b.y() - a.y()) * (c.x() - a.x()));
}

} // namespace stk::geometry

#include "stk/geometry/impl/point.ipp"

#endif // STK_GEOMETRY_POINT_H
