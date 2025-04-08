#pragma once
#include <memory>
#include <vector>
#include <functional>

template <typename T>
struct TreeNode {
    using Ptr = std::unique_ptr<TreeNode<T>>;
    T data;
    std::vector<Ptr> children;

    explicit TreeNode(const T& data)
        : data(data)
    {}

    explicit TreeNode(T&& data)
        : data(std::move(data))
    {}

    TreeNode<T>* addChild(const T& childData) {
        children.push_back(std::make_unique<TreeNode<T>>(childData));
        return children.back().get();
    }

    TreeNode<T>* addChild(T&& childData) {
        children.push_back(std::make_unique<TreeNode<T>>(std::move(childData)));
        return children.back().get();
    }
};

template <typename T>
class Tree {
public:
    explicit Tree(const T& rootData)
        : root(std::make_unique<TreeNode<T>>(rootData))
    {}

    explicit Tree(T&& rootData)
        : root(std::make_unique<TreeNode<T>>(std::move(rootData)))
    {}

    TreeNode<T>* getRoot() {
        return root.get();
    }

    const TreeNode<T>* getRoot() const {
        return root.get();
    }

    void traverse(const std::function<void(const TreeNode<T>*)>& action) const {
        traverseHelper(root.get(), action);
    }

private:
    std::unique_ptr<TreeNode<T>> root;

    void traverseHelper(const TreeNode<T>* node, const std::function<void(const TreeNode<T>*)>& action) const {
        if (!node) return;
        action(node);
        for (const auto& child : node->children) {
            traverseHelper(child.get(), action);
        }
    }
};
