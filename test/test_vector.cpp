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

#include <gtest/gtest.h>

#include "stk/ds/vector.h"

class VectorTest : public ::testing::Test {
protected:
    std::valarray<double> va_u_{1.0, 2.0, 3.0};
    std::valarray<double> va_v_{2.0, 4.0, 6.0};

    stk::ds::vector<double> u_{va_u_};
    stk::ds::vector<double> v_{va_v_};
};

TEST_F(VectorTest, norm1)
{
    EXPECT_DOUBLE_EQ(6.0, u_.norm1());
    EXPECT_DOUBLE_EQ(12.0, v_.norm1());
}

TEST_F(VectorTest, norm2)
{
    EXPECT_DOUBLE_EQ(3.7416573867739413, u_.norm2());
    EXPECT_DOUBLE_EQ(7.483314773547883, v_.norm2());
}

TEST_F(VectorTest, norm_inf)
{
    EXPECT_DOUBLE_EQ(3.0, u_.norm_inf());
    EXPECT_DOUBLE_EQ(6.0, v_.norm_inf());
}

TEST_F(VectorTest, dot)
{
    EXPECT_EQ(28, u_.dot(v_));
    EXPECT_EQ(28, v_.dot(u_));
}

TEST_F(VectorTest, OperatorPlus) {}
