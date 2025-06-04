// bm_interval_map.cpp
#include <benchmark/benchmark.h>
#include "interval_map_erase_range.hpp"
#include "interval_map_optimal_not.hpp"
#include <vector>
#include <random>

// Prepare some synthetic keys/values for testing
static std::vector<int> keys;
static void init_keys()
{
    if (!keys.empty())
        return;
    std::mt19937 rng(123);
    std::uniform_int_distribution<int> dist(0, 10'000);
    // std::uniform_int_distribution<int> dist(0, 100);
    keys.resize(1'000'000);
    for (auto &k : keys)
        k = dist(rng);
}

// Benchmark for interval_map_optimal_not
static void BM_IntervalMap_optimal_not_Assign(benchmark::State &state)
{
    init_keys();
    for (auto _ : state)
    {
        interval_map_optimal_not::interval_map<int, char> m('A');
        for (int i = 0; i < keys.size(); ++i)
        {
            int a = keys[i];
            int b = keys[i + 1];
            if (a > b)
                std::swap(a, b);
            m.assign(a, b, char('A' + (i % 26)));
        }
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_IntervalMap_optimal_not_Assign)->Unit(benchmark::kMillisecond);

// Benchmark for interval_map_erase_range
static void BM_IntervalMap_erase_range_Assign(benchmark::State &state)
{
    init_keys();
    for (auto _ : state)
    {
        interval_map_erase_range::interval_map<int, char> m('A');
        // assign random intervals
        for (int i = 0; i < keys.size(); ++i)
        {
            int a = keys[i];
            int b = keys[i + 1];
            if (a > b)
                std::swap(a, b);
            m.assign(a, b, char('A' + (i % 26)));
        }
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_IntervalMap_erase_range_Assign)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
