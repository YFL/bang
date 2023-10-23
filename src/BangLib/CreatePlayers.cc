#include "BangLib/CreatePlayers.h"

#include "BangLib/GameState.h"
#include "BangLib/GenerateCharacters.h"

#include <iostream>

namespace Bang
{

auto CreatePlayers::Update(GameState &gameState) -> bool
{
  std::cerr << "CreatePlayers" << std::endl;
  constexpr auto NumberOfPlayers = 2u;

  for(auto i = 0u; i < NumberOfPlayers; ++i)
  {
    std::cerr << "Creating player #" << i << '.' << std::endl;
    gameState.players.emplace_back(new Player {});
    std::cerr << "Player #" << i << " created. " << std::endl;
  }

  std::cerr << "Players created." << std::endl;
  return false;
}

template<>
auto GetNextState<GameStates, GameStates::CreatePlayers>(const StatePointer<GameStates> &currentState, const GameState &gameState) -> StatePointer<GameStates>
{
  return StatePointer<GameStates> {new GenerateCharacters};
}

} // namespace Bang