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

#include "stk/stat.h"

#include <gtest/gtest.h>

#include "stk/ds/vector.h"

class StatTest : public ::testing::Test {
protected:
    using vector_type = stk::ds::vector<>;

    vector_type v_{1.0, 3.0, 2.0, 5.0, 9.0, 8.0, 4.0, 6.0, 7.0};
};

TEST_F(StatTest, Sum)
{
    // sum(1, 2, 3, 4, 5, 6, 7, 8, 9)
    EXPECT_DOUBLE_EQ(45.0, stk::stat::sum(v_));
}

TEST_F(StatTest, Count)
{
    //    EXPECT_DOUBLE_EQ(9, stk::stat::count<vector_type>(v_));
    //    EXPECT_DOUBLE_EQ(9, stk::stat::dim<vector_type>(v_));
}

TEST_F(StatTest, Mean)
{
    // mean(1, 2, 3, 4, 5, 6, 7, 8, 9)
    EXPECT_DOUBLE_EQ(5.0, stk::stat::mean(v_));
}

TEST_F(StatTest, Variance)
{
    // var(1, 2, 3, 4, 5, 6, 7, 8, 9)
    EXPECT_DOUBLE_EQ(6.666666666666667, stk::stat::var(v_));
}

TEST_F(StatTest, StdDev)
{
    // stddev(1, 2, 3, 4, 5, 6, 7, 8, 9)
    EXPECT_DOUBLE_EQ(2.581988897471611, stk::stat::sd(v_));
}

TEST_F(StatTest, Median)
{
    // median(1, 2, 3, 4, 5, 6, 7, 8, 9)
    EXPECT_DOUBLE_EQ(5.0, stk::stat::median(v_));
}
