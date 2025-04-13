#pragma once

namespace algo {

template <typename InputIt, typename T>
T accumulate(InputIt first, InputIt last, T init) {
    for (; first != last; ++first) {
        init = init + *first;
    }
    return init;
}

} 
