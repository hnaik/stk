#ifndef STK_OPT_LINEAR_REGRESSION_H
#define STK_OPT_LINEAR_REGRESSION_H

#include <cassert>
#include <cmath>
#include <iomanip>
#include <ostream>
#include <tuple>
#include <valarray>

#include "stk/ds/vector.h"

namespace stk::opt {
template <typename T>
struct lr_soln {
    using value_type = T;

    value_type a0{};
    value_type a1{};
    value_type sd{};
    value_type se{};
    value_type r2{};
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const lr_soln<T>& lr);

template <typename Vector>
lr_soln<typename Vector::value_type> fit(const Vector& x, const Vector& y);
} // namespace stk::opt

#include "stk/opt/impl/linear_regression.ipp"

#endif // STK_OPT_LINEAR_REGRESSION_H
