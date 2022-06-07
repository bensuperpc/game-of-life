file(
    RELATIVE_PATH relative_path
    "/${game-of-life_INSTALL_CMAKEDIR}"
    "/${CMAKE_INSTALL_BINDIR}/${game-of-life_NAME}"
)

get_filename_component(prefix "${CMAKE_INSTALL_PREFIX}" ABSOLUTE)
set(config_dir "${prefix}/${game-of-life_INSTALL_CMAKEDIR}")
set(config_file "${config_dir}/game-of-lifeConfig.cmake")

message(STATUS "Installing: ${config_file}")
file(WRITE "${config_file}" "\
get_filename_component(
    _game-of-life-cpp-executable
    \"\${CMAKE_CURRENT_LIST_DIR}/${relative_path}\"
    ABSOLUTE
)
set(
    GAME_OF_LIFE_EXECUTABLE \"\${_game-of-life-cpp-executable}\"
    CACHE FILEPATH \"Path to the game-of-life executable\"
)
")
list(APPEND CMAKE_INSTALL_MANIFEST_FILES "${config_file}")
