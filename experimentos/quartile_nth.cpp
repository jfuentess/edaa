#ifndef QUARTILE_NTH
#define QUARTILE_NTH

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>

inline void quartile_nth(std::vector<double>& data, std::vector<double>& q)
{
    q.resize(5);
    std::size_t n = data.size();
    double t;

    if (n < 4) {
        std::cerr << "quartiles needs at least 4 data points." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    auto q0 = data.begin();
    auto q1 = q0 + n / 4;
    auto q2 = q0 + n / 2;
    auto q3 = q0 + (3 * n) / 4;
    auto q4 = data.end() - 1;

    // Find min and max
    std::nth_element(data.begin(), q0, data.end());
    q[0] = *q0;
    std::nth_element(data.begin(), q4, data.end());
    q[4] = *q4;

    // Find median
    if (n % 2 == 1) {
        std::nth_element(data.begin(), q2, data.end());
        q[2] = *q2;
    } else {
        std::nth_element(data.begin(), q2, data.end());
        t = *q2;
        q2--;
        std::nth_element(data.begin(), q2, data.end());
        q[2] = ((*q2) + t) / 2.0;
    }

    // Find lower and upper quartiles
    if (n % 4 == 2 or n % 4 == 3) {
        std::nth_element(data.begin(), q1, data.end());
        q[1] = *q1;
        std::nth_element(data.begin(), q3, data.end());
        q[3] = *q3;
    } else {
        std::nth_element(data.begin(), q1, data.end());
        t = *q1;
        q1--;
        std::nth_element(data.begin(), q1, data.end());
        q[1] = 0.25 * (*q1) + 0.75 * t;
        std::nth_element(data.begin(), q3, data.end());
        t = *q3;
        q3--;
        std::nth_element(data.begin(), q3, data.end());
        q[3] = 0.75 * (*q3) + 0.25 * t;
    }
}

#endif
