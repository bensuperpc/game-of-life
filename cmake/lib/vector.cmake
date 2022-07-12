cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
  vector
  GIT_REPOSITORY https://github.com/bensuperpc/vector.git
  GIT_TAG 99253acc36a8f48ead0f6748d42180fd7d3b6a61) # 07-07-2022

FetchContent_MakeAvailable(vector)
