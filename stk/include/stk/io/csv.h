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

#ifndef STK_IO_CSV_H
#define STK_IO_CSV_H

#include <filesystem>
#include <fstream>
#include <iostream>

#include "stk/geometry/point.h"

namespace stk::io {
template <typename T = double>
class csv {
public:
    using value_type = T;
    using row_type = std::vector<value_type>;
    using table_type = std::vector<row_type>;

    inline csv(bool header = true, const char delimiter = ',')
        : header_{header}
        , delimiter_{delimiter}
    {
    }

    void read(std::istream& in);

    inline void read(const std::filesystem::path& path)
    {
        std::ifstream in{path.c_str()};
        read(in);
    }

    template <typename PointContainer>
    PointContainer table() const;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const csv<U>& object);

private:
    bool header_ = true;
    char delimiter_ = ',';

    std::vector<std::string> columns_;
    table_type table_;
};

template <typename Row>
void write_row(std::ostream& out, Row row);

template <typename U>
std::ostream& operator<<(std::ostream& out, const csv<U>& csv);
} // namespace stk::io

#include "impl/csv.ipp"

#endif // STK_IO_CSV_H
