/** Generic Segment Tree for RMQs
 * O(n) construction with O(lg n) queries.
 * T must allow a total ordering <.
 *
 * Author: LELE */
 
#ifndef SEGMENT_TREE
#define SEGMENT_TREE
 
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>
 
template<class T>
class segment_tree
{
    private:
        std::vector<T> ST;
 
        inline T _min(const T &x, const T &y)
        {
            return x < y ? x : y;
        }
 
    public:
        segment_tree(const std::vector<T> &A)
        {
            if (A.size() == 0) {
                std::cerr << "Invalid input array: must be non-empty." << std::endl;
                std::exit(EXIT_FAILURE);
            }
 
            uint64_t n, i, j;
            n = A.size();
            ST.resize(n << 1); // Size is 2n
 
            // Load A as leaves of tree
            for (i = 0; i < n; i++)
                ST[i + n] = A[i];
 
            // Combine intervals bottom-up
            for (i = n - 1; i > 0; i--) {
                j = i << 1;
                ST[i] = _min(ST[j], ST[j | 1]);
            }
        }
 
        // Answers min A[i:j] in O(lg n) time
        T query(uint64_t i, uint64_t j)
        {
            uint64_t n = ST.size() >> 1;

            if (i >= j || j > n) {
                std::cerr << "Invalid query " << i << " " << j << std::endl;
                std::exit(EXIT_FAILURE);
            }
 
            T q = ST[i + n]; // Initialize query result as an element that's always in A[i:j]
            // Go bottom-up combining values in node to answer query
            for (i += n, j += n; i < j; i >>= 1, j >>= 1) {
                if (i & 1)
                    q = _min(q, ST[i++]);
                if (j & 1)
                    q = _min(q, ST[--j]);
            }
 
            return q;
        }
 
        // Changes value at index i to x
        void update(uint64_t i, const T x)
        {
            uint64_t n = ST.size() >> 1;
 
            if (i >= n) {
                std::cerr << "Invalid update " << i << std::endl;
                std::exit(EXIT_FAILURE);
            }
 
            // Update parent nodes until root
            for (ST[i += n] = x; i > 1; i >>= 1)
                ST[i >> 1] = _min(ST[i], ST[i ^ 1]); // i ^ 1 gives the sibling node to i
        }
};
 
#endif
