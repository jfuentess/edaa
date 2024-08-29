#ifndef BINARY_SEARCH
#define BINARY_SEARCH

#include <cstdint>

/** Returns position of key in data.
 * If not found, returns -1 */
template<typename T>
std::int64_t binary_search(T *data, std::int64_t size, T key)
{
    std::int64_t lo, mi, hi;
    lo = 0;
    hi = size - 1;

    while (lo != hi) {
        mi = (lo + hi + 1) / 2; // 1 is added to compute the ceiling of the semi-sum
        if (key < data[mi])
            hi = mi - 1;
        else
            lo = mi;
    }

    if (data[lo] == key)
        return lo;

    return -1;
}

#endif
