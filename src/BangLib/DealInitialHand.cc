#include <DealInitialHand.h>

#include <Application.h>
#include <Exception.h>
#include <GameState.h>
#include <PlayPhase.h>

#include <iostream>

namespace
{

auto GenerateHandForPlayer(const Bang::PlayerPointer &player) -> void
{
  const auto &contentStorageComponent = Bang::Application::Get().contentStorageComponent;
  const auto &renderer = Bang::Application::Get().renderingComponent->window->renderer;
  if(!renderer)
    throw Bang::Exception {"No renderer available when generating a hand for a player."};
  
  const auto &fonts = Bang::Application::Get().contentStorageComponent->Fonts();
  if(fonts.empty())
    throw Bang::Exception {"No fonts available when generating a hand for a player."};
  
  auto *font = fonts.cbegin()->second;
  if(!font)
    throw Bang::Exception {"Null font found when generating a hand for a player."};

  constexpr auto suit {Bang::Suit::Diamond};
  constexpr auto cardNumber {Bang::CardNumber::Ace};
  const auto name = std::string("PlayCard ") + Bang::ToString(suit) + " " + Bang::ToString(cardNumber);
  auto *texture = renderer->TextToTexture(font, name, SDL_Color {255, 0, 0, 0});
  contentStorageComponent->AddTexture(name, texture);
  player->CardsInHand(Bang::CardPointerVector {std::make_shared<Bang::Card>("PlayCard", texture, suit, cardNumber)});
}

} // namespace 

namespace Bang
{

auto DealInitialHand::Update(GameState &gameState) -> bool
{
  std::cerr << "DealInitialHand" << std::endl;
  for(const auto &player : gameState.players)
  {
    GenerateHandForPlayer(player);
  }

  return false;
}

template<>
auto GetNextState<GameStates, GameStates::DealInitialHand>(const StatePointer<GameStates> &currentState, const GameState &gameState) -> StatePointer<GameStates>
{
  return StatePointer<GameStates> {new PlayPhase};
}

} // namespace Bang