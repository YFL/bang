#include <PlayPhase.h>

#include <iostream>

namespace Bang
{

auto PlayPhase::Update(GameState &gameState) -> bool
{
  std::cerr << "PlayPhase" << std::endl;
  return false;
}

} // namespace Bang