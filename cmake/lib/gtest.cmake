cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG 4556086674e4dfae2aa5f042d9e7844fc5ef9b89) # 11-07-2022

# Disable tests on gtest
set(gtest_build_tests
    OFF
    CACHE BOOL "" FORCE)
set(gtest_build_samples
    OFF
    CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
# Lib: gtest gtest_main
