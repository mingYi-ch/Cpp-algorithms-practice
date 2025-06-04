# Interval map implmentation

I benchmarked two different implementations of interval map from me, the one with erase by range (`benchmark/interval_map_erase_range.hpp`) has better performance.

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
