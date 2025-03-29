#include <gtest/gtest.h>
#include "../src/ringbuffer.hpp"  // Include the ring buffer header.
#include <vector>
#include <stdexcept>

// Test that push() and to_vector() work as expected.
TEST(RingBufferTest, PushAndToVectorTest) {
    RingBuffer<int> rb(5);
    rb.push(1);
    rb.push(2);
    rb.push(3);
    std::vector<int> expected = {1, 2, 3};
    EXPECT_EQ(rb.to_vector(), expected);
}

// Test that pushing into a full buffer overwrites the oldest element.
TEST(RingBufferTest, OverwriteTest) {
    RingBuffer<int> rb(5);
    // Fill the buffer.
    for (int i = 1; i <= 5; ++i) {
        rb.push(i);
    }
    // Buffer is full; next push overwrites the oldest element.
    rb.push(6);
    // Expected FIFO order becomes {2, 3, 4, 5, 6}.
    std::vector<int> expected = {2, 3, 4, 5, 6};
    EXPECT_EQ(rb.to_vector(), expected);
}

// Test that pop() returns elements in FIFO order.
TEST(RingBufferTest, PopTest) {
    RingBuffer<int> rb(5);
    for (int i = 1; i <= 5; ++i) {
        rb.push(i);
    }
    // Pop two elements.
    int first = rb.pop();
    int second = rb.pop();
    EXPECT_EQ(first, 1);
    EXPECT_EQ(second, 2);
    // Expected remaining elements: {3, 4, 5}
    std::vector<int> expected = {3, 4, 5};
    EXPECT_EQ(rb.to_vector(), expected);
}

// Test the empty and full state of the buffer.
TEST(RingBufferTest, EmptyAndFullTest) {
    RingBuffer<int> rb(3);
    EXPECT_TRUE(rb.empty());
    EXPECT_FALSE(rb.full());
    
    rb.push(10);
    EXPECT_FALSE(rb.empty());
    EXPECT_FALSE(rb.full());
    
    rb.push(20);
    rb.push(30);
    EXPECT_TRUE(rb.full());
    
    // After popping, the buffer should no longer be full.
    rb.pop();
    EXPECT_FALSE(rb.full());
}

// Test that pop() on an empty buffer throws an exception.
TEST(RingBufferTest, PopEmptyTest) {
    RingBuffer<int> rb(3);
    EXPECT_THROW(rb.pop(), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
