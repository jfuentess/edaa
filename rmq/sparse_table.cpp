/** Generic Sparse Table
 * O(n lg n) construction with O(lg n) queries for general f,
 * O(1) queries for idempotent and commutative f.
 *
 * Author: LELE */

#ifndef SPARSE_TABLE
#define SPARSE_TABLE

#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

template<class T>
class sparse_table
{
    private:
        std::vector<std::vector<T> > ST;
        std::function<T(T, T)> f;

        // Returns floor(lg(n))
        inline uint64_t _lg(uint64_t n)
        {
            if (n == 0) {
                std::cerr << "lg(0) is undefined." << std::endl;
                std::exit(EXIT_FAILURE);
            }

            return std::bit_width(n) - 1;
        }

    public:
        sparse_table(const std::vector<T> &A, std::function<T(T, T)> F)
        {
            if (A.size() == 0) {
                std::cerr << "Invalid input array: must be non-empty." << std::endl;
                std::exit(EXIT_FAILURE);
            }

            uint64_t i, j, m, n, p, q, one;
            n = A.size();
            m = _lg(n);
            one = 1;

            ST.resize(m + 1, std::vector<T>(n));
            f = F;

            // Store results for length one ranges
            for (j = 0; j < n; j++)
                ST[0][j] = A[j];

            // Compute results for queries of length equal to power of two
            for (i = 0; i < m; i++) {
                p = one << i;
                q = p << 1;
                for (j = 0; j <= n - q; j++)
                    ST[i + 1][j] = f(ST[i][j], ST[i][j + p]);
            }
        }

        // Answers A[i:j] queries in O(lg n) time
        T query(uint64_t i, uint64_t j)
        {
            if (i >= j || j > ST[0].size()) {
                std::cerr << "Invalid query " << i << " " << j << std::endl;
                std::exit(EXIT_FAILURE);
            }

            uint64_t one, b;
            one = 1;

            b = _lg(j - i);
            T q = ST[b][i];
            i += (one << b);

            while (i < j) {
                b = _lg(j - i);
                q = f(q, ST[b][i]);
                i += (one << b);
            }

            return q;
        }

        // Answers A[i:j] queries in constant time if f is idempotent and commutative
        T query_idempotent(uint64_t i, uint64_t j)
        {
            if (i >= j || j > ST[0].size()) {
                std::cerr << "Invalid query " << i << " " << j << std::endl;
                std::exit(EXIT_FAILURE);
            }

            uint64_t one, b;
            one = 1;
            b = _lg(j - i);

            return f(ST[b][i], ST[b][j - (one << b)]);
        }
};

#endif
