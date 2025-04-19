#pragma once
#include "rbtree.hpp"
#include <cstddef>
#include <functional>

namespace ds{

template <typename T, typename Compare = std::less<T>>
class Set {
    RedBlackTree<T,Compare> tree;
public:
    Set() = default;
    bool empty() const { return tree.empty(); }
    std::size_t size() const { return tree.size(); }
    bool insert(const T& v) { return tree.insert(v); }
    bool contains(const T& v) const { return tree.find(v) != nullptr; }
    using iterator = typename RedBlackTree<T,Compare>::iterator;
    iterator begin() const { return tree.begin(); }
    iterator end()   const { return tree.end(); }
};

}
