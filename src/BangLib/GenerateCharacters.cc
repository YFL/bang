#include <GenerateCharacters.h>

#include <Application.h>
#include <Exception.h>
#include <DealInitialHand.h>
#include <GameState.h>

#include <iostream>

namespace
{

auto GenerateCharacterForPlayer(const Bang::PlayerPointer &player) -> void
{
  const auto &renderer = Bang::Application::Get().renderingComponent->window->renderer;
  if(!renderer)
    throw Bang::Exception {"Renderer not available when generating a character to a player."};

  const auto &fonts = Bang::Application::Get().contentStorageComponent->Fonts();
  if(fonts.empty())
    throw Bang::Exception {"No foint available"};

  constexpr auto suit {Bang::Suit::Spade};
  constexpr auto cardNumber {Bang::CardNumber::Ace};
  const std::string name {std::string {"Character "} + Bang::ToString(suit) + " " + Bang::ToString(cardNumber)};

  auto *font = fonts.cbegin()->second;
  if(!font)
    throw Bang::Exception {"Null font found when generating a character to a player."};
  
  auto *texture = renderer->TextToTexture(font, name, {255, 0, 0, 0});

  player->Character(new Bang::Card {name, texture, suit, cardNumber});
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