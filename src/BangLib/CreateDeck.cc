#include <CreateDeck.h>

#include <Application.h>
#include <CardNumber.h>
#include <CreatePlayers.h>
#include <PlayCard.h>
#include <Suite.h>

#include <CardCollapsingContainer.h>

#include <Exception.h>

#include <algorithm>
#include <random>

namespace Bang
{

auto CreateDeck::Update(GameState &gameState) -> bool
{
  auto &app = Bang::Application::Get();
  auto screen = std::static_pointer_cast<Graphics::Positionable>(app.renderingComponent->screen);
  const auto screenDrawArea = screen->GetAbsoluteDrawArea();
  const auto cardSize = app.configComponent->CardSize();
  auto cardCollapsingContainer = std::make_shared<Graphics::CardCollapsingContainer>(
    screen,
    Utils::DrawArea
    {
      {
        static_cast<int32_t>(
          screenDrawArea.size.x
          * Utils::ConvertLengthUnit(screenDrawArea.size.unit, Utils::LengthUnits::px)
          - cardSize.x
          * Utils::ConvertLengthUnit(cardSize.unit, Utils::LengthUnits::px)),
        static_cast<int32_t>(
          screenDrawArea.size.y / 2
          * Utils::ConvertLengthUnit(screenDrawArea.size.unit, Utils::LengthUnits::px)
          - cardSize.y / 2
          * Utils::ConvertLengthUnit(cardSize.unit, Utils::LengthUnits::px)),
        0
      },
      {
        static_cast<int32_t>(
          cardSize.x * Utils::ConvertLengthUnit(cardSize.unit, Utils::LengthUnits::px)),
        static_cast<int32_t>(
          cardSize.y * Utils::ConvertLengthUnit(cardSize.unit, Utils::LengthUnits::px)),
        Utils::LengthUnits::px
      }
    });

  const auto &contentStorageComponent = Bang::Application::Get().contentStorageComponent;
  const auto &cardBankComponent = Bang::Application::Get().cardBankComponent;
  const auto &renderer = Bang::Application::Get().renderingComponent->window->renderer;
  if (!renderer)
    throw Utils::Exception{ "No renderer available when generating a hand for a player." };

  const auto &fonts = Bang::Application::Get().contentStorageComponent->Fonts();
  if (fonts.empty())
    throw Utils::Exception{ "No fonts available when generating a hand for a player." };

  auto *font = fonts.cbegin()->second;
  if (!font)
    throw Utils::Exception{ "Null font found when generating a hand for a player." };

  constexpr auto suit{ Bang::Suite::Diamond };
  constexpr auto cardNumber{ Bang::CardNumber::Ace };
  const auto name = std::format("PlayCard {} {}", ToString(suit), ToString(cardNumber));
  // TODO: Check if the texture already exists in the content storage before creating it.
  auto *texture = renderer->TextToTexture(font, name, SDL_Color{ 255, 0, 0, 0 });
  contentStorageComponent->AddTexture(name, texture);

  for (auto i = 0u; i < 20; ++i)
    cardBankComponent->playCards.emplace_back(
      new Bang::PlayCard{ name, texture, cardNumber, suit });

  std::copy(cardBankComponent->playCards.begin(),
    cardBankComponent->playCards.end(),
    std::back_inserter(gameState.drawDeck));

  std::shuffle(
    gameState.drawDeck.begin(),
    gameState.drawDeck.end(),
    std::mt19937{ std::random_device{}() });

  for (const auto &cardWeakPtr : gameState.drawDeck)
  {
    const auto card = cardWeakPtr.lock();
    if (!card)
      std::cerr << "Card weak pointer is expired." << std::endl;
    auto cardCollapsingContainerPositionable =
      std::static_pointer_cast<Graphics::Positionable>(cardCollapsingContainer);
    card->Entity()->Get<Graphics::Positionable>()
      ->SwitchParent(cardCollapsingContainerPositionable);
  }

  cardCollapsingContainer->SwitchParent(screen);
}

template<>
auto GetNextState<GameStates, GameStates::CreateDeck>(
  const StatePointer<GameStates> &currentState,
  const GameState &gameState)
  -> StatePointer<GameStates>
{
  return StatePointer<GameStates> {new CreatePlayers};
}

} // namespace Bang