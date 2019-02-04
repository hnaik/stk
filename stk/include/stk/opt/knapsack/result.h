#ifndef STK_OPT_KNAPSACK_SOLUTION_H
#define STK_OPT_KNAPSACK_SOLUTION_H

#include <ostream>
#include <vector>

namespace stk::opt::knapsack {
template <typename T>
struct result {
    using value_type = T;

    result(size_t item_count)
        : solution(item_count)
    {
        std::fill(begin(solution), end(solution), 0);
    }

    value_type z{};
    bool opt = false;
    std::vector<short> solution;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const result<T>& result)
{
    os << result.z << " " << std::noboolalpha << result.opt << "\n";
    for(const auto& item : result.solution) {
        os << item << " ";
    }

    return os;
}

} // namespace stk::opt::knapsack

#endif // STK_OPT_KNAPSACK_SOLUTION_H
