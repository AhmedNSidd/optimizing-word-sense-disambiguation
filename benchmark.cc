#include <benchmark/benchmark.h>
#include "wsd.hpp"

static void BM_StringCreation(benchmark::State& state) {
  for (auto _ : state)
    simplified_wsd("stock", "I'm expecting to make a lot of money from the stocks I'm investing in using my bank account. They rushed out the door, grabbing anything and everything they could think of they might need. There was no time to double-check to make sure they weren't leaving something important behind. Everything was thrown into the car and they sped off. Thirty minutes later they were safe and that was when it dawned on them that they had forgotten the most important thing of all.");
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);

BENCHMARK_MAIN();
