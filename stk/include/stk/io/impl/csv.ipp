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

#include <iostream>
#include <istream>

#include "stk/geometry/point.h"

namespace stk::io {
template <typename T>
void csv<T>::read(std::istream& in)
{
    size_t line_idx{0};
    std::string token;
    std::vector<value_type> row;
    while(!in.eof()) {
        const char c = in.get();

        if(c == delimiter_) {
            if(header_ == true && line_idx == 0) {
                columns_.push_back(token);
            } else {
                value_type value =
                    static_cast<value_type>(std::atof(token.c_str()));
                row.push_back(value);
            }
            token.clear();
        } else {
            token.push_back(c);
        }

        if(c == '\n') {
            token.pop_back();

            if(header_ == true && line_idx == 0) {
                columns_.push_back(token);
            } else {
                value_type value =
                    static_cast<value_type>(std::atof(token.c_str()));
                row.push_back(value);
                table_.push_back(row);
                row.clear();
            }

            token.clear();
            ++line_idx;
        }
    }
}

template <typename T>
template <typename PointContainer>
PointContainer csv<T>::table() const
{
    PointContainer points;
    for(const auto& row : table_) {
        points.emplace_back(row);
    }

    return points;
}

template <typename Row>
void write_row(std::ostream& out, Row row)
{
    std::vector<typename Row::value_type> v{row};
    for(size_t idx = 0; idx < row.size(); ++idx) {
        out << v[idx];
        if(idx < v.size() - 1) {
            out << ',';
        }
    }
}

template <typename U>
std::ostream& operator<<(std::ostream& out, const csv<U>& object)
{
    if(object.header_) {
        write_row(out, object.columns_);
        out << "\n";
    }

    for(const auto& row : object.table_) {
        write_row(out, row);
        out << "\n";
    }
    return out;
}
} // namespace stk::io
