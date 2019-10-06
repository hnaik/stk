#include <ostream>

namespace stk::opt::regression::linear {
template <typename Vector>
solution<typename Vector::value_type> fit(const Vector& x, const Vector& y)
{
    using value_type = typename Vector::value_type;

    assert(x.dim() == y.dim());
    const size_t n = x.dim();
    assert(n > 0);

    const auto sum_x = x.sum();
    const auto sum_y = y.sum();
    const auto sum_xy = (x * y).sum();
    const auto sum_x2 = ds::pow(x, 2.0).sum();

    value_type xm = sum_x / n;
    value_type ym = sum_y / n;

    solution<value_type> soln;

    soln.a1 = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    soln.a0 = ym - soln.a1 * xm;

    const auto st = ds::pow(y - ym, 2.0).sum();

    // TODO: To investigate why the vectorized version of this does not work
    value_type sr = 0.0;
    for(size_t i = 0; i < n; ++i) {
        sr += std::pow(y[i] - x[i] * soln.a1 - soln.a0, 2);
    }

    soln.se = std::sqrt(sr / (n - 2));
    soln.r2 = (st - sr) / st;

    return soln;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const solution<T>& lr)
{
    std::setprecision(6);
    os << "[a0:" << lr.a0 << ",a1:" << lr.a1 << ",sd:" << lr.sd
       << ",se:" << lr.se << ",r2:" << lr.r2 << "]";
    return os;
}

} // namespace stk::opt::regression::linear
