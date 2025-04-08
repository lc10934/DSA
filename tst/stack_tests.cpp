#include <gtest/gtest.h>
#include <optional>
#include <string>
#include "../src/stack.hpp" 

struct Person {
    std::string name;
    int age;

    Person() : name(""), age(0) {}
    Person(const std::string &n, int a) : name(n), age(a) {}

    bool operator==(const Person &other) const {
        return name == other.name && age == other.age;
    }
};

TEST(StackTest, InitializeTest) {
    Stack<int> s;
    ASSERT_TRUE(s.empty());
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.top(), std::nullopt);
    ASSERT_EQ(s.pop(), std::nullopt);
}

TEST(StackTest, SinglePushPopTest) {
    Stack<int> s;
    s.push(42);
    ASSERT_FALSE(s.empty());
    ASSERT_EQ(s.size(), 1);
    ASSERT_EQ(s.top(), 42);
    ASSERT_EQ(s.pop(), 42);
    ASSERT_TRUE(s.empty());
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.top(), std::nullopt);
}

TEST(StackTest, MultiplePushPopTest) {
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    ASSERT_EQ(s.size(), 3);
    ASSERT_EQ(s.top(), 30);
    ASSERT_EQ(s.pop(), 30);
    ASSERT_EQ(s.top(), 20);
    ASSERT_EQ(s.pop(), 20);
    ASSERT_EQ(s.top(), 10);
    ASSERT_EQ(s.pop(), 10);
    ASSERT_TRUE(s.empty());
    ASSERT_EQ(s.pop(), std::nullopt);
}

TEST(StackTest, CustomTest) {
    Stack<Person> s;
    s.push({"Alice", 30});
    s.push({"Bob", 25});
    ASSERT_EQ(s.size(), 2);
    // Top should return the most recently pushed element ("Bob", 25)
    ASSERT_EQ(s.top().value(), Person("Bob", 25));
    auto p = s.pop();
    ASSERT_TRUE(p.has_value());
    ASSERT_EQ(p.value(), Person("Bob", 25));
    ASSERT_EQ(s.top().value(), Person("Alice", 30));
    p = s.pop();
    ASSERT_TRUE(p.has_value());
    ASSERT_EQ(p.value(), Person("Alice", 30));
    ASSERT_TRUE(s.empty());
}

TEST(StackTest, MiscTest) {
    Stack<std::string> s;
    s.push("first");
    s.push("second");
    ASSERT_EQ(s.top(), "second");
    ASSERT_EQ(s.pop(), "second");
    s.push("third");
    ASSERT_EQ(s.top(), "third");
    s.push("fourth");
    ASSERT_EQ(s.size(), 3);
    ASSERT_EQ(s.pop(), "fourth");
    ASSERT_EQ(s.top(), "third");
    ASSERT_EQ(s.pop(), "third");
    ASSERT_EQ(s.top(), "first");
    ASSERT_EQ(s.pop(), "first");
    ASSERT_TRUE(s.empty());
}
