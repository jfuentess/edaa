/** uhr: generic time performance tester
 * Author: LELE
 *
 * Things to set up:
 * 0. Number of runs: in RUNS,
 * 1. LOWER, UPPER, STEP bounds for test type,
 * 2. Time unit: in elapsed_time,
 * 3. What to write on time_data,
 * 4. The experiments: in outer for loop. */

#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

// Change these depending on application
#define RUNS 256
#define LOWER 0
#define UPPER 1024
#define STEP 128

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << "Usage requires exactly one argument: <filename>" << std::endl;
        std::cerr << "<filename> is the name of the file where performance data will be written." << std::endl;
        std::cerr << "It is recommended for <filename> to have .csv extension and it should not previously exist." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // Set up clock variables
    int64_t n, i;
    double time[RUNS];
    double mean_time, time_stdev, dev;
    auto begin_time = std::chrono::high_resolution_clock::now();
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> elapsed_time = end_time - begin_time;

    // File to write time data
    std::ofstream time_data;
    time_data.open(argv[1]);
    time_data << "n,t_mean,t_stdev" << std::endl;

    // Begin testing
    for (n = LOWER; n <= UPPER; n += STEP) {
        mean_time = 0;
        time_stdev = 0;

        // Test configuration goes here

        // Run to compute elapsed time
        for (i = 0; i < RUNS; i++) {
            begin_time = std::chrono::high_resolution_clock::now();
            // Function to test goes here
            end_time = std::chrono::high_resolution_clock::now();

            elapsed_time = end_time - begin_time;
            time[i] = elapsed_time.count();

            mean_time += time[i];
        }

        // Compute statistics
        mean_time /= RUNS;

        for (i = 0; i < RUNS; i++) {
            dev = time[i] - mean_time;
            time_stdev += dev * dev;
        }

        time_stdev /= RUNS - 1; // Subtract 1 to get unbiased estimator
        time_stdev = std::sqrt(time_stdev);

        time_data << n << "," << mean_time << "," << time_stdev << std::endl;
    }

    time_data.close();

    return 0;
}
