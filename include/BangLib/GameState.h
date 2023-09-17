#pragma once

#include <Player.h>

namespace Bang
{

struct GameState
{
  PlayerVector players;
  CardVector drawDeck;
  CardVector throwAwayDeck;
  size_t currentPlayer;
};

auto CardsOnTheTable(const GameState &gameState) -> const std::vector<const CardVector *>;
auto CardsInAllHands(const GameState &gameState) -> const std::vector<const CardVector *>;

} // namespace Bang