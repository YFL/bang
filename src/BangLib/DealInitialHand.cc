#include <DealInitialHand.h>

#include <Application.h>
#include <Exception.h>
#include <GameState.h>
#include <PlayCard.h>
#include <PlayPhase.h>

#include <format>

#include <iostream>

namespace
{

auto GenerateHandForPlayer(const Bang::PlayerPointer &player) -> void
{
  const auto &contentStorageComponent = Bang::Application::Get().contentStorageComponent;
  const auto &renderer = Bang::Application::Get().renderingComponent->window->renderer;
  if(!renderer)
    throw Utils::Exception {"No renderer available when generating a hand for a player."};

  const auto &fonts = Bang::Application::Get().contentStorageComponent->Fonts();
  if(fonts.empty())
    throw Utils::Exception {"No fonts available when generating a hand for a player."};

  auto *font = fonts.cbegin()->second;
  if(!font)
    throw Utils::Exception {"Null font found when generating a hand for a player."};

  constexpr auto suit {Bang::Suit::Diamond};
  constexpr auto cardNumber {Bang::CardNumber::Ace};
  const auto name = std::format("PlayCard {} {}", ToString(suit), ToString(cardNumber));
  // TODO: Check if the texture already exists in the content storage before creating it.
  auto *texture = renderer->TextToTexture(font, name, SDL_Color {255, 0, 0, 0});
  contentStorageComponent->AddTexture(name, texture);
  Bang::CardPointerVector cards;
  for (auto i = 0u; i < 10; ++i)
    cards.emplace_back(new Bang::PlayCard { "PlayCard", texture, cardNumber, suit });

  player->CardsInHand(cards);
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
auto GetNextState<GameStates, GameStates::DealInitialHand>(
  const StatePointer<GameStates> &currentState,
  const GameState &gameState)
  -> StatePointer<GameStates>
{
  return StatePointer<GameStates> {new PlayPhase};
}

} // namespace Bang