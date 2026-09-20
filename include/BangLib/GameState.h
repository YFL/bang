#pragma once

#include <Player.h>

namespace Bang
{

struct GameState
{
  PlayerPointerVector players;
  CardWeakPtrVector drawDeck;
  CardWeakPtrVector throwAwayDeck;
  size_t currentPlayer;
};

auto CardsOnTheTable(const GameState &gameState) -> const std::vector<const CardWeakPtrVector *>;
auto CardsInAllHands(const GameState &gameState) -> const std::vector<const CardWeakPtrVector *>;

} // namespace Bang