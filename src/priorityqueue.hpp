#pragma once
#include "binary_search_tree.hpp"
#include <optional>
#include <memory>

template <typename T, typename Compare = std::less<T>>
class PriorityQueue {
public:
    PriorityQueue() = default; 
    
    void push(const T& data) {
        if (!bst_) {
            bst_ = std::make_unique<BinarySearchTree<T, Compare>>(data);
        } else {
            bst_->insert(data);
        }
    }
    
    void push(T&& data) {
        if (!bst_) {
            bst_ = std::make_unique<BinarySearchTree<T, Compare>>(std::move(data));
        } else {
            bst_->insert(std::move(data));
        }
    }
    
    std::optional<T> top() const {
        if (!bst_ || bst_->empty()) return std::nullopt;
        return bst_->findMin();
    }
    
    std::optional<T> pop() {
        if (!bst_ || bst_->empty()) return std::nullopt;
        T minValue = bst_->findMin();
        bst_->removeMin();
        return minValue;
    }
    
    bool empty() const {
        return (!bst_ || bst_->empty());
    }
    
private:
    std::unique_ptr<BinarySearchTree<T, Compare>> bst_;
};
