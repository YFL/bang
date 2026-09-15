#include <GenerateCharacters.h>

#include <Application.h>
#include <DealInitialHand.h>
#include <Exception.h>
#include <GameState.h>

#include <iostream>

namespace
{

auto GenerateCharacterForPlayer(const Bang::PlayerPointer &player) -> void
{
  const auto &characterCards = Bang::Application::Get().cardBankComponent->characterCards;
  std::cout << "characterCards number: " << characterCards.size() << std::endl;
  player->Character(characterCards[0]);
}

auto AddCharacterToScreen(
  const Bang::PlayerPointer &player,
  const Utils::DrawArea &playerPosition,
  std::shared_ptr<Graphics::Screen> &screen) -> void
{
  auto character = player->Character();
  if (!character)
  {
    std::cerr << "No character available." << std::endl;
    return;
  }

  const auto &characterPositionable = character->Entity()->Get<Graphics::Positionable>();
  const auto cardSize = Bang::Application::Get().configComponent->CardSize();
  const auto converter = Utils::ConvertLengthUnit(cardSize.unit, Utils::LengthUnits::px);

  std::cerr << "Setting character position to x: " << playerPosition.position.x << " y: " << playerPosition.position.y - cardSize.y * converter << std::endl;
  characterPositionable->SetPosition({
      playerPosition.position.x,
      playerPosition.position.y - cardSize.y * converter
    });

  screen->AddChild(characterPositionable);
}

} // namespace

namespace Bang
{

auto GenerateCharacters::Update(GameState &gameState) -> bool
{
  std::cerr << "GenerateCharacters" << std::endl;
  const auto playerPositions = Bang::Application::Get().configComponent->PlayerPositions();
  for(auto i = 0u; i < gameState.players.size(); ++i)
  {
    const auto player = gameState.players[i];
    std::cerr << "Generating a character for a player." << std::endl;
    ::GenerateCharacterForPlayer(player);
    std::cerr << "Character generated." << std::endl;
    std::cerr << "Adding generated character to screen" << std::endl;
    ::AddCharacterToScreen(
      player,
      playerPositions[i >= playerPositions.size() ? i % playerPositions.size() : i],
      Bang::Application::Get().renderingComponent->screen);
    std::cerr << "character added to screen" << std::endl;
  }

  std::cerr << "Character generation done." << std::endl;

  return false;
}

template<>
auto GetNextState<GameStates, GameStates::GenerateCharacters>(
  const StatePointer<GameStates> &currentState,
  const GameState &gameState)
  -> StatePointer<GameStates>
{
  return StatePointer<GameStates> {new DealInitialHand};
}

} // namespace Bang