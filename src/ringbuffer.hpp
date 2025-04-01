#pragma once
#include <vector>
#include <stdexcept>
#include <optional>
#include <memory>

template <typename T>
class RingBuffer {
public:
    explicit RingBuffer(size_t capacity)
        : capacity_(capacity), head_(0), tail_(0), full_(false),
          buffer_(std::make_unique<T[]>(capacity)) {}

    void push(const T& item)
    {
        buffer_[head_] = item;
        head_ = (head_ + 1) % capacity_;
        if (full_) {
            tail_ = (tail_ + 1) % capacity_;
        }
        full_ = (head_ == tail_);
    }

    std::optional<T> pop()
    {
        if (empty()) {
            return std::nullopt;
        }
        T item = buffer_[tail_];
        tail_ = (tail_ + 1) % capacity_;
        full_ = false;
        return item;
    }

    bool empty() const
    {
        return (!full_ && (head_ == tail_));
    }

    bool full() const
    {
        return full_;
    }

    size_t size() const
    {
        if (full_) {
            return capacity_;
        }
        if (head_ >= tail_) {
            return head_ - tail_;
        }
        return capacity_ - tail_ + head_;
    }

    size_t capacity() const
    {
        return capacity_;
    }

    std::vector<T> to_vector() const
    {
        std::vector<T> result;
        if (empty()) {
            return result;
        }
        size_t count = size();
        size_t index = tail_;
        for (size_t i = 0; i < count; ++i) {
            result.push_back(buffer_[index]);
            index = (index + 1) % capacity_;
        }
        return result;
    }

private:
    std::unique_ptr<T[]> buffer_;
    size_t capacity_;
    size_t head_;
    size_t tail_;
    bool full_;
};
