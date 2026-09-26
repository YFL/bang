#include <DealInitialHand.h>

#include <Application.h>
#include <CardCollapsingHoveredHighlightingContainer.h>
#include <Exception.h>
#include <GameState.h>
#include <PlayPhase.h>

#include <Positionable.h>

#include <format>
#include <iostream>

namespace
{

auto GenerateHandForPlayer(const Bang::PlayerPointer &player, Bang::GameState &gameState) -> void
{
  Bang::CardWeakPtrVector cards;
  for (auto i = 0u; i < 10; ++i)
    cards.emplace_back(gameState.drawDeck->GetCard());

  player->CardsInHand(cards);
}

auto AddHandsToScreen(const Bang::PlayerPointerVector &players) -> void
{
  if (players.empty()) return;
  const auto &app = Bang::Application::Get();
  const auto playerPositions = app.configComponent->PlayerPositions();
  const auto &screen = app.renderingComponent->screen;
  auto positionableScreen = std::static_pointer_cast<Graphics::Positionable>(screen);
  const auto cardSize = app.configComponent->CardSize();
  for (auto playerIndex = 0u; playerIndex < players.size(); ++playerIndex)
  {
    const auto &player = players[playerIndex];

    const auto &cardsInHand = player->CardsInHand();
    const auto playerPosition = playerPositions[playerIndex];

    std::cerr << "Player #" << playerIndex << " position: " << playerPosition.position.x << ", "
      << playerPosition.position.y << std::endl;

    const auto cardSize = app.configComponent->CardSize();
    const auto converter = Utils::ConvertLengthUnit(cardSize.unit, Utils::LengthUnits::px);
    const auto cardCollapsingContainerY = playerPosition.position.y;

    auto cardCollapsingContainer =
      std::make_shared<Graphics::CardCollapsingHoveredHighlightingContainer>(
        screen,
        Utils::DrawArea
        {
          {
            static_cast<int32_t>(app.configComponent->FirstCardToScreenLeftOffset()),
            static_cast<int32_t>(cardCollapsingContainerY),
            0
          },
          {
            static_cast<int32_t>(
            app.configComponent->MaxCardsNextToEachOtherWithoutOverlapping() * cardSize.x * converter),
            static_cast<int32_t>(cardSize.y),
            Utils::LengthUnits::px
          }
        });

    cardCollapsingContainer->SwitchParent(positionableScreen);
    dynamic_cast<Utils::IEventEmitter<Utils::MouseMovementEvent> *>(&app.inputComponent->mouse)
      ->RegisterHandler(cardCollapsingContainer);

    std::cerr << "Container draw area: " << Utils::ToString(cardCollapsingContainer->GetDrawArea()) << std::endl;
    for (const auto& cardWeakPtr : cardsInHand)
    {
      const auto card = cardWeakPtr.lock();
      auto containerPositionable =
        std::static_pointer_cast<Graphics::Positionable>(cardCollapsingContainer);
      card->Entity()->Get<Graphics::Positionable>()->SwitchParent(containerPositionable);
    }
  }
}

} // namespace

namespace Bang
{

auto DealInitialHand::Update(GameState &gameState) -> bool
{
  std::cerr << "DealInitialHand" << std::endl;
  for(const auto &player : gameState.players)
  {
    GenerateHandForPlayer(player, gameState);
  }

  AddHandsToScreen(gameState.players);

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
