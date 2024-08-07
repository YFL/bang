#include <GameState.h>

#include <numeric>

namespace Bang
{

auto CardsOnTheTable(const GameState &gameState) -> const std::vector<const CardPointerVector *>
{
  return std::accumulate(
    gameState.players.cbegin(),
    gameState.players.cend(),
    std::vector<const CardPointerVector *> {},
    [](
      std::vector<const CardPointerVector *> cardsOnTheTable,
      const PlayerPointer &player)
      {
        cardsOnTheTable.emplace_back(&player->CardsOnTable());
        return cardsOnTheTable;
      });
}

auto CardsInAllHands(const GameState &gameState) -> const std::vector<const CardPointerVector *>
{
  return std::accumulate(
    gameState.players.cbegin(),
    gameState.players.cend(),
    std::vector<const CardPointerVector *> {},
    [](
      std::vector<const CardPointerVector *> cardsInAllHands,
      const PlayerPointer &player)
      {
        cardsInAllHands.emplace_back(&player->CardsInHand());
        return cardsInAllHands;
      });
}

} // namespace Bang