#pragma once

namespace algo {

template <typename InputIt, typename OutputIt>
OutputIt copy(InputIt first, InputIt last, OutputIt dest) {
    while (first != last) {
        *dest = *first;
        ++first;
        ++dest;
    }
    return dest;
}

}
