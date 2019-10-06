#ifndef STK_OPT_REGRESSION_LINEAR_H
#define STK_OPT_REGRESSION_LINEAR_H

#include <cassert>
#include <cmath>
#include <iomanip>
#include <ostream>
#include <tuple>
#include <valarray>

#include "stk/ds/vector.h"

namespace stk::opt::regression::linear {
template <typename T>
struct solution {
    using value_type = T;

    value_type a0{};
    value_type a1{};
    value_type sd{};
    value_type se{};
    value_type r2{};
};

template <typename Vector>
solution<typename Vector::value_type> fit(const Vector& x, const Vector& y);

template <typename T>
std::ostream& operator<<(std::ostream& os, const solution<T>& lr);

} // namespace stk::opt::regression::linear

#include "stk/opt/impl/regression/linear.ipp"

#endif // STK_OPT_REGRESSION_LINEAR_H
