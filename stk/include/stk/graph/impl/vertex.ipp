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

namespace stk::graph {
template <typename Id>
size_t vertex<Id>::hash() const
{
    return vertex_hasher<Id>{}(id);
}

template <typename Id>
bool operator==(const vertex<Id>& v1, const vertex<Id>& v2)
{
    return v1.id == v2.id;
}

template <typename Id>
std::ostream& operator<<(std::ostream& os, const vertex<Id>& v)
{
    os << v.id;
    return os;
}

template <typename Id>
size_t vertex_hasher<Id>::operator()(const vertex<Id>& v) const
{
    return std::hash<std::string>{}(v.id);
}

} // namespace stk::graph
