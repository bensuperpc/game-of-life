##############################################################
#   ____                                                     #
#  | __ )  ___ _ __  ___ _   _ _ __   ___ _ __ _ __   ___    #
#  |  _ \ / _ \ '_ \/ __| | | | '_ \ / _ \ '__| '_ \ / __|   #
#  | |_) |  __/ | | \__ \ |_| | |_) |  __/ |  | |_) | (__    #
#  |____/ \___|_| |_|___/\__,_| .__/ \___|_|  | .__/ \___|   #
#                             |_|             |_|            #
##############################################################
#                                                            #
#  BenLib, 2021                                              #
#  Created: 16, March, 2021                                  #
#  Modified: 17, March, 2021                                 #
#  file: CMakeLists.txt                                      #
#  CMake                                                     #
#  Source:                                                   #
#  OS: ALL                                                   #
#  CPU: ALL                                                  #
#                                                            #
##############################################################

cmake_minimum_required(VERSION 3.14)
project(
    game-of-life-lib
    VERSION 0.1.0
    DESCRIPTION "game of life lib"
    HOMEPAGE_URL "https://github.com/bensuperpc"
    LANGUAGES C CXX
)

find_package(raylib QUIET)
find_package(raylib_cpp QUIET)
find_package(OpenMP 3.0 QUIET)


include(../../cmake/lib/vector.cmake)

set(SRCS
    source/gol.cpp
    source/gol.c
	)
	
set(HEADERS
    source/gol.h
    source/gol.hpp
    )

add_library(game-of-life-lib ${SRCS} ${HEADERS})

target_include_directories(
    game-of-life-lib
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_link_libraries(game-of-life-lib PRIVATE raylib raylib_cpp)

# Needed to be PUBLIC to link with game-of-life
target_link_libraries(game-of-life-lib PUBLIC vector::vector)

if (OpenMP_FOUND OR OpenMP_CXX_FOUND)
  target_link_libraries(game-of-life-lib PRIVATE OpenMP::OpenMP_CXX OpenMP::OpenMP_C)
  target_compile_definitions(game-of-life-lib PRIVATE -DENABLE_OPENMP)
endif()
