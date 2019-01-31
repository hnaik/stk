#ifndef STK_OPT_KNAPSACK_INPUT_H
#define STK_OPT_KNAPSACK_INPUT_H

#include <istream>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include <iostream>

namespace stk::opt::knapsack {

template <typename T>
struct item {
    using value_type = T;
    size_t index;
    value_type value;
    value_type weight;
    size_t copies{1};

    static inline std::string header() { return "index,value,weight"; };
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const item<T>& item)
{
    os << item.index << "," << item.value << "," << item.weight << ","
       << item.copies;
    return os;
}

template <typename T>
class input {
public:
    using value_type = T;
    using item_type = item<value_type>;
    using container_type = std::vector<item_type>;

    virtual bool read(std::istream& is) = 0;
    virtual size_t item_count() const = 0;
    virtual value_type capacity() const = 0;
    virtual const container_type items() const = 0;
    virtual void allow_multiple(bool){};
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<item<T>>& items)
{
    os << item<T>::header() << "\n";
    for(const auto& item : items) {
        os << item << "\n";
    }

    return os;
}

template <typename T>
class txt_input : public input<T> {
public:
    using value_type = typename input<T>::value_type;
    using item_type = typename input<T>::item_type;
    using container_type = typename input<T>::container_type;

    virtual bool read(std::istream& is) override;
    inline size_t item_count() const override { return count_; }
    inline value_type capacity() const override { return capacity_; }
    inline const container_type items() const override { return items_; }
    inline void allow_multiple(bool allow) { allow_multiple_ = allow; }

private:
    bool allow_multiple_{false};
    size_t count_;
    value_type capacity_;
    container_type items_;
};

template <typename T>
bool txt_input<T>::read(std::istream& is)
{
    size_t index{0};
    value_type value{};
    value_type weight{};
    size_t copies{1};

    is >> count_ >> capacity_;

    while(is >> value >> weight) {
        // TODO: check if weight is 0 and handle accordingly

        if(allow_multiple_) {
            is >> copies;
        }

        items_.push_back(item<value_type>{index++, value, weight, copies});
    }

    return true;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const input<T>& input)
{
    os << "item count: " << input.item_count()
       << ", capacity: " << input.capacity() << "\n";
    os << input.items() << "\n";

    return os;
}

template <typename T>
std::shared_ptr<input<T>> create_input(std::string_view id)
{
    if(id == "txt") {
        return std::make_shared<txt_input<T>>();
    }

    throw std::runtime_error{"unsupported input type"};
}
} // namespace stk::opt::knapsack

#include "stk/opt/knapsack/impl/input.ipp"

#endif // STK_OPT_KNAPSACK_INPUT_H
