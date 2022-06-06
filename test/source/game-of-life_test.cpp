#include "lib.hpp"

auto main() -> int
{
  auto const lib = library {};

  return lib.name == "game-of-life" ? 0 : 1;
}
