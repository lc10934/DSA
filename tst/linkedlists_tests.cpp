#include <gtest/gtest.h>
#include "../src/linkedlists.cpp" 

TEST(DoublyLinkedListTest, PushFrontTest) {
    DoublyLinkedList<int> list;
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    
    std::vector<int> expected = {30, 20, 10};
    EXPECT_EQ(list.to_vector(), expected);
}

TEST(DoublyLinkedListTest, PushBackTest) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    
    std::vector<int> expected = {10, 20, 30};
    EXPECT_EQ(list.to_vector(), expected);
}

TEST(DoublyLinkedListTest, PopFrontTest) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    
    list.pop_front(); // removes 10
    std::vector<int> expected = {20, 30};
    EXPECT_EQ(list.to_vector(), expected);
    
    list.pop_front(); // removes 20
    expected = {30};
    EXPECT_EQ(list.to_vector(), expected);
    
    list.pop_front(); // removes 30, list becomes empty
    expected = {};
    EXPECT_EQ(list.to_vector(), expected);
}

TEST(DoublyLinkedListTest, PopBackTest) {
    DoublyLinkedList<int> list;
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    
    list.pop_back(); // removes 10
    std::vector<int> expected = {30, 20};
    EXPECT_EQ(list.to_vector(), expected);
    
    list.pop_back(); // removes 20
    expected = {30};
    EXPECT_EQ(list.to_vector(), expected);
    
    list.pop_back(); // removes 30, list becomes empty
    expected = {};
    EXPECT_EQ(list.to_vector(), expected);
}
