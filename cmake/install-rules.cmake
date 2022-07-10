install(
    TARGETS game-of-life-c_exe
    RUNTIME COMPONENT game-of-life_Runtime
)

install(
    TARGETS game-of-life-cpp_exe
    RUNTIME COMPONENT game-of-life_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
