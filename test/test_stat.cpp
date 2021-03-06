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
    using vector_type = stk::ds::vector<double>;

    vector_type v_{1.0, 3.0, 2.0, 5.0, 9.0, 8.0, 4.0, 6.0, 7.0};
};

using namespace stk::stat;

TEST_F(StatTest, Sum)
{
    EXPECT_DOUBLE_EQ(45.0, stk::stat::sum(v_));
}

TEST_F(StatTest, Count)
{
    EXPECT_EQ(count(v_), 9);
}

TEST_F(StatTest, Mean)
{
    EXPECT_DOUBLE_EQ(5.0, stk::stat::mean(v_));
}

TEST_F(StatTest, Variance)
{
    EXPECT_DOUBLE_EQ(6.666666666666667, stk::stat::var(v_));
}

TEST_F(StatTest, StdDev)
{
    EXPECT_DOUBLE_EQ(2.581988897471611, stk::stat::sd(v_));
}

TEST_F(StatTest, Median)
{
    EXPECT_DOUBLE_EQ(5.0, stk::stat::median(v_));
}

TEST_F(StatTest, Moments)
{
    const auto m = compute_moments(v_);

    double epsilon = 0.0000000001;

    EXPECT_EQ(5.0, m.mean);
    EXPECT_EQ(2.2222222222222223, m.mean_abs_deviation);
    EXPECT_EQ(2.581988897471611, m.stddev);
    EXPECT_EQ(6.666666666666667, m.variance);
    EXPECT_NEAR(0, m.skew, epsilon);
    EXPECT_NEAR(-1.23, m.kurtosis, epsilon);
}
