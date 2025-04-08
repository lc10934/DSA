#pragma once
#include "deque.hpp"  
#include <optional>
#include <stdexcept>

template <typename T>
class Queue {
public:
    explicit Queue(size_t capacity = 4)
        : deque_(capacity)
    {}

    void enqueue(const T& item) {
        deque_.push_back(item);
    }

    std::optional<T> dequeue() {
        return deque_.pop_front();
    }

    std::optional<T> front() const {
        return deque_.front();
    }

    std::optional<T> back() const {
        return deque_.back();
    }

    const bool empty() const {
        return deque_.empty();
    }

    const size_t size() const {
        return deque_.size();
    }

    const size_t capacity() const {
        return deque_.capacity();
    }

private:
    Deque<T> deque_;
};
