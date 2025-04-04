#pragma once
#include <optional>
#include "vector.hpp"  

template <typename T>
class Stack {
public:
    Stack() = default;

    void push(const T& item) {
        container_.push_back(item);
    }

    std::optional<T> pop() {
        return container_.pop();
    }

    std::optional<T> top() const {
        if (container_.size() == 0) {
            return std::nullopt;
        }
        return container_[container_.size() - 1];
    }

    size_t size() const {
        return container_.size();
    }

    bool empty() const {
        return (container_.size() == 0);
    }

private:
    Vector<T> container_;
};
