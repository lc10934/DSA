#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../src/tree.hpp"

struct Person {
    std::string name;
    int age;
    Person() : name(""), age(0) {}
    Person(const std::string& n, int a) : name(n), age(a) {}
    bool operator==(const Person &other) const { return name == other.name && age == other.age; }
};

TEST(TreeTest, InitializeTest) {
    Tree<int> tree(10);
    TreeNode<int>* root = tree.getRoot();
    ASSERT_NE(root, nullptr);
    ASSERT_EQ(root->data, 10);
}

TEST(TreeTest, AddChildTest) {
    Tree<std::string> tree("root");
    TreeNode<std::string>* root = tree.getRoot();
    root->addChild("child1");
    root->addChild("child2");
    ASSERT_EQ(root->children.size(), 2);
    ASSERT_EQ(root->children[0]->data, "child1");
    ASSERT_EQ(root->children[1]->data, "child2");
}

TEST(TreeTest, PreOrderTraverseTest) {
    Tree<std::string> tree("A");
    TreeNode<std::string>* root = tree.getRoot();
    root->addChild("B");
    TreeNode<std::string>* nodeC = root->addChild("C");
    nodeC->addChild("D");
    nodeC->addChild("E");

    std::vector<std::string> traversal;
    tree.traverse([&traversal](const TreeNode<std::string>* node) {
        traversal.push_back(node->data);
    });

    std::vector<std::string> expected = {"A", "B", "C", "D", "E"};
    ASSERT_EQ(traversal, expected);
}

TEST(TreeTest, DeepTreeTest) {
    Tree<int> tree(1);
    TreeNode<int>* root = tree.getRoot();
    TreeNode<int>* node2 = root->addChild(2);
    TreeNode<int>* node3 = root->addChild(3);
    node2->addChild(4);
    node2->addChild(5);
    node3->addChild(6);
    node3->addChild(7);

    std::vector<int> traversal;
    tree.traverse([&traversal](const TreeNode<int>* node) {
        traversal.push_back(node->data);
    });

    std::vector<int> expected = {1, 2, 4, 5, 3, 6, 7};
    ASSERT_EQ(traversal, expected);
}

TEST(TreeTest, ConstGetRootTest) {
    Tree<int> tree(42);
    const Tree<int>& constTree = tree;
    const TreeNode<int>* root = constTree.getRoot();
    ASSERT_NE(root, nullptr);
    ASSERT_EQ(root->data, 42);
}

TEST(TreeTest, CustomStructTest) {
    Tree<Person> tree(Person("Alice", 30));
    TreeNode<Person>* root = tree.getRoot();
    root->addChild(Person("Bob", 25));
    root->addChild(Person("Charlie", 20));

    std::vector<Person> traversal;
    tree.traverse([&traversal](const TreeNode<Person>* node) {
        traversal.push_back(node->data);
    });

    std::vector<Person> expected = {Person("Alice", 30), Person("Bob", 25), Person("Charlie", 20)};
    ASSERT_EQ(traversal, expected);
}
