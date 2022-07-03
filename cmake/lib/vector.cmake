cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
  vector
  GIT_REPOSITORY https://github.com/bensuperpc/vector.git
  GIT_TAG 3088b2b38d239fc354ce7e140ebc0a89ede7c4fb) # 03-07-2022

FetchContent_MakeAvailable(vector)
