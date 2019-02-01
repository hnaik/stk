#ifndef STK_OPT_KNAPSACK_SOLUTION_H
#define STK_OPT_KNAPSACK_SOLUTION_H

#include <ostream>
#include <vector>

namespace stk::opt::knapsack {
template <typename T>
struct solution {
    using value_type = T;

    solution(size_t item_count)
        : picked(item_count)
    {
        std::fill(begin(picked), end(picked), 0);
    }

    value_type obj{};
    bool opt = false;
    std::vector<short> picked;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const solution<T>& solution)
{
    os << solution.obj << " " << std::noboolalpha << solution.opt << "\n";
    for(const auto& item : solution.picked) {
        os << item << " ";
    }

    return os;
}

} // namespace stk::opt::knapsack

#endif // STK_OPT_KNAPSACK_SOLUTION_H
