#include <DropPhase.h>

#include <iostream>

namespace Bang
{

auto DropPhase::Update(GameState &gameState) -> bool
{
  std::cerr << "DropPhase" << std::endl;
  return false;
}

} // namespace Bang