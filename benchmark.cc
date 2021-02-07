#include <benchmark/benchmark.h>
#include "simplified_wsd.hpp"

static void BM_StringCreation(benchmark::State& state) {
  for (auto _ : state)
    simplified_wsd("stock", "I'm expecting to make a lot of money from the stocks I'm investing in using my bank account.");
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);

BENCHMARK_MAIN();