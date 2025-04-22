#include <gtest/gtest.h>
#include "../src/deque.hpp"
#include <stdexcept>

TEST(DequeTest, PushBackAndPopFront) {
    Deque<int> dq(5);
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);

    EXPECT_EQ(dq.size(), 3);

    EXPECT_EQ(dq.pop_front(), 1);
    EXPECT_EQ(dq.pop_front(), 2);
    EXPECT_EQ(dq.pop_front(), 3);

    EXPECT_TRUE(dq.empty());
}

TEST(DequeTest, PushFrontAndPopBack) {
    Deque<int> dq(5);
    dq.push_front(1);
    dq.push_front(2);
    dq.push_front(3);

    EXPECT_EQ(dq.size(), 3);

    EXPECT_EQ(dq.pop_back(), 1);
    EXPECT_EQ(dq.pop_back(), 2);
    EXPECT_EQ(dq.pop_back(), 3);

    EXPECT_TRUE(dq.empty());
}

TEST(DequeTest, MixedOperations) {
    Deque<int> dq(4);
    dq.push_back(10);
    dq.push_front(20);
    dq.push_back(30);
    dq.push_front(40);

    EXPECT_EQ(dq.front(), 40);
    EXPECT_EQ(dq.back(), 30);

    EXPECT_EQ(dq.pop_front(), 40);
    EXPECT_EQ(dq.pop_back(), 30);

    EXPECT_EQ(dq.size(), 2);
    EXPECT_EQ(dq.front(), 20);
    EXPECT_EQ(dq.back(), 10);
}

TEST(DequeTest, ResizingTest) {
    Deque<int> dq(4);
    for (int i = 1; i <= 10; ++i) {
        dq.push_back(i);
    }
    EXPECT_EQ(dq.size(), 10);

    for (int i = 1; i <= 10; ++i) {
        EXPECT_EQ(dq.pop_front(), i);
    }

    EXPECT_TRUE(dq.empty());
}

TEST(DequeTest, PopOnEmptyDequeThrows) {
    Deque<int> dq(3);

    EXPECT_THROW(dq.pop_front(), std::out_of_range);
    EXPECT_THROW(dq.pop_back(), std::out_of_range);
}

