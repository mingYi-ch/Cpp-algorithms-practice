# Leetcode-150-Algorithms-Submission-C++

## Requirements

- C++20 compatible compiler (e.g., `g++ >= 10`, `clang++ >= 11`)
- [Google Benchmark](https://github.com/google/benchmark)
- pthread (usually available by default on Unix-like systems)

## How to Run

Navigate to the `benchmark` directory and run the following command:

```bash
g++ -std=c++20 -O2 -march=native benchmark_im.cpp \
    -lbenchmark -lpthread -o bm_interval_map && ./bm_interval_map

The benchmark is tested on Mac OS.