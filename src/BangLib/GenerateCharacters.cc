#include "BangLib/GenerateCharacters.h"

#include "BangLib/Application.h"
#include "BangLib/DealInitialHand.h"
#include "BangLib/Exception.h"
#include "BangLib/GameState.h"

#include <iostream>

namespace
{

auto GenerateCharacterForPlayer(const Bang::PlayerPointer &player) -> void
{
  const auto &renderer = Bang::Application::Get().renderingComponent->window->renderer;
  if(!renderer)
    throw Bang::Exception {"Renderer not available when generating a character to a player."};

  const auto &characterCards = Bang::Application::Get().cardBankComponent->characterCards;
  std::cout << "characterCards number: " << characterCards.size() << std::endl;
  player->Character(characterCards[0].get());
}

} // namespace 

namespace Bang
{

auto GenerateCharacters::Update(GameState &gameState) -> bool
{
  std::cerr << "GenerateCharacters" << std::endl;

  for(const auto &player : gameState.players)
  {
    std::cerr << "Generating a character for a player." << std::endl;
    GenerateCharacterForPlayer(player);
    std::cerr << "Character generated." << std::endl;
  }

  std::cerr << "Character generation done." << std::endl;

  return false;
}

template<>
auto GetNextState<GameStates, GameStates::GenerateCharacters>(const StatePointer<GameStates> &currentState, const GameState &gameState) -> StatePointer<GameStates>
{
  return StatePointer<GameStates> {new DealInitialHand};
}

} // namespace Bang