#include <gtest/gtest.h>
#include "../src/deque.hpp" 
#include <vector>
#include <stdexcept>

TEST(DequeTest, PushBackAndPopFront) {
    Deque<int> dq(5);
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);
    
    EXPECT_EQ(dq.size(), 3);
    
    auto first = dq.pop_front();
    ASSERT_TRUE(first.has_value());
    EXPECT_EQ(first.value(), 1);
    
    auto second = dq.pop_front();
    ASSERT_TRUE(second.has_value());
    EXPECT_EQ(second.value(), 2);
    
    auto third = dq.pop_front();
    ASSERT_TRUE(third.has_value());
    EXPECT_EQ(third.value(), 3);
    
    EXPECT_TRUE(dq.empty());
}

TEST(DequeTest, PushFrontAndPopBack) {
    Deque<int> dq(5);
    dq.push_front(1);
    dq.push_front(2);  
    dq.push_front(3);  
    
    EXPECT_EQ(dq.size(), 3);
    
    auto first = dq.pop_back();
    ASSERT_TRUE(first.has_value());
    EXPECT_EQ(first.value(), 1);
    
    auto second = dq.pop_back();
    ASSERT_TRUE(second.has_value());
    EXPECT_EQ(second.value(), 2);
    
    auto third = dq.pop_back();
    ASSERT_TRUE(third.has_value());
    EXPECT_EQ(third.value(), 3);
    
    EXPECT_TRUE(dq.empty());
}

TEST(DequeTest, MixedOperations) {
    Deque<int> dq(4);
    dq.push_back(10);   
    dq.push_front(20);  
    dq.push_back(30);   
    dq.push_front(40);  
    
    auto frontOpt = dq.front();
    ASSERT_TRUE(frontOpt.has_value());
    EXPECT_EQ(frontOpt.value(), 40);
    
    auto backOpt = dq.back();
    ASSERT_TRUE(backOpt.has_value());
    EXPECT_EQ(backOpt.value(), 30);
    
    auto popF = dq.pop_front();
    ASSERT_TRUE(popF.has_value());
    EXPECT_EQ(popF.value(), 40);
    
    auto popB = dq.pop_back();
    ASSERT_TRUE(popB.has_value());
    EXPECT_EQ(popB.value(), 30);
    
    EXPECT_EQ(dq.size(), 2);
    auto newFront = dq.front();
    ASSERT_TRUE(newFront.has_value());
    EXPECT_EQ(newFront.value(), 20);
    auto newBack = dq.back();
    ASSERT_TRUE(newBack.has_value());
    EXPECT_EQ(newBack.value(), 10);
}

TEST(DequeTest, ResizingTest) {
    Deque<int> dq(4);
    for (int i = 1; i <= 10; ++i) {
        dq.push_back(i);
    }
    EXPECT_EQ(dq.size(), 10);
    
    // Verify order using pop_front
    for (int i = 1; i <= 10; ++i) {
        auto item = dq.pop_front();
        ASSERT_TRUE(item.has_value());
        EXPECT_EQ(item.value(), i);
    }
    EXPECT_TRUE(dq.empty());
}

TEST(DequeTest, PopOnEmptyDeque) {
    Deque<int> dq(3);
    EXPECT_FALSE(dq.pop_front().has_value());
    EXPECT_FALSE(dq.pop_back().has_value());
}
  
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
