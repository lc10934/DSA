#pragma once
#include <iterator>
#include <algorithm>

namespace algo {

template <typename BidirectionalIt>
void reverse(BidirectionalIt first, BidirectionalIt last) {
    while ((first != last) && (first != --last)) {
        std::iter_swap(first, last);
        ++first;
    }
}

} 
