cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
  vector
  GIT_REPOSITORY https://github.com/bensuperpc/vector.git
  GIT_TAG 1c8f8b484d9bea7dc9792a771efbe4f1dfd06a9b) # 03-07-2022

FetchContent_MakeAvailable(vector)
