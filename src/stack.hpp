#pragma once
#include "deque.hpp" 
#include <optional>
#include <stdexcept>

template <typename T>
class Stack {
public:
    explicit Stack(size_t capacity = 4)
        : deque_(capacity)
    {}

    void push(const T& item) {
        deque_.push_back(item);
    }

    std::optional<T> pop() {
        return deque_.pop_back();
    }

    std::optional<T> top() const {
        return deque_.back();
    }

    const bool empty() const {
        return deque_.empty();
    }

    const size_t size() const {
        return deque_.size();
    }

private:
    Deque<T> deque_;
};
