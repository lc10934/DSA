#include <gtest/gtest.h>
#include "../src/queue.hpp"  
#include <vector>
#include <stdexcept>

TEST(QueueTest, EnqueueAndDequeue) {
    Queue<int> q(5);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    
    EXPECT_EQ(q.size(), 3);
    
    auto first = q.dequeue();
    ASSERT_TRUE(first.has_value());
    EXPECT_EQ(first.value(), 1);
    
    auto second = q.dequeue();
    ASSERT_TRUE(second.has_value());
    EXPECT_EQ(second.value(), 2);
    
    auto third = q.dequeue();
    ASSERT_TRUE(third.has_value());
    EXPECT_EQ(third.value(), 3);
    
    EXPECT_TRUE(q.empty());
}

TEST(QueueTest, FrontAndBack) {
    Queue<int> q(4);
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    
    auto frontOpt = q.front();
    ASSERT_TRUE(frontOpt.has_value());
    EXPECT_EQ(frontOpt.value(), 10);
    
    auto backOpt = q.back();
    ASSERT_TRUE(backOpt.has_value());
    EXPECT_EQ(backOpt.value(), 30);
}

TEST(QueueTest, ResizingTest) {
    Queue<int> q(4);
    for (int i = 1; i <= 10; ++i) {
        q.enqueue(i);
    }
    EXPECT_EQ(q.size(), 10);
    
    for (int i = 1; i <= 10; ++i) {
        auto item = q.dequeue();
        ASSERT_TRUE(item.has_value());
        EXPECT_EQ(item.value(), i);
    }
    EXPECT_TRUE(q.empty());
}

TEST(QueueTest, DequeueOnEmptyQueue) {
    Queue<int> q(3);
    EXPECT_FALSE(q.dequeue().has_value());
}

TEST(QueueTest, FrontBackOnEmptyQueue) {
    Queue<int> q(3);
    EXPECT_FALSE(q.front().has_value());
    EXPECT_FALSE(q.back().has_value());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
