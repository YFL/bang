#include <PlayPhase.h>

#include <DropPhase.h>

#include <iostream>

namespace Bang
{

auto PlayPhase::Update(GameState &gameState) -> bool
{
  std::cerr << "PlayPhase" << std::endl;
  return false;
}

template<>
auto GetNextState<GameStates, GameStates::PlayPhase>(
  const StatePointer<GameStates> &currentState,
  const GameState &gameState)
  -> StatePointer<GameStates>
{
  return StatePointer<GameStates> {new DropPhase};
}

} // namespace Bang