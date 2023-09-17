#include <GameState.h>

#include <numeric>

namespace Bang
{

auto CardsOnTheTable(const GameState &gameState) -> const std::vector<const CardVector *>
{
  return std::accumulate(
    gameState.players.cbegin(),
    gameState.players.cend(),
    std::vector<const CardVector *> {}, [](std::vector<const CardVector *> cardsOnTheTable, const std::shared_ptr<Player> &player)
      {
        cardsOnTheTable.emplace_back(&player->CardsOnTable());
        return cardsOnTheTable;
      });
}

auto CardsInAllHands(const GameState &gameState) -> const std::vector<const CardVector *>
{
  return std::accumulate(
    gameState.players.cbegin(),
    gameState.players.cend(),
    std::vector<const CardVector *> {},
    [](std::vector<const CardVector *> &cardsInAllHands, const std::shared_ptr<Player> &player)
      {
        cardsInAllHands.emplace_back(&player->CardsInHand());
        return cardsInAllHands;
      });
}

} // namespace Bang