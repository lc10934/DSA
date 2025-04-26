#pragma once
#include "rbtree.hpp"
#include <cstddef>
#include <functional>
#include <stdexcept>
#include <utility>

namespace ds {

template <typename Key, typename Value, typename Compare = std::less<Key>>
class Map {
private:
    struct KeyCompare {
        Compare comp;
        KeyCompare(Compare c = Compare()) : comp(c) {}
        bool operator()(const std::pair<const Key, Value>& lhs, 
                        const std::pair<const Key, Value>& rhs) const {
            return comp(lhs.first, rhs.first);
        }
    };

    RedBlackTree<std::pair<const Key, Value>, KeyCompare> tree;

public:
    Map() = default;
    
    bool empty() const { return tree.empty(); }
    std::size_t size() const { return tree.size(); }
    
    std::pair<bool, typename RedBlackTree<std::pair<const Key, Value>, KeyCompare>::iterator>
    insert(const Key& key, const Value& value) {
        auto result = tree.insert(std::make_pair(key, value));
        return {result, tree.end()}; 
    }
    
    std::pair<bool, typename RedBlackTree<std::pair<const Key, Value>, KeyCompare>::iterator>
    insert(const std::pair<const Key, Value>& pair) {
        return {tree.insert(pair), tree.end()};
    }
    
    Value& operator[](const Key& key) {
        auto pair = std::make_pair(key, Value());
        auto result = tree.find(pair);
        if (result) {
            return const_cast<Value&>(result->second);
        } else {
            tree.insert(pair);
            result = tree.find(pair);
            return const_cast<Value&>(result->second);
        }
    }
    
    const Value& at(const Key& key) const {
        auto pair = std::make_pair(key, Value());
        auto result = tree.find(pair);
        if (!result) {
            throw std::out_of_range("Key not found in map");
        }
        return result->second;
    }
    
    Value& at(const Key& key) {
        auto pair = std::make_pair(key, Value());
        auto result = tree.find(pair);
        if (!result) {
            throw std::out_of_range("Key not found in map");
        }
        return const_cast<Value&>(result->second);
    }
    
    bool contains(const Key& key) const {
        auto pair = std::make_pair(key, Value());
        return tree.find(pair) != nullptr;
    }
    
    using iterator = typename RedBlackTree<std::pair<const Key, Value>, KeyCompare>::iterator;
    
    iterator begin() const { return tree.begin(); }
    iterator end() const { return tree.end(); }
};

}