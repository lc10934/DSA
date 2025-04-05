#pragma once
#include <optional>
#include <memory>
#include <iostream>
#include <stdexcept>

template <typename T>
class Deque {
public:
    explicit Deque(size_t capacity = 4)
        : capacity_(capacity), size_(0), front_index_(0),
          data_(std::make_unique<T[]>(capacity))
    {}

    void push_back(const T& item) {
        if (size_ == capacity_) {
            resize(capacity_ + capacity_ / 2);
        }
        size_t back_index = (front_index_ + size_) % capacity_;
        data_[back_index] = item;
        ++size_;
    }

    void push_front(const T& item) {
        if (size_ == capacity_) {
            resize(capacity_ + capacity_ / 2);
        }
        front_index_ = (front_index_ + capacity_ - 1) % capacity_;
        data_[front_index_] = item;
        ++size_;
    }

    std::optional<T> pop_front() {
        if (empty()) {
            return std::nullopt;
        }
        T item = data_[front_index_];
        front_index_ = (front_index_ + 1) % capacity_;
        --size_;
        return item;
    }

    std::optional<T> pop_back() {
        if (empty()) {
            return std::nullopt;
        }
        size_t back_index = (front_index_ + size_ - 1) % capacity_;
        T item = data_[back_index];
        --size_;
        return item;
    }

    std::optional<T> front() const {
        if (empty()) {
            return std::nullopt;
        }
        return data_[front_index_];
    }

    std::optional<T> back() const {
        if (empty()) {
            return std::nullopt;
        }
        size_t back_index = (front_index_ + size_ - 1) % capacity_;
        return data_[back_index];
    }

    bool empty() const {
        return size_ == 0;
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

private:
    void resize(size_t newCapacity) {
        std::cout << "Resizing deque from " << capacity_
                  << " to " << newCapacity << "\n";
        auto newData = std::make_unique<T[]>(newCapacity);
        for (size_t i = 0; i < size_; ++i) {
            newData[i] = data_[(front_index_ + i) % capacity_];
        }
        data_ = std::move(newData);
        capacity_ = newCapacity;
        front_index_ = 0;
    }

    std::unique_ptr<T[]> data_;
    size_t capacity_;
    size_t size_;
    size_t front_index_;  
};
