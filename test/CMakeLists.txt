# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(game-of-lifeTests LANGUAGES CXX)

# ---- Tests ----

add_executable(game-of-life_test source/game-of-life_test.cpp)
target_link_libraries(game-of-life_test PRIVATE game-of-life_lib)
target_compile_features(game-of-life_test PRIVATE cxx_std_17)

add_test(NAME game-of-life_test COMMAND game-of-life_test)

# ---- End-of-file commands ----

add_folders(Test)
