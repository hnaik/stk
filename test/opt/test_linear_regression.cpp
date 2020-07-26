#include "stk/opt/regression/linear.h"

#include <gtest/gtest.h>

#include "stk/ds/vector.h"

namespace {
TEST(LinearRegressionTest, fit)
{
    stk::ds::vector<double> x{1., 2., 3., 4., 5., 6., 7.};
    stk::ds::vector<double> y{0.5, 2.5, 2.0, 4.0, 3.5, 6.0, 5.5};

    using namespace stk::opt::regression;
    const auto soln = linear::fit(x, y);

    EXPECT_NEAR(soln.a0, 0.07142857, 0.00000001);
    EXPECT_NEAR(soln.a1, 0.83928571, 0.00000001);
    EXPECT_NEAR(soln.se, 0.773443136, 0.00000001);
    EXPECT_NEAR(soln.r2, 0.86831761, 0.00000001);
}
} // namespace
