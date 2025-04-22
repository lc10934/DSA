#pragma once
#include <iterator>
#include <functional>
#include <algorithm>

namespace algo {

template <typename RandomIt, typename Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
void sort(RandomIt first, RandomIt last, Compare comp = Compare()) {
    if (first >= last || (last - first) <= 1) {
        return;
    }
    
    auto pivot = *(first + (last - first) / 2);
    RandomIt left = first;
    RandomIt right = last - 1;
    
    while (left <= right) {
        while (comp(*left, pivot)) {
            ++left;
        }
        while (comp(pivot, *right)) {
            --right;
        }
        if (left <= right) {
            std::iter_swap(left, right);
            ++left;
            --right;
        }
    }
    algo::sort(first, right + 1, comp);
    algo::sort(left, last, comp);
}

} 
