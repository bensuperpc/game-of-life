#include <vector>

#include <benchmark/benchmark.h>

#include "gol.h"
#include "gol.hpp"

static void gol_cpp_bench_update(benchmark::State& state)
{
  const auto width = state.range(0);
  const auto height = state.range(0);
  const auto cells = width * height;

  auto grid = benlib::Gol(width, height);
  grid.RandomFill();
  benchmark::DoNotOptimize(grid);

  for (auto _ : state) {
    grid.Update();
    benchmark::ClobberMemory();
  }

  state.SetItemsProcessed(state.iterations() * cells);
  state.SetBytesProcessed(state.iterations() * cells * sizeof(bool));
}
BENCHMARK(gol_cpp_bench_update)->Name("gol_cpp_bench_update")->RangeMultiplier(8)->Range(8, 4096);

static void gol_cpp_bench_random_fill(benchmark::State& state)
{
  const auto width = state.range(0);
  const auto height = state.range(0);
  const auto cells = width * height;

  auto grid = benlib::Gol(width, height);
  benchmark::DoNotOptimize(grid);

  for (auto _ : state) {
    grid.RandomFill();
    benchmark::ClobberMemory();
  }

  state.SetItemsProcessed(state.iterations() * cells);
  state.SetBytesProcessed(state.iterations() * cells * sizeof(bool));
}
BENCHMARK(gol_cpp_bench_random_fill)->Name("gol_cpp_bench_random_fill")->RangeMultiplier(4)->Range(64, 1024);

static void gol_cpp_bench_random_fill2(benchmark::State& state)
{
  const auto width = state.range(0);
  const auto height = state.range(0);
  const auto cells = width * height;

  std::mt19937_64 rng;
  std::random_device rnd_device;
  rng.seed(rnd_device());

  auto grid = benlib::Gol(width, height);
  benchmark::DoNotOptimize(grid);

  for (auto _ : state) {
    grid.RandomFill(rng);
    benchmark::ClobberMemory();
  }

  state.SetItemsProcessed(state.iterations() * cells);
  state.SetBytesProcessed(state.iterations() * cells * sizeof(bool));
}
BENCHMARK(gol_cpp_bench_random_fill2)->Name("gol_cpp_bench_random_fill2")->RangeMultiplier(4)->Range(64, 1024);

static void gol_cpp_bench_fill(benchmark::State& state)
{
  const auto width = state.range(0);
  const auto height = state.range(0);
  const auto cells = width * height;

  std::mt19937_64 rng;
  std::random_device rnd_device;
  rng.seed(rnd_device());

  auto grid = benlib::Gol(width, height);
  benchmark::DoNotOptimize(grid);

  for (auto _ : state) {
    grid.Fill(true);
    benchmark::ClobberMemory();
  }

  state.SetItemsProcessed(state.iterations() * cells);
  state.SetBytesProcessed(state.iterations() * cells * sizeof(bool));
}
BENCHMARK(gol_cpp_bench_fill)->Name("gol_cpp_bench_fill")->RangeMultiplier(4)->Range(64, 1024);

static void gol_cpp_bench_reset(benchmark::State& state)
{
  const auto width = state.range(0);
  const auto height = state.range(0);
  const auto cells = width * height;

  auto grid = benlib::Gol(width, height);
  grid.Reset();
  benchmark::DoNotOptimize(grid);

  for (auto _ : state) {
    grid.Reset();
    benchmark::ClobberMemory();
  }

  state.SetItemsProcessed(state.iterations() * cells);
  state.SetBytesProcessed(state.iterations() * cells * sizeof(bool));
}
BENCHMARK(gol_cpp_bench_reset)->Name("gol_cpp_bench_reset")->RangeMultiplier(4)->Range(64, 512);

static void gol_c_bench_update(benchmark::State& state)
{
  const auto width = state.range(0);
  const auto height = state.range(0);
  const auto cells = width * height;

  bool** grid = CreateGrid(width, height);
  ResetGrid(grid, width, height);
  RandomFill(grid, width, height);

  benchmark::DoNotOptimize(grid);

  for (auto _ : state) {
    UpdateGrid(grid, width, height);
    benchmark::ClobberMemory();
  }
  FreeGrid(grid, width);

  state.SetItemsProcessed(state.iterations() * cells);
  state.SetBytesProcessed(state.iterations() * cells * sizeof(bool));
}
BENCHMARK(gol_c_bench_update)->Name("gol_c_bench_update")->RangeMultiplier(8)->Range(8, 4096);

static void gol_c_bench_random_fill(benchmark::State& state)
{
  const auto width = state.range(0);
  const auto height = state.range(0);
  const auto cells = width * height;

  bool** grid = CreateGrid(width, height);
  ResetGrid(grid, width, height);

  benchmark::DoNotOptimize(grid);

  for (auto _ : state) {
    RandomFill(grid, width, height);
    benchmark::ClobberMemory();
  }
  FreeGrid(grid, width);

  state.SetItemsProcessed(state.iterations() * cells);
  state.SetBytesProcessed(state.iterations() * cells * sizeof(bool));
}
BENCHMARK(gol_c_bench_random_fill)->Name("gol_c_bench_random_fill")->RangeMultiplier(2)->Range(16, 64);

static void gol_c_bench_reset(benchmark::State& state)
{
  const auto width = state.range(0);
  const auto height = state.range(0);
  const auto cells = width * height;

  bool** grid = CreateGrid(width, height);
  ResetGrid(grid, width, height);

  benchmark::DoNotOptimize(grid);

  for (auto _ : state) {
    ResetGrid(grid, width, height);
    benchmark::ClobberMemory();
  }
  FreeGrid(grid, width);

  state.SetItemsProcessed(state.iterations() * cells);
  state.SetBytesProcessed(state.iterations() * cells * sizeof(bool));
}
BENCHMARK(gol_c_bench_reset)->Name("gol_c_bench_reset")->RangeMultiplier(4)->Range(64, 1024);
