#ifndef STK_OPT_KNAPSACK_MODEL_FACTORY_H
#define STK_OPT_KNAPSACK_MODEL_FACTORY_H

#include <memory>
#include <string_view>

#include "stk/opt/knapsack/input.h"
#include "stk/opt/knapsack/model.h"

namespace stk::opt::knapsack {

template <typename T>
class model_factory {
public:
    using value_type = T;

    inline model_factory(std::string_view solver_id, std::string_view input_id)
        : solver_id_{solver_id}
        , input_id_{input_id}
    {
    }

    std::shared_ptr<input<value_type>> input_handle() const;

    std::shared_ptr<model<value_type>> solver_handle() const;

private:
    std::string_view solver_id_;
    std::string_view input_id_;
}; // namespace ks=stk::opt::knapsacktemplate<typenameT>classmodel_factory

template <typename T>
std::shared_ptr<input<T>> model_factory<T>::input_handle() const
{
    return create_input<T>(input_id_);
}

template <typename T>
std::shared_ptr<model<T>> model_factory<T>::solver_handle() const
{
    if(solver_id_ == "zero_one") {
        return std::make_shared<zero_one<T>>();
    } else if(solver_id_ == "bkp") {
        return std::make_shared<bkp<T>>();
    }

    throw std::runtime_error{"unsupported solver type"};
}
} // namespace stk::opt::knapsack
#endif // STK_OPT_KNAPSACK_MODEL_FACTORY_H
