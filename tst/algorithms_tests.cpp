#include <gtest/gtest.h>
#include <vector>
#include "../src/algorithms/sort.hpp"
#include "../src/algorithms/find.hpp"
#include "../src/algorithms/copy.hpp"
#include "../src/algorithms/reverse.hpp"
#include "../src/algorithms/accumulate.hpp"

TEST(QuickSortTest, SortsCorrectly) {
    std::vector<int> vec = { 5, 2, 9, 1, 5, 6 };
    algo::sort(vec.begin(), vec.end());
    std::vector<int> expected = { 1, 2, 5, 5, 6, 9 };
    EXPECT_EQ(vec, expected);
}

TEST(MyFindTest, FindsValue) {
    std::vector<int> vec = { 1, 3, 5, 7, 9 };
    auto it = algo::find(vec.begin(), vec.end(), 5);
    ASSERT_NE(it, vec.end());
    EXPECT_EQ(*it, 5);
}

TEST(MyFindTest, NotFound) {
    std::vector<int> vec = { 1, 3, 5, 7, 9 };
    auto it = algo::find(vec.begin(), vec.end(), 10);
    EXPECT_EQ(it, vec.end());
}

TEST(MyCopyTest, CopiesCorrectly) {
    std::vector<int> src = { 1, 2, 3, 4, 5 };
    std::vector<int> dest(src.size());
    algo::copy(src.begin(), src.end(), dest.begin());
    EXPECT_EQ(src, dest);
}

TEST(MyReverseTest, ReversesCorrectly) {
    std::vector<int> vec = { 1, 2, 3, 4, 5 };
    algo::reverse(vec.begin(), vec.end());
    std::vector<int> expected = { 5, 4, 3, 2, 1 };
    EXPECT_EQ(vec, expected);
}

TEST(MyAccumulateTest, AccumulatesCorrectly) {
    std::vector<int> vec = { 1, 2, 3, 4, 5 };
    int sum = algo::accumulate(vec.begin(), vec.end(), 0);
    EXPECT_EQ(sum, 15);
    sum = algo::accumulate(vec.begin(), vec.end(), 10);
    EXPECT_EQ(sum, 25);
}
