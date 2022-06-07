include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package game-of-life)

install(
    TARGETS game-of-life-cpp-exe
    RUNTIME COMPONENT game-of-life_Runtime
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    game-of-life_INSTALL_CMAKEDIR "${CMAKE_INSTALL_DATADIR}/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
mark_as_advanced(game-of-life_INSTALL_CMAKEDIR)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${game-of-life_INSTALL_CMAKEDIR}"
    COMPONENT game-of-life_Development
)

# Export variables for the install script to use
install(CODE "
set(game-of-life_NAME [[$<TARGET_FILE_NAME:game-of-life-cpp-exe>]])
set(game-of-life_INSTALL_CMAKEDIR [[${game-of-life_INSTALL_CMAKEDIR}]])
set(CMAKE_INSTALL_BINDIR [[${CMAKE_INSTALL_BINDIR}]])
" COMPONENT game-of-life_Development)

install(
    SCRIPT cmake/install-script.cmake
    COMPONENT game-of-life_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
