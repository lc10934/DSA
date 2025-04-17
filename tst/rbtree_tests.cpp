#include <gtest/gtest.h>
#include "../src/rbtree.hpp"
#include <vector>
#include <algorithm>

struct Person {
    std::string name;
    int age;
    Person() : name(""), age(0) {}
    Person(std::string n, int a) : name(std::move(n)), age(a) {}
    bool operator<(Person const& o) const {
        return age < o.age || (age == o.age && name < o.name);
    }
    bool operator==(Person const& o) const {
        return age == o.age && name == o.name;
    }
};

TEST(RBTreeTest, EmptyInitially) {
    ds::RedBlackTree<int> tree;
    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.size(), 0u);
}

TEST(RBTreeTest, InsertAndFindInt) {
    ds::RedBlackTree<int> tree;
    EXPECT_TRUE(tree.insert(10));
    EXPECT_FALSE(tree.empty());
    EXPECT_EQ(tree.size(), 1u);
    EXPECT_TRUE(tree.insert(5));
    EXPECT_TRUE(tree.insert(20));
    EXPECT_EQ(tree.size(), 3u);
    EXPECT_FALSE(tree.insert(10));
    EXPECT_EQ(tree.size(), 3u);
    auto p = tree.find(10);
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(*p, 10);
    EXPECT_EQ(tree.find(42), nullptr);
}

TEST(RBTreeTest, InOrderIterationInt) {
    ds::RedBlackTree<int> tree;
    std::vector<int> vals = {7, 3, 9, 1, 5};
    for (int v : vals) tree.insert(v);
    std::sort(vals.begin(), vals.end());
    std::vector<int> out;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        out.push_back(*it);
    }
    EXPECT_EQ(out, vals);
}

TEST(RBTreeTest, InsertAndFindCustom) {
    ds::RedBlackTree<Person> tree;
    Person a{"Alice",30}, b{"Bob",25}, c{"Charlie",35};
    EXPECT_TRUE(tree.insert(a));
    EXPECT_TRUE(tree.insert(b));
    EXPECT_TRUE(tree.insert(c));
    EXPECT_EQ(tree.size(), 3u);
    auto pb = tree.find(Person{"Bob",25});
    ASSERT_NE(pb, nullptr);
    EXPECT_EQ(*pb, b);
    EXPECT_EQ(tree.find(Person{"David",40}), nullptr);
}

TEST(RBTreeTest, InOrderIterationCustom) {
    ds::RedBlackTree<Person> tree;
    std::vector<Person> ppl = {{"Alice",30}, {"Bob",25}, {"Charlie",35}};
    for (auto& p : ppl) tree.insert(p);
    std::sort(ppl.begin(), ppl.end(), [](auto const& x, auto const& y){
        return x < y;
    });
    std::vector<Person> out;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        out.push_back(*it);
    }
    EXPECT_EQ(out, ppl);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
