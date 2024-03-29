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

# ---- Enable Utile ----
include(cmake/utile/ccache.cmake)
# include(cmake/utile/lto.cmake)
# include(cmake/utile/ninja_color.cmake)
# include(cmake/lib/backward-cpp.cmake)

# ---- Download and install dependencies

# ---- Enable Utile ----
find_package(OpenMP 3.0)

set(FETCHCONTENT_BASE_DIR "${CMAKE_BINARY_DIR}/3rd-party" CACHE BOOL "" FORCE)
set(FETCHCONTENT_QUIET FALSE CACHE BOOL "" FORCE)

include(cmake/lib/raylib.cmake)
include(cmake/lib/raygui.cmake)
include(cmake/lib/raylib-cpp.cmake)
include(cmake/lib/vector.cmake)

# include(cmake/lib/json.cmake)

include(FetchContent)

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

add_executable(game-of-life-cpp_exe source/main-raylib-cpp.cpp)
add_executable(game-of-life-cpp::exe ALIAS game-of-life-cpp_exe)

set_target_properties(
    game-of-life-cpp_exe PROPERTIES
    OUTPUT_NAME game-of-life-cpp
    EXPORT_NAME exe
)

#target_compile_features(game-of-life-cpp_exe PRIVATE cxx_std_17)

target_link_libraries(game-of-life-cpp_exe PRIVATE game-of-life-lib)

target_link_libraries(game-of-life-cpp_exe PRIVATE raylib raylib_cpp)

if (OpenMP_FOUND OR OpenMP_CXX_FOUND)
  target_link_libraries(game-of-life-cpp_exe PRIVATE OpenMP::OpenMP_CXX)
endif()

# ---- Declare executable raylib ----

add_executable(game-of-life-c_exe source/main-raylib.c)
add_executable(game-of-life-c::exe ALIAS game-of-life-c_exe)

set_target_properties(
    game-of-life-c_exe PROPERTIES
    OUTPUT_NAME game-of-life-c
    EXPORT_NAME exe
)

#target_compile_features(game-of-life-c_exe PRIVATE cxx_std_17)

target_link_libraries(game-of-life-c_exe PRIVATE game-of-life-lib)

target_link_libraries(game-of-life-c_exe PRIVATE raylib)

#if (OpenMP_FOUND OR OpenMP_CXX_FOUND)
#  target_link_libraries(game-of-life-c_exe PRIVATE OpenMP::OpenMP_CXX)
#endif()


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
