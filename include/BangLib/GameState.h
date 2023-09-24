#pragma once

#include <Player.h>

namespace Bang
{

struct GameState
{
  PlayerPointerVector players;
  CardPointerVector drawDeck;
  CardPointerVector throwAwayDeck;
  size_t currentPlayer;
};

auto CardsOnTheTable(const GameState &gameState) -> const std::vector<const CardPointerVector *>;
auto CardsInAllHands(const GameState &gameState) -> const std::vector<const CardPointerVector *>;

} // namespace Bang