#include <PlayPhase.h>

#include <DropPhase.h>

#include <iostream>

namespace Bang
{

auto PlayPhase::Update(GameState &gameState) -> bool
{
  std::cerr << "PlayPhase of player #" << gameState.currentPlayer << std::endl;
  // We don't wanna go to the next state, we want to stay in this one, until the player has
  // finished their turn.
  const auto finishTurn = false;
  return !finishTurn;
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