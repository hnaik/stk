#ifndef STK_OPT_RESULT_H
#define STK_OPT_RESULT_H

#include "stk/ds/vector.h"

namespace stk::opt {
template <typename T>
class result {
public:
    using value_type = T;
    using solution_container = ds::vector<value_type>;

    virtual value_type z() const = 0;
    virtual void set_z(value_type opt) = 0;

    virtual solution_container solution() const = 0;
    virtual void set_solution(const solution_container& soln) = 0;
};

template <typename T>
class basic_result : public result<T> {
    using value_type = typename result<T>::value_type;
    using solution_container = typename result<T>::solution_container;

    inline value_type z() const override { return 0; }
    inline void set_z(value_type opt) override { z_ = opt; }

    inline solution_container solution() const override { return soln_; }
    inline void set_solution(const solution_container& soln) override
    {
        soln_ = soln;
    }

private:
    value_type z_;
    solution_container soln_;
};

} // namespace stk::opt
#endif // STK_OPT_RESULT_H
