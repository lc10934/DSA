#pragma once
#include "ringbuffer.hpp"  
#include <vector>
#include <optional>
#include <stdexcept>
#include <memory>
#include <iostream>

template <typename T>
class Deque {
public:
    explicit Deque(size_t capacity = 4)
        : ringBuffer_(capacity)
    {}

    void push_back(const T& item) {
        ringBuffer_.push(item);
    }

    std::optional<T> pop_front() {
        return ringBuffer_.pop();
    }

    std::optional<T> front() const {
        std::vector<T> elems = ringBuffer_.to_vector();
        if (elems.empty()) {
            return std::nullopt;
        }
        return elems.front();
    }

    void push_front(const T& item) {
        std::vector<T> elems = ringBuffer_.to_vector();
        elems.insert(elems.begin(), item); 
        rebuild_buffer(elems);
    }

    std::optional<T> pop_back() {
        std::vector<T> elems = ringBuffer_.to_vector();
        if (elems.empty()) {
            return std::nullopt;
        }
        T item = elems.back();
        elems.pop_back();
        rebuild_buffer(elems);
        return item;
    }

    std::optional<T> back() const {
        std::vector<T> elems = ringBuffer_.to_vector();
        if (elems.empty()) {
            return std::nullopt;
        }
        return elems.back();
    }

    bool empty() const {
        return ringBuffer_.empty();
    }

    size_t size() const {
        return ringBuffer_.size();
    }

    size_t capacity() const {
        return ringBuffer_.capacity();
    }

private:
    void rebuild_buffer(const std::vector<T>& elems) {
        size_t newCapacity = ringBuffer_.capacity();
        if (elems.size() > newCapacity) {
            newCapacity = elems.size();
        }
        ringBuffer_ = RingBuffer<T>(newCapacity);
        for (const auto &e : elems) {
            ringBuffer_.push(e);
        }
    }

    RingBuffer<T> ringBuffer_;
};
