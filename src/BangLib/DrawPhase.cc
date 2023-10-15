#include <DrawPhase.h>

#include <PlayPhase.h>

#include <iostream>

namespace Bang
{

auto DrawPhase::Update(GameState &gameState) -> bool
{
  std::cerr << "DrawPhase" << std::endl;
  return false;
}

template<>
auto GetNextState<GameStates, GameStates::DrawPhase>(const StatePointer<GameStates> &currentState, const GameState &gameState) -> StatePointer<GameStates>
{
  return StatePointer<GameStates> {new PlayPhase};
}

} // namespace Bang