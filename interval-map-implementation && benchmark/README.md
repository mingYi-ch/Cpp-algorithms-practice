# Leetcode-150-Algorithms-Submission-C++

## Requirements

- [Google Benchmark](https://github.com/google/benchmark)

## How to Run

Navigate to the `benchmark` directory and run the following command:

```bash
g++ -std=c++20 -O2 -march=native benchmark_im.cpp \
    -lbenchmark -lpthread -o bm_interval_map && ./bm_interval_map
