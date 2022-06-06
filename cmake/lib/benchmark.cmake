cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG 6d50251d8e6ed6b7f6eb1e12c558d2808fb4ddaa) # 01-06-2022

# Disable tests on google benchmark
set(BENCHMARK_ENABLE_TESTING
    OFF
    CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_WERROR
    OFF
    CACHE BOOL "" FORCE)
set(BENCHMARK_FORCE_WERROR
    OFF
    CACHE BOOL "" FORCE)

set(BENCHMARK_ENABLE_INSTALL
    OFF
    CACHE BOOL "" FORCE)

set(BENCHMARK_DOWNLOAD_DEPENDENCIES
    ON
    CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googlebenchmark)