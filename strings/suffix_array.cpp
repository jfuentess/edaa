/** Author: LELE
 *
 * O(n lg n) Suffix Array construction with O(m lg n) matching. */

#ifndef SUFFIX_ARRAY
#define SUFFIX_ARRAY

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

class suffix_array
{
private:
    std::string _t;
    std::string_view t;
    std::vector<std::int64_t> SA;

public:
    suffix_array(const std::string &text)
    {
        // Add lexicographically minimal char at end of text
        // Done to properly compare suffixes
        char ETX = 3;
        _t = text + ETX;
        t = _t;

        std::int64_t n, sigma, one, i, j, k;
        n = t.length();
        sigma = 256; // Size of alphabet, ASCII for now
                     // If changed, must implement key function that maps
                     // symbols to integers in range 0..sigma uniquely
        one = 1;

        SA.resize(n);
        std::vector<std::int64_t> count(std::max(sigma, n), 0);
        std::vector<std::int64_t> p(n); // For shifted indices
        std::vector<std::int64_t> q(n); // Helper for rank
        std::vector<std::int64_t> r(n); // For ranks

        // Counting sort substrings of length 1
        for (i = 0; i < n; i++)
            count[t[i]]++;
        for (i = 1; i < sigma; i++)
            count[i] += count[i - 1];
        for (i = n - 1; i >= 0; i--)
            SA[--count[t[i]]] = i;

        // Set up ranks by comparing pairs and increasing by one if different
        r[SA[0]] = 0;
        j = 0;
        for (i = 1; i < n; i++) {
            if (t[SA[i - 1]] != t[SA[i]])
                j++;
            r[SA[i]] = j;
        }

        for (k = 0; (one << k) < n; k++) {
            // Find cyclic shifted index
            for (i = 0; i < n; i++) {
                p[i] = SA[i] - (one << k);
                if (p[i] < 0)
                    p[i] += n;
            }

            // Sort again using radix sort
            // This is just a counting sort, but works as a faster
            // radix sort because of the shifting hack
            // We sort first with second half and then first half,
            // but only once, so it is faster
            for (i = 0; i <= j; i++)
                count[i] = 0;
            for (i = 0; i < n; i++)
                count[r[p[i]]]++;
            for (i = 1; i <= j; i++)
                count[i] += count[i - 1];
            for (i = n - 1; i >= 0; i--)
                SA[--count[r[p[i]]]] = p[i];

            // Recompute ranks
            q[SA[0]] = 0;
            j = 0;
            for (i = 1; i < n; i++) {
                // Check if first half or second half differ
                if (r[SA[i - 1]] != r[SA[i]] ||
                    r[(SA[i - 1] + (one << k)) % n] != r[(SA[i] + (one << k)) % n])
                    j++;

                q[SA[i]] = j;
            }

            for (i = 0; i < n; i++)
                r[i] = q[i];
        }
    }

    std::int64_t count(const std::string_view s)
    {
        if (s.length() > t.length())
            return 0;

        std::int64_t n, lo, mi, hi, matches;
        n = t.length();

        // Find lower bound
        lo = 0;
        hi = n;
        while (lo < hi) {
            mi = lo + (hi - lo) / 2;
            if (t.substr(SA[mi]) < s)
                lo = mi + 1;
            else
                hi = mi;
        }
        matches = lo;

        // Find upper bound
        // Do not set lo = 0 since it is already at lower bound
        hi = n;
        while (lo < hi) {
            mi = lo + (hi - lo) / 2;
            if (t.substr(SA[mi]).starts_with(s)) // Suffixes with same prefix are contiguous in SA
                lo = mi + 1;
            else
                hi = mi;
        }
        matches = hi - matches;

        return matches;
    }
};

#endif
