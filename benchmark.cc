#include <benchmark/benchmark.h>
#include "wsd.hpp"

static void BM_StringCreation(benchmark::State& state) {
  for (auto _ : state)
    for (int i = 0; i < 100; i++) {
          simplified_wsd("stock", "I'm expecting to make a lot of money from the stocks I'm investing in using my bank account. They rushed out the door, grabbing anything and everything they could think of they might need. There was no time to double-check to make sure they weren't leaving something important behind. Everything was thrown into the car and they sped off. Thirty minutes later they were safe and that was when it dawned on them that they had forgotten the most important thing of all. These words are added here to increase the set size of the context vector in order to properly test out the effectiveness of the temporal locality that we are trying to optimize. If there are not enough words in here then I hypothesize that the optimized code will probably not be effective. So this is me just typing more words in here. Okay this might be enough words. Let us see. Hope your day is going well by the way.");
    }
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);

BENCHMARK_MAIN();
