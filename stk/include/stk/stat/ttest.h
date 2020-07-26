#ifndef STK_STAT_TTEST_H
#define STK_STAT_TTEST_H

#include <array>
#include <exception>

#include <stk/utils.h>

namespace stk::stat {
static constexpr size_t n_gau = 18;

template <typename T, size_t N_GAU = n_gau>
struct gauss_legendre {
    static constexpr size_t n_gau = N_GAU;
    using value_type = std::array<T, n_gau>;

    static const value_type y{0., 0., 0., 0., 0., 0., 0., 0., 0.,
                              0., 0., 0., 0., 0., 0., 0., 0., 0.};
    static const value_type w{0., 0., 0., 0., 0., 0., 0., 0., 0.,
                              0., 0., 0., 0., 0., 0., 0., 0., 0.};
};

/// Incomplete
template <typename T>
T beta(const T& a, const T& b, const T& x)
{
    T bt;

    if(a <= 0.0 || b <= 0.0) {
        throw std::domain_error{"violated: a>0, b>0"};
    }

    if(x < 0.0 || x > 1.0) {
        throw std::domain_error{"invalid value for x"};
    }

    if(utils::almost_equal(x, 0.0) || utils::almost_equal(1.0)) {
        return x;
    }

    return T{};
}
} // namespace stk::stat
#endif // STK_STAT_TTEST_H
