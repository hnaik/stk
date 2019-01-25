#include <cassert>
#include <iomanip>
#include <iostream>
#include <random>
#include <valarray>

#include "stk/ds/matrix.h"

int main()
{
    constexpr std::size_t row = 3;
    constexpr std::size_t col = 4;
    std::valarray<double> v(row * col);
    stk::ds::matrix<double> m{row, col};

    double count{1.0};
    for(size_t i = 0; i < row; ++i) {
        for(size_t j = 0; j < col; ++j) {
            m(i, j) = count;
            v[i * col + j] = count;

            ++count;
        }
    }

    std::cout << "size: " << m.size() << "\n";
    std::cout << m << "\n";

    v *= 2;
    m = v;
    std::cout << m << "\n";

    auto t = m.transpose();
    std::cout << t << "\n";

    std::valarray<double> row_a{11, 12, 13, 14};
    m.row(0) = row_a;
    std::cout << m << "\n";

    std::valarray<double> col_a{33, 43, 53};
    m.col(2) = col_a;
    std::cout << m << "\n";
}
