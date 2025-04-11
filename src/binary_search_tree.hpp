#pragma once
#include "tree.hpp"
#include <functional>
#include <memory>

template <typename T, typename Compare = std::less<T>>
class BinarySearchTree {
public:
    explicit BinarySearchTree(const T& rootData)
        : root(std::make_unique<TreeNode<T>>(rootData))
    {
        ensureBinary(root.get());
    }
    
    explicit BinarySearchTree(T&& rootData)
        : root(std::make_unique<TreeNode<T>>(std::move(rootData)))
    {
        ensureBinary(root.get());
    }
    
    void insert(const T& data) {
        insertHelper(root.get(), data);
    }
    
    void insert(T&& data) {
        insertHelper(root.get(), std::move(data));
    }
    
    const T& findMin() const {
        TreeNode<T>* node = root.get();
        while (node->children[0]) {
            node = node->children[0].get();
        }
        return node->data;
    }
    
    void removeMin() {
        root = removeMinHelper(std::move(root));
    }
    
    bool empty() const { return root == nullptr; }
    
private:
    std::unique_ptr<TreeNode<T>> root;
    Compare comp;
    
    void ensureBinary(TreeNode<T>* node) {
        if (node->children.size() < 2) {
            node->children.resize(2);
        }
    }
    
    template <typename U>
    void insertHelper(TreeNode<T>* node, U&& data) {
        if (comp(std::forward<U>(data), node->data)) {
            ensureBinary(node);
            if (!node->children[0]) {
                node->children[0] = std::make_unique<TreeNode<T>>(std::forward<U>(data));
                ensureBinary(node->children[0].get());
            } else {
                insertHelper(node->children[0].get(), std::forward<U>(data));
            }
        } else {
            ensureBinary(node);
            if (!node->children[1]) {
                node->children[1] = std::make_unique<TreeNode<T>>(std::forward<U>(data));
                ensureBinary(node->children[1].get());
            } else {
                insertHelper(node->children[1].get(), std::forward<U>(data));
            }
        }
    }
    
    std::unique_ptr<TreeNode<T>> removeMinHelper(std::unique_ptr<TreeNode<T>> node) {
        if (!node) return nullptr;
        ensureBinary(node.get());
        if (!node->children[0]) {
            return std::move(node->children[1]);
        } else {
            node->children[0] = removeMinHelper(std::move(node->children[0]));
            return node;
        }
    }
};
