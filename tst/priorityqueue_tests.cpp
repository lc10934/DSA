#include <gtest/gtest.h>
#include <optional>
#include <string>
#include "../src/priorityqueue.hpp" 


struct Person {
    std::string name;
    int age;
    
    Person() : name(""), age(0) {}
    Person(const std::string& n, int a) : name(n), age(a) {}
    
    bool operator==(const Person &other) const {
        return name == other.name && age == other.age;
    }
};

struct PersonCompare {
    bool operator()(const Person &a, const Person &b) const {
        return a.age < b.age;
    }
};

TEST(PriorityQueueTest, BasicOperations) {
    PriorityQueue<int> pq;
    
    EXPECT_TRUE(pq.empty());

    pq.push(5);
    pq.push(3);
    pq.push(8);
    pq.push(1);
    
    ASSERT_TRUE(pq.top().has_value());
    EXPECT_EQ(pq.top().value(), 1);
    
    ASSERT_TRUE(pq.pop().has_value());
    EXPECT_EQ(pq.top().value(), 3);

    EXPECT_EQ(pq.pop().value(), 3);
    EXPECT_EQ(pq.top().value(), 5);
    EXPECT_EQ(pq.pop().value(), 5);
    EXPECT_EQ(pq.top().value(), 8);
    EXPECT_EQ(pq.pop().value(), 8);
    
    EXPECT_TRUE(pq.empty());
}

TEST(PriorityQueueTest, CustomStructTest) {
    PriorityQueue<Person, PersonCompare> pq;
    
    pq.push(Person("Alice", 30));
    pq.push(Person("Bob", 25));
    pq.push(Person("Charlie", 35));
    
    ASSERT_TRUE(pq.top().has_value());
    EXPECT_EQ(pq.top().value(), Person("Bob", 25));
    
    pq.pop();
    ASSERT_TRUE(pq.top().has_value());
    EXPECT_EQ(pq.top().value(), Person("Alice", 30));
    
    pq.pop();
    ASSERT_TRUE(pq.top().has_value());
    EXPECT_EQ(pq.top().value(), Person("Charlie", 35));
    
    pq.pop();
    EXPECT_TRUE(pq.empty());
}

TEST(PriorityQueueTest, OperationsOnEmptyQueue) {
    PriorityQueue<int> pq;
    EXPECT_FALSE(pq.top().has_value());
    EXPECT_FALSE(pq.pop().has_value());
}


