/* Author: LELE */

#ifndef BINARY_HEAP
#define BINARY_HEAP

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

/** Implements a binary heap using C++'s STL */
template<typename T>
class binary_heap
{
    protected:
        std::vector<T> data;

    public:
        /** Empty constructor to create an empty heap */
        binary_heap(void)
        {
        }

        binary_heap(const std::vector<T> &v) : data(v)
        {
            std::make_heap(data.begin(), data.end());
        }

        T top(void)
        {
            if (!data.empty())
                return data.front();

            std::cerr << "There's no top: heap is empty." << std::endl;
            std::exit(EXIT_FAILURE);
        }

        void push(T key)
        {
            data.push_back(key);
            std::push_heap(data.begin(), data.end());
        }

        void pop(void)
        {
            std::pop_heap(data.begin(), data.end());
            data.pop_back();
        }

        void meld(const binary_heap &h)
        {
            data.insert(data.end(), h.data.begin(), h.data.end());
            std::make_heap(data.begin(), data.end());
        }

        bool empty(void)
        {
            return data.empty();
        }
};

#endif
