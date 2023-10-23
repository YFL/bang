#include "BangLib/DropPhase.h"

#include "BangLib/SwitchPlayers.h"

#include <iostream>

namespace Bang
{

auto DropPhase::Update(GameState &gameState) -> bool
{
  std::cerr << "DropPhase" << std::endl;
  return false;
}

template<>
auto GetNextState<GameStates, GameStates::DropPhase>(const StatePointer<GameStates> &currentState, const GameState& gameState) -> StatePointer<GameStates>
{
  return StatePointer<GameStates> {new SwitchPlayers};
}

} // namespace Bang