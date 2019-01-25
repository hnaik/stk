#include "stk/algorithms/lu.h"

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

class LuTest : public ::testing::Test {
protected:
    static constexpr double epsilon = 0.000000000000001;
    using value_type = double;
    using vector_type = std::valarray<value_type>;
    using matrix_type = stk::ds::matrix<value_type>;
    using lu_type = stk::algorithms::lu<value_type>;

    void SetUp() { m_.reshape(3, 3); }

    matrix_type m_{5.0, 4.0, 3.0, 2.0, 3.0, 2.0, 3.0, 4.0, 5.0};
};

TEST_F(LuTest, solveSingle)
{
    lu_type lu{m_};
    const auto solution = lu.solve(std::valarray<double>{1, 2, 3});

    EXPECT_DOUBLE_EQ(-0.75, solution[0]);
    EXPECT_DOUBLE_EQ(1, solution[1]);
    EXPECT_NEAR(0.25, solution[2], epsilon);
}

TEST_F(LuTest, improve)
{
    lu_type lu{m_};
    const auto solution = lu.improve({1, 2, 3});

    EXPECT_DOUBLE_EQ(-0.75, solution[0]);
    EXPECT_DOUBLE_EQ(1, solution[1]);
    EXPECT_NEAR(0.25, solution[2], epsilon);
}

TEST_F(LuTest, solveMultiple)
{
    lu_type lu{m_};
    matrix_type mat{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    mat.reshape(3, 3);

    const auto solution = lu.solve(mat);

    EXPECT_DOUBLE_EQ(-2.0, solution(0, 0));
    EXPECT_DOUBLE_EQ(-2.125, solution(0, 1));
    EXPECT_DOUBLE_EQ(-2.25, solution(0, 2));

    EXPECT_DOUBLE_EQ(2.0, solution(1, 0));
    EXPECT_DOUBLE_EQ(2.5, solution(1, 1));
    EXPECT_DOUBLE_EQ(3.0, solution(1, 2));

    EXPECT_DOUBLE_EQ(1.0, solution(2, 0));
    EXPECT_NEAR(0.875, solution(2, 1), epsilon);
    EXPECT_DOUBLE_EQ(0.75, solution(2, 2));
}

TEST_F(LuTest, inverse)
{
    lu_type lu{m_};
    const auto inv = lu.inverse();

    EXPECT_DOUBLE_EQ(0.4375, inv(0, 0));
    EXPECT_DOUBLE_EQ(-0.5, inv(0, 1));
    EXPECT_DOUBLE_EQ(-0.0625, inv(0, 2));

    EXPECT_DOUBLE_EQ(-0.25, inv(1, 0));
    EXPECT_DOUBLE_EQ(1, inv(1, 1));
    EXPECT_DOUBLE_EQ(-0.25, inv(1, 2));

    EXPECT_NEAR(-0.0625, inv(2, 0), epsilon);
    EXPECT_DOUBLE_EQ(-0.5, inv(2, 1));
    EXPECT_DOUBLE_EQ(0.4375, inv(2, 2));
}

TEST_F(LuTest, det)
{
    lu_type lu{m_};
    EXPECT_DOUBLE_EQ(16.0, lu.det());
}
