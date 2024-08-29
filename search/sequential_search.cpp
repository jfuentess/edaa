#ifndef SEQUENTIAL_SEARCH
#define SEQUENTIAL_SEARCH

#include <cstdint>

/** Returns position of key in data.
 * If not found, returns -1 */
template<typename T>
std::int64_t sequential_search(T *data, std::int64_t size, T key)
{
    for (std::int64_t i = 0; i < size; i++)
        if (data[i] == key)
            return i;

    return -1;
}

#endif
