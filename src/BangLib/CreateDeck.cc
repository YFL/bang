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

namespace
{

auto CreateCardTexture(
  const std::string_view &name,
  const std::unique_ptr<Bang::ContentStorageComponent> &contentStorageComponent,
  const std::unique_ptr<Utils::Renderer> &renderer) -> SDL_Texture *
{
  if (!renderer)
    throw Utils::Exception{ "No renderer available when generating a hand for a player." };

  const auto &fonts = Bang::Application::Get().contentStorageComponent->Fonts();
  if (fonts.empty())
    throw Utils::Exception{ "No fonts available when generating a hand for a player." };

  auto *font = fonts.cbegin()->second;
  if (!font)
    throw Utils::Exception{ "Null font found when generating a hand for a player." };
  if (auto *texture = contentStorageComponent->GetTexture(name.data()))
  {
    std::cerr << "Texture for card already exists: " << name << std::endl;
    return texture;
  }

  std::cerr << "Creating texture for card: " << name << std::endl;
  auto *texture = renderer->TextToTexture(font, name.data(), SDL_Color{255, 0, 0, 0});
  contentStorageComponent->AddTexture(name.data(), texture);

  return texture;
}

auto GeneratePlayCards() -> Bang::CardPointerVector
{
  const auto &contentStorageComponent = Bang::Application::Get().contentStorageComponent;
  const auto &renderer = Bang::Application::Get().renderingComponent->window->renderer;
  constexpr auto suite{ Bang::Suite::Diamond };
  constexpr auto cardNumber{ Bang::CardNumber::Ace };
  const auto name = std::format("PlayCard {} {}", ToString(suite), ToString(cardNumber));
  auto *texture = ::CreateCardTexture(name, contentStorageComponent, renderer);
  Bang::CardPointerVector playCards;
  for (auto i = 0u; i < 30; ++i)
    playCards.emplace_back(
      new Bang::PlayCard{ name, texture, cardNumber, suite });

  return playCards;
}

} // anon namespace

namespace Bang
{

auto CreateDeck::Update(GameState &gameState) -> bool
{
  auto &app = Bang::Application::Get();
  auto screen = std::static_pointer_cast<Graphics::Positionable>(app.renderingComponent->screen);
  const auto screenDrawArea = screen->GetAbsoluteDrawArea();
  const auto cardSize = app.configComponent->CardSize();
  const auto &cardBankComponent = Bang::Application::Get().cardBankComponent;
  const auto &contentStorageComponent = Bang::Application::Get().contentStorageComponent;
  const auto &renderer = Bang::Application::Get().renderingComponent->window->renderer;

  cardBankComponent->playCards = ::GeneratePlayCards();
  for (const auto &card : cardBankComponent->playCards)
    gameState.drawDeck->AddCard(card);

  gameState.drawDeck->Shuffle();
  gameState.drawDeck->Entity()->Get<Graphics::Positionable>()->SwitchParent(screen);
  gameState.drawDeck->Entity()->Get<Graphics::Positionable>()->SetPosition(
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
    });
  auto *mouse = &Application::Get().inputComponent->mouse;
  dynamic_cast<Utils::IEventEmitter<Utils::MouseMovementEvent> *>(mouse)
    ->RegisterHandler(gameState.drawDeck);
  dynamic_cast<Utils::IEventEmitter<Utils::MouseButtonEvent> *>(mouse)
    ->RegisterHandler(gameState.drawDeck);
  return false;
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