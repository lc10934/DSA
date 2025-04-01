#pragma once
#include <stdexcept>
#include <optional>
#include <memory>
#include <iostream>

template <typename T>
class Vector {
public:
    Vector()
        : size_(0), capacity_(2), data_(std::make_unique<T[]>(2))
    {}

    explicit Vector(size_t capacity)
        : size_(0), capacity_(capacity), data_(std::make_unique<T[]>(capacity))
    {}

    void push_back(const T& item)
    {
        if (size_ >= capacity_) {
            reserve(capacity_ + capacity_ / 2);
        }
        data_[size_++] = item;
    }

    std::optional<T> pop()
    {
        if (size_ == 0) {
            return std::nullopt;
        }
        return data_[--size_];
    }

    std::optional<T> operator[](size_t index) const
    {
        if (index >= size_) {
            return std::nullopt;
        }
        return data_[index];
    }

    size_t size() const
    {
        return size_;
    }

    size_t capacity() const
    {
        return capacity_;
    }

private:
    void reserve(size_t newCapacity)
    {
        if (newCapacity <= capacity_) {
            return;
        }
        std::cout << "Reserving new capacity: " << newCapacity << "\n";
        auto newData = std::make_unique<T[]>(newCapacity);
        for (size_t i = 0; i < size_; i++) {
            newData[i] = data_[i];
        }
        data_ = std::move(newData);
        capacity_ = newCapacity;
    }

    std::unique_ptr<T[]> data_;
    size_t size_;
    size_t capacity_;
};
