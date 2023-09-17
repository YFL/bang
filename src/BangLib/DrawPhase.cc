#include <DrawPhase.h>

#include <iostream>

namespace Bang
{

auto DrawPhase::Update(GameState &gameState) -> bool
{
  std::cerr << "DrawPhase" << std::endl;
  return false;
}

} // namespace Bang