#ifndef STK_OPT_MODEL_H
#define STK_OPT_MODEL_H

#include <istream>
#include <memory>
#include <ostream>
#include <vector>

#include "stk/ds/matrix.h"
#include "stk/ds/vector.h"
#include "stk/opt/result.h"

namespace stk::opt {
template <typename T>
struct bound {
    using value_type = T;
    value_type value{};
};

template <typename T>
struct bounds {
    using value_type = T;
    using bound_type = bound<value_type>;

    std::string_view name;
    bound_type min;
    bound_type max;
};

template <typename T>
class model {
public:
    using value_type = T;
    using vector_type = ds::vector<value_type>;
    using matrix_type = ds::matrix<value_type>;
    using name_type = std::string_view;
    using names_type = std::vector<name_type>;
    using result_type = result<value_type>;
    using result_ptr = std::shared_ptr<result_type>;
    using bounds_container = std::vector<bounds<value_type>>;

    virtual ~model() = default;

    virtual std::string_view name() const = 0;
    virtual ds::vector<value_type> objective() const = 0;
    virtual ds::matrix<value_type> constraints() const = 0;
    virtual names_type variable_names() const = 0;
    virtual names_type constraint_names() const = 0;
    virtual vector_type costs() const = 0;

    virtual void set_name(std::string_view name) = 0;

    virtual void set_objective(const vector_type& objective) = 0;
    virtual void set_variable_names(names_type variable_names) = 0;

    virtual void set_constraints(const matrix_type& constraints) = 0;
    virtual void set_constraint_names(names_type constraint_names) = 0;
    virtual void set_costs(const vector_type& costs) = 0;

    virtual void solve() = 0;
    virtual result_ptr solution() const = 0;
    virtual void read(std::istream& is) = 0;
    virtual void set_bounds(const bounds_container& bounds) = 0;
};

template <typename T>
class basic_model : public model<T> {
public:
    using value_type = typename model<T>::value_type;
    using vector_type = typename model<T>::vector_type;
    using matrix_type = typename model<T>::matrix_type;
    using name_type = typename model<T>::name_type;
    using names_type = typename model<T>::names_type;
    using result_type = typename model<T>::result_type;
    using result_ptr = typename model<T>::result_ptr;
    using bounds_container = typename model<T>::bounds_container;

    inline std::string_view name() const override { return name_; }

    inline ds::vector<value_type> objective() const override
    {
        return objective_;
    }

    inline ds::matrix<value_type> constraints() const override
    {
        return constraints_;
    }

    inline names_type variable_names() const override
    {
        return variable_names_;
    }

    inline names_type constraint_names() const override
    {
        return constraint_names_;
    }

    inline vector_type costs() const override { return costs_; }

    inline void set_name(std::string_view name) override { name_ = name; }

    inline void set_objective(const vector_type& objective) override
    {
        objective_ = objective;
    }

    inline void set_constraints(const matrix_type& constraints) override
    {
        constraints_ = constraints;
    }

    inline void set_variable_names(names_type variable_names) override
    {
        variable_names_ = variable_names;
    }

    inline void set_constraint_names(names_type constraint_names) override
    {
        constraint_names_ = constraint_names;
    }

    inline void set_costs(const vector_type& costs) override { costs_ = costs; }

    void solve() override;

    void read(std::istream& is) override;

    result_ptr solution() const override
    {
        return std::make_shared<basic_result<value_type>>();
    }

    inline void set_bounds(const bounds_container& bounds) { bounds_ = bounds; }

private:
    std::string_view name_;
    vector_type costs_;
    vector_type objective_;
    matrix_type constraints_;
    names_type variable_names_;
    names_type constraint_names_;
    bounds_container bounds_;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const model<T>& m);

} // namespace stk::opt

#include "stk/opt/impl/model.ipp"

#endif // STK_OPT_MODEL_H
