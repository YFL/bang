#include <SwitchPlayers.h>

#include <DrawPhase.h>

#include <iostream>

namespace Bang
{

auto SwitchPlayers::Update(GameState &gameState) -> bool
{
  std::cerr << "SwitchPlayers" << std::endl;
  return false;
}

template<>
auto GetNextState<GameStates, GameStates::SwitchPlayers>(const StatePointer<GameStates> &currentState, const GameState &gameState) -> StatePointer<GameStates>
{
  return StatePointer<GameStates> {new DrawPhase};
}

} // namespace Bang