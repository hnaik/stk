#include "stk/la.h"

#include <gtest/gtest.h>
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

#include "stk/ds/matrix.h"
#include "stk/ds/vector.h"

class LaTest : public ::testing::Test {
protected:
    void SetUp()
    {
        U_.reshape(2, 3);
        V_.reshape(2, 3);
    }

    stk::ds::vector<double> u_{1.0, 2.0, 3.0};
    stk::ds::vector<double> v_{2.0, 4.0, 6.0};

    stk::ds::matrix<> U_{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    stk::ds::matrix<> V_{2.0, 4.0, 6.0, 8.0, 10.0, 12.0};
};

TEST_F(LaTest, norm1)
{
    EXPECT_DOUBLE_EQ(6.0, stk::la::norm1(u_));
    EXPECT_DOUBLE_EQ(12.0, stk::la::norm1(v_));

    //    EXPECT_DOUBLE_EQ(6.0, stk::la::norm1(U_));
}

TEST_F(LaTest, norm2)
{
    EXPECT_DOUBLE_EQ(3.7416573867739413, stk::la::norm2(u_));
    EXPECT_DOUBLE_EQ(7.483314773547883, stk::la::norm2(v_));
}

TEST_F(LaTest, normInf)
{
    EXPECT_DOUBLE_EQ(3.0, stk::la::norm_inf(u_));
    EXPECT_DOUBLE_EQ(6.0, stk::la::norm_inf(v_));
}

TEST_F(LaTest, dot)
{
    //
    EXPECT_DOUBLE_EQ(28, stk::la::dot(u_, v_));
}

TEST_F(LaTest, dist1)
{
    //
    EXPECT_DOUBLE_EQ(6.0, stk::la::dist1(u_, v_));
}

TEST_F(LaTest, dist_inf)
{
    EXPECT_DOUBLE_EQ(3.0, stk::la::dist_inf(u_, v_));
}

TEST_F(LaTest, saxpy)
{
    const auto y = stk::la::saxpy(u_, v_, 10);
    EXPECT_DOUBLE_EQ(12.0, y[0]);
    EXPECT_DOUBLE_EQ(24.0, y[1]);
    EXPECT_DOUBLE_EQ(36.0, y[2]);
}

TEST_F(LaTest, mul)
{
    //
    auto res = stk::la::mul(U_, u_);
    EXPECT_DOUBLE_EQ(14.0, res[0]);
    EXPECT_DOUBLE_EQ(32.0, res[1]);
}
