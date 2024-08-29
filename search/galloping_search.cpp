#ifndef GALLOPING_SEARCH
#define GALLOPING_SEARCH

#include <cstdint>

#include "binary_search.cpp"

/** Returns position of key in data.
 * If not found, returns -1 */
template<typename T>
std::int64_t galloping_search(T *data, std::int64_t size, T key)
{
    // Check first few positions to prepare the search
    if (key < data[0])
        return -1;
    else if (size > 0 && key == data[0])
        return 0;
    else if (size > 1 && key == data[1])
        return 1;
    else if (size > 2 && key == data[2])
        return 2;

    // Begin sequential search over postitions that are a power of 2
    // to locate interval to perform binary search
    std::int64_t i, j, lo, hi;

    i = 4;
    while (i < size && data[i] < key)
        i *= 2;

    // If key already found, no need for binary search
    if (i < size && key == data[i])
        return i;

    // Prepare binary search
    // We know that data[0..lo] does not contain key
    // And that either we have to check last segment
    // or that data[i] >= key
    lo = i / 2 + 1;

    if (i < size)
        hi = lo - 1;
    else
        hi = size - lo;

    // This is the shifted position of key if found
    j = binary_search(data + lo, hi, key);

    if (j != -1)
        return lo + j; // undoes shift if found

    return -1;
}

#endif
