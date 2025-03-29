#pragma once
#include <vector>
#include <stdexcept>

template <typename T>
class RingBuffer {
public:
    explicit RingBuffer(size_t capacity)
        : buffer_(capacity), head_(0), tail_(0), full_(false)
    {
    }
    void push(const T& item)
    {
        buffer_[head_] = item;
        head_ = (head_ + 1) % buffer_.size();
        if (full_) {
            tail_ = (tail_ + 1) % buffer_.size();
        }
        full_ = (head_ == tail_);
    }

    T pop()
    {
        if (empty()) {
            throw std::runtime_error("RingBuffer is empty");
        }
        T item = buffer_[tail_];
        tail_ = (tail_ + 1) % buffer_.size();
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
            return buffer_.size();
        }
        if (head_ >= tail_) {
            return head_ - tail_;
        }
        return buffer_.size() - tail_ + head_;
    }

    size_t capacity() const
    {
        return buffer_.size();
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
            index = (index + 1) % buffer_.size();
        }
        return result;
    }

private:
    std::vector<T> buffer_; 
    size_t head_;          
    size_t tail_;           
    bool full_;             
};
