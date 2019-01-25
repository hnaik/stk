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

#include <gtest/gtest.h>

class MatrixTest : public ::testing::Test {
protected:
    using value_type = double;
    using matrix_type = stk::ds::matrix<value_type>;

    void SetUp() { fill_matrix(m_); }

    static stk::ds::matrix<double> create_matrix()
    {
        matrix_type test_m{row_count_, col_count_};
        fill_matrix(test_m);
        return test_m;
    }

    static void fill_matrix(matrix_type& m)
    {
        value_type count{1.0};
        for(size_t i = 0; i < row_count_; ++i) {
            for(size_t j = 0; j < col_count_; ++j) {
                m(i, j) = count;
                ++count;
            }
        }
    }

    static constexpr size_t row_count_ = 3;
    static constexpr size_t col_count_ = 4;
    matrix_type m_{row_count_, col_count_};
};

TEST_F(MatrixTest, ConstructorVariadic)
{
    stk::ds::matrix<> m{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

    EXPECT_EQ(1, m.rows());
    EXPECT_EQ(6, m.cols());

    m.reshape(2, 3);

    EXPECT_EQ(2, m.rows());
    EXPECT_EQ(3, m.cols());
}

TEST_F(MatrixTest, ConstructorValarray)
{
    { // r-value
        stk::ds::matrix<> m{
            std::valarray<double>{1.0, 2.0, 3.0, 4.0, 5.0, 6.0}};

        EXPECT_EQ(1, m.rows());
        EXPECT_EQ(6, m.cols());

        m.reshape(2, 3);

        EXPECT_EQ(2, m.rows());
        EXPECT_EQ(3, m.cols());
    }

    { // l-value
        std::valarray<double> v{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
        stk::ds::matrix<> m{v};

        EXPECT_EQ(1, m.rows());
        EXPECT_EQ(6, m.cols());

        m.reshape(2, 3);

        EXPECT_EQ(2, m.rows());
        EXPECT_EQ(3, m.cols());
    }
}

TEST_F(MatrixTest, size)
{ //
    EXPECT_EQ(12, m_.size());
}

TEST_F(MatrixTest, zero)
{
    m_.zero();
    for(size_t i = 0; i < m_.rows(); ++i) {
        for(size_t j = 0; j < m_.cols(); ++j) {
            EXPECT_EQ(0, m_(i, j));
        }
    }
}

TEST_F(MatrixTest, OperatorIndividualAssignment)
{
    EXPECT_EQ(1.0, m_(0, 0));
    EXPECT_EQ(2.0, m_(0, 1));
    EXPECT_EQ(3.0, m_(0, 2));
    EXPECT_EQ(4.0, m_(0, 3));

    EXPECT_EQ(5.0, m_(1, 0));
    EXPECT_EQ(6.0, m_(1, 1));
    EXPECT_EQ(7.0, m_(1, 2));
    EXPECT_EQ(8.0, m_(1, 3));

    EXPECT_EQ(9.0, m_(2, 0));
    EXPECT_EQ(10.0, m_(2, 1));
    EXPECT_EQ(11.0, m_(2, 2));
    EXPECT_EQ(12.0, m_(2, 3));
}

TEST_F(MatrixTest, OperatorValarrayAssignment)
{
    double count{1.0};
    std::valarray<double> v(row_count_ * col_count_);
    for(size_t i = 0; i < row_count_; ++i) {
        for(size_t j = 0; j < col_count_; ++j) {
            v[i * col_count_ + j] = count * 2;
            ++count;
        }
    }

    m_ = v;

    EXPECT_EQ(2.0, m_(0, 0));
    EXPECT_EQ(4.0, m_(0, 1));
    EXPECT_EQ(6.0, m_(0, 2));
    EXPECT_EQ(8.0, m_(0, 3));

    EXPECT_EQ(10.0, m_(1, 0));
    EXPECT_EQ(12.0, m_(1, 1));
    EXPECT_EQ(14.0, m_(1, 2));
    EXPECT_EQ(16.0, m_(1, 3));

    EXPECT_EQ(18.0, m_(2, 0));
    EXPECT_EQ(20.0, m_(2, 1));
    EXPECT_EQ(22.0, m_(2, 2));
    EXPECT_EQ(24.0, m_(2, 3));
}

TEST_F(MatrixTest, transpose)
{
    const auto t = m_.transpose();

    EXPECT_EQ(1.0, t(0, 0));
    EXPECT_EQ(5.0, t(0, 1));
    EXPECT_EQ(9.0, t(0, 2));

    EXPECT_EQ(2.0, t(1, 0));
    EXPECT_EQ(6.0, t(1, 1));
    EXPECT_EQ(10.0, t(1, 2));

    EXPECT_EQ(3.0, t(2, 0));
    EXPECT_EQ(7.0, t(2, 1));
    EXPECT_EQ(11.0, t(2, 2));

    EXPECT_EQ(4.0, t(3, 0));
    EXPECT_EQ(8.0, t(3, 1));
    EXPECT_EQ(12.0, t(3, 2));
}

TEST_F(MatrixTest, row)
{
    m_.row(0) = {11, 12, 13, 14};
    EXPECT_EQ(11.0, m_(0, 0));
    EXPECT_EQ(12.0, m_(0, 1));
    EXPECT_EQ(13.0, m_(0, 2));
    EXPECT_EQ(14.0, m_(0, 3));

    m_.row(1) = {21, 22, 23, 24};
    EXPECT_EQ(21.0, m_(1, 0));
    EXPECT_EQ(22.0, m_(1, 1));
    EXPECT_EQ(23.0, m_(1, 2));
    EXPECT_EQ(24.0, m_(1, 3));

    m_.row(2) = {31, 32, 33, 34};
    EXPECT_EQ(31.0, m_(2, 0));
    EXPECT_EQ(32.0, m_(2, 1));
    EXPECT_EQ(33.0, m_(2, 2));
    EXPECT_EQ(34.0, m_(2, 3));
}

TEST_F(MatrixTest, colonRow)
{
    m_(0, ":") = {11, 12, 13, 14};
    EXPECT_EQ(11.0, m_(0, 0));
    EXPECT_EQ(12.0, m_(0, 1));
    EXPECT_EQ(13.0, m_(0, 2));
    EXPECT_EQ(14.0, m_(0, 3));

    m_(1, ":") = {21, 22, 23, 24};
    EXPECT_EQ(21.0, m_(1, 0));
    EXPECT_EQ(22.0, m_(1, 1));
    EXPECT_EQ(23.0, m_(1, 2));
    EXPECT_EQ(24.0, m_(1, 3));

    m_(2, ":") = {31, 32, 33, 34};
    EXPECT_EQ(31.0, m_(2, 0));
    EXPECT_EQ(32.0, m_(2, 1));
    EXPECT_EQ(33.0, m_(2, 2));
    EXPECT_EQ(34.0, m_(2, 3));
}

TEST_F(MatrixTest, col)
{
    m_.col(0) = {11, 12, 13};
    EXPECT_EQ(11.0, m_(0, 0));
    EXPECT_EQ(12.0, m_(1, 0));
    EXPECT_EQ(13.0, m_(2, 0));

    m_.col(1) = {21, 22, 23};
    EXPECT_EQ(21.0, m_(0, 1));
    EXPECT_EQ(22.0, m_(1, 1));
    EXPECT_EQ(23.0, m_(2, 1));

    m_.col(2) = {31, 32, 33};
    EXPECT_EQ(31.0, m_(0, 2));
    EXPECT_EQ(32.0, m_(1, 2));
    EXPECT_EQ(33.0, m_(2, 2));

    m_.col(3) = {41, 42, 43};
    EXPECT_EQ(41.0, m_(0, 3));
    EXPECT_EQ(42.0, m_(1, 3));
    EXPECT_EQ(43.0, m_(2, 3));
}

TEST_F(MatrixTest, colonCol)
{
    m_(":", 0) = {11, 12, 13};
    EXPECT_EQ(11.0, m_(0, 0));
    EXPECT_EQ(12.0, m_(1, 0));
    EXPECT_EQ(13.0, m_(2, 0));

    m_(":", 1) = {21, 22, 23};
    EXPECT_EQ(21.0, m_(0, 1));
    EXPECT_EQ(22.0, m_(1, 1));
    EXPECT_EQ(23.0, m_(2, 1));

    m_(":", 2) = {31, 32, 33};
    EXPECT_EQ(31.0, m_(0, 2));
    EXPECT_EQ(32.0, m_(1, 2));
    EXPECT_EQ(33.0, m_(2, 2));

    m_(":", 3) = {41, 42, 43};
    EXPECT_EQ(41.0, m_(0, 3));
    EXPECT_EQ(42.0, m_(1, 3));
    EXPECT_EQ(43.0, m_(2, 3));
}

TEST_F(MatrixTest, Equality)
{
    auto test_m = create_matrix();
    EXPECT_TRUE(m_ == test_m);

    // Change one element and test for equality again
    test_m(0, 0) = 100;

    EXPECT_TRUE(m_ != test_m);
}

TEST_F(MatrixTest, Addition)
{
    auto test_m = create_matrix();
    const auto result = m_ + test_m;

    EXPECT_EQ(2.0, result(0, 0));
    EXPECT_EQ(4.0, result(0, 1));
    EXPECT_EQ(6.0, result(0, 2));
    EXPECT_EQ(8.0, result(0, 3));

    EXPECT_EQ(10.0, result(1, 0));
    EXPECT_EQ(12.0, result(1, 1));
    EXPECT_EQ(14.0, result(1, 2));
    EXPECT_EQ(16.0, result(1, 3));

    EXPECT_EQ(18.0, result(2, 0));
    EXPECT_EQ(20.0, result(2, 1));
    EXPECT_EQ(22.0, result(2, 2));
    EXPECT_EQ(24.0, result(2, 3));

    m_.zero();
    std::valarray<value_type> v(row_count_ * col_count_);
    v = 0;
    matrix_type m{v};
    m.reshape(row_count_, col_count_);

    ASSERT_EQ(m_, m);

    m_ += test_m;

    EXPECT_EQ(1.0, m_(0, 0));
    EXPECT_EQ(2.0, m_(0, 1));
    EXPECT_EQ(3.0, m_(0, 2));
    EXPECT_EQ(4.0, m_(0, 3));

    EXPECT_EQ(5.0, m_(1, 0));
    EXPECT_EQ(6.0, m_(1, 1));
    EXPECT_EQ(7.0, m_(1, 2));
    EXPECT_EQ(8.0, m_(1, 3));

    EXPECT_EQ(9.0, m_(2, 0));
    EXPECT_EQ(10.0, m_(2, 1));
    EXPECT_EQ(11.0, m_(2, 2));
    EXPECT_EQ(12.0, m_(2, 3));
}

TEST_F(MatrixTest, Subtraction)
{
    auto test_m = create_matrix();
    const auto result = m_ - test_m;

    EXPECT_EQ(0.0, result(0, 0));
    EXPECT_EQ(0.0, result(0, 1));
    EXPECT_EQ(0.0, result(0, 2));
    EXPECT_EQ(0.0, result(0, 3));

    EXPECT_EQ(0.0, result(1, 0));
    EXPECT_EQ(0.0, result(1, 1));
    EXPECT_EQ(0.0, result(1, 2));
    EXPECT_EQ(0.0, result(1, 3));

    EXPECT_EQ(0.0, result(2, 0));
    EXPECT_EQ(0.0, result(2, 1));
    EXPECT_EQ(0.0, result(2, 2));
    EXPECT_EQ(0.0, result(2, 3));

    m_.zero();
    std::valarray<value_type> v(row_count_ * col_count_);
    v = 0;
    matrix_type m{v};
    m.reshape(row_count_, col_count_);

    ASSERT_EQ(m_, m);

    m_ -= test_m;

    EXPECT_EQ(-1.0, m_(0, 0));
    EXPECT_EQ(-2.0, m_(0, 1));
    EXPECT_EQ(-3.0, m_(0, 2));
    EXPECT_EQ(-4.0, m_(0, 3));

    EXPECT_EQ(-5.0, m_(1, 0));
    EXPECT_EQ(-6.0, m_(1, 1));
    EXPECT_EQ(-7.0, m_(1, 2));
    EXPECT_EQ(-8.0, m_(1, 3));

    EXPECT_EQ(-9.0, m_(2, 0));
    EXPECT_EQ(-10.0, m_(2, 1));
    EXPECT_EQ(-11.0, m_(2, 2));
    EXPECT_EQ(-12.0, m_(2, 3));
}

TEST_F(MatrixTest, Multiplication)
{
    const auto t = m_.transpose();
    const auto result = m_ * t;

    ASSERT_EQ(9, result.size());

    // [ 30,  70, 110
    //   70, 174, 278
    //  110, 278, 446 ]

    EXPECT_EQ(30.0, result(0, 0));
    EXPECT_EQ(70.0, result(0, 1));
    EXPECT_EQ(110.0, result(0, 2));

    EXPECT_EQ(70.0, result(1, 0));
    EXPECT_EQ(174.0, result(1, 1));
    EXPECT_EQ(278.0, result(1, 2));

    EXPECT_EQ(110.0, result(2, 0));
    EXPECT_EQ(278.0, result(2, 1));
    EXPECT_EQ(446.0, result(2, 2));
}

TEST_F(MatrixTest, eye)
{
    const auto m = matrix_type::eye(3);
    EXPECT_EQ(1.0, m(0, 0));
    EXPECT_EQ(0.0, m(0, 1));
    EXPECT_EQ(0.0, m(0, 2));

    EXPECT_EQ(0.0, m(1, 0));
    EXPECT_EQ(1.0, m(1, 1));
    EXPECT_EQ(0.0, m(1, 2));

    EXPECT_EQ(0.0, m(2, 0));
    EXPECT_EQ(0.0, m(2, 1));
    EXPECT_EQ(1.0, m(2, 2));
}
