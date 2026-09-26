#pragma once

#include <Deck.h>
#include <Player.h>

namespace Bang
{

struct GameState
{
  PlayerPointerVector players = {};
  DeckPointer drawDeck = std::make_shared<Deck>();
  DeckPointer throwAwayDeck = std::make_shared<Deck>();
  size_t currentPlayer = {};
};

auto CardsOnTheTable(const GameState &gameState) -> const std::vector<const CardWeakPtrVector *>;
auto CardsInAllHands(const GameState &gameState) -> const std::vector<const CardWeakPtrVector *>;

} // namespace Bang