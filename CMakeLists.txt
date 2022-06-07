cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    game-of-life
    VERSION 0.1.0
    DESCRIPTION "game-of-life"
    HOMEPAGE_URL "https://github.com/bensuperpc"
    LANGUAGES C CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# set(OpenGL_GL_PREFERENCE GLVND)

# ---- Enable ccache ----
include(cmake/ccache.cmake)
# include(cmake/lto.cmake)

# ---- Download and install dependencies
set(FETCHCONTENT_BASE_DIR "${CMAKE_BINARY_DIR}/3rd-party" CACHE BOOL "" FORCE)
set(FETCHCONTENT_QUIET FALSE CACHE BOOL "" FORCE)

include(cmake/lib/raylib.cmake)
include(cmake/lib/raygui.cmake)
include(cmake/lib/raylib-cpp.cmake)

include(cmake/lib/json.cmake)

include(FetchContent)

FetchContent_Declare(bs-thread-pool
    GIT_REPOSITORY https://github.com/bshoshany/thread-pool.git
    GIT_TAG 9d43f5d05d11835ec027ae0679f8cd8a1a87e9cb # 2022-05-31
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)
FetchContent_MakeAvailable(bs-thread-pool)
include_directories("${bs-thread-pool_SOURCE_DIR}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#[[
FetchContent_Declare(
    sfml
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG        65e357e901ff9b43d3f4cfff7b20cbaa50beb95a # 2022-05-11
)

set(SFML_BUILD_DOC OFF)
set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_TEST_SUIT OFF)

FetchContent_MakeAvailable(sfml)
]]

# ---- Declare library ----

#[[
add_library(
    game-of-life_lib OBJECT
    source/lib.cpp
)

target_include_directories(
    game-of-life_lib ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(game-of-life_lib PUBLIC cxx_std_17)
]]

add_subdirectory(source/lib)

# ---- Declare executable raylib-cpp ----

add_executable(game-of-life-cpp-exe source/main-raylib-cpp.cpp)
add_executable(game-of-life-cpp::exe ALIAS game-of-life-cpp-exe)

set_target_properties(
    game-of-life-cpp-exe PROPERTIES
    OUTPUT_NAME game-of-life-cpp
    EXPORT_NAME exe
)

#target_compile_features(game-of-life-cpp-exe PRIVATE cxx_std_17)

target_link_libraries(game-of-life-cpp-exe PRIVATE game-of-life-lib)

target_link_libraries(game-of-life-cpp-exe PRIVATE raylib raylib_cpp)

# ---- Declare executable raylib ----

add_executable(game-of-life-exe source/main-raylib.c)
add_executable(game-of-life::exe ALIAS game-of-life-exe)

set_target_properties(
    game-of-life-exe PROPERTIES
    OUTPUT_NAME game-of-life
    EXPORT_NAME exe
)

#target_compile_features(game-of-life-exe PRIVATE cxx_std_17)

target_link_libraries(game-of-life-exe PRIVATE game-of-life-lib)

target_link_libraries(game-of-life-exe PRIVATE raylib)


# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT game-of-life_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of game-of-life"
  )
endif()

include(cmake/dev-mode.cmake)
