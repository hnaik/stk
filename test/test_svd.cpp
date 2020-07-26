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

#include "stk/algorithms/svd.h"

#include <gtest/gtest.h>

#include "stk/ds/matrix.h"
#include "stk/ds/vector.h"

TEST(SvdTest, constructor)
{
    stk::ds::matrix<double> mat{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    mat.reshape(2, 3);

    stk::algorithms::svd<double> svd{mat};
}
