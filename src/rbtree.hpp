#pragma once
#include <functional>
#include <memory>
#include <cstddef>
#include <stdexcept>

namespace ds{

enum Color { RED, BLACK };

template <typename T, typename Compare = std::less<T>>
class RedBlackTree {
private:
    struct Node {
        T data;
        Color color;
        Node* parent;
        Node* left;
        Node* right;
        Node(const T& v, Color c, Node* n)
            : data(v), color(c), parent(n), left(n), right(n) {}
        Node(T&& v, Color c, Node* n)
            : data(std::move(v)), color(c), parent(n), left(n), right(n) {}
    };

    Node* root;
    Node* nil;   
    std::size_t sz;
    Compare comp;

    void rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nil) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nil) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != nil) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nil) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void insertFix(Node* z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        rotateLeft(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateRight(z->parent->parent);
                }
            } else {
                Node* y = z->parent->parent->left;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotateRight(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateLeft(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void deleteSubtree(Node* x) {
        if (x == nil) return;
        deleteSubtree(x->left);
        deleteSubtree(x->right);
        delete x;
    }

public:
    RedBlackTree()
        : sz(0), comp(Compare()) {
        nil = new Node(T(), BLACK, nullptr);
        nil->parent = nil->left = nil->right = nil;
        root = nil;
    }

    ~RedBlackTree() {
        deleteSubtree(root);
        delete nil;
    }

    bool empty() const { return sz == 0; }
    std::size_t size() const { return sz; }

    bool insert(const T& value) {
        Node* z = new Node(value, RED, nil);
        Node* y = nil;
        Node* x = root;
        while (x != nil) {
            y = x;
            if (comp(z->data, x->data)) x = x->left;
            else if (comp(x->data, z->data)) x = x->right;
            else { delete z; return false; }
        }
        z->parent = y;
        if (y == nil) root = z;
        else if (comp(z->data, y->data)) y->left = z;
        else y->right = z;
        ++sz;
        insertFix(z);
        return true;
    }

    const T* find(const T& value) const {
        Node* x = root;
        while (x != nil) {
            if (comp(value, x->data)) x = x->left;
            else if (comp(x->data, value)) x = x->right;
            else return &x->data;
        }
        return nullptr;
    }

    class iterator {
        Node* node;
        const RedBlackTree* tree;
        Node* treeMin(Node* x) const {
            while (x->left != tree->nil) x = x->left;
            return x;
        }
    public:
        iterator(Node* n, const RedBlackTree* t) : node(n), tree(t) {}
        const T& operator*() const { return node->data; }
        const T* operator->() const { return &node->data; }
        bool operator==(const iterator& o) const { return node == o.node; }
        bool operator!=(const iterator& o) const { return node != o.node; }

        iterator& operator++() {
            if (node->right != tree->nil) {
                node = treeMin(node->right);
            } else {
                Node* y = node->parent;
                while (y != tree->nil && node == y->right) {
                    node = y;
                    y = y->parent;
                }
                node = y;
            }
            return *this;
        }

        iterator& operator--() {
            if (node == tree->nil) {
                node = tree->root;
                while (node->right != tree->nil) node = node->right;
            } else if (node->left != tree->nil) {
                node = node->left;
                while (node->right != tree->nil) node = node->right;
            } else {
                Node* y = node->parent;
                while (y != tree->nil && node == y->left) {
                    node = y;
                    y = y->parent;
                }
                node = y;
            }
            return *this;
        }
    };

    iterator begin() const {
        Node* x = root;
        while (x->left != nil) x = x->left;
        return iterator(x, this);
    }
    iterator end() const {
        return iterator(nil, this);
    }
};

}