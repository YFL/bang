#pragma once

#include <Card.h>

namespace Bang
{

class Player
{
public:
  Player() = default;

public:
  auto Character(const CardPointer &character) -> void
  { _character = character; }

  auto CardsInHand(const CardWeakPtrVector &cards) -> void
  { _cardsInHand = cards; }

  auto CurrentLife(uint32_t newCurrentLife) -> void
  { _currentLife = newCurrentLife; }

public:
  auto Character() const -> CardWeakPtr
  { return _character; }

  auto CardsInHand() const -> const CardWeakPtrVector &
  { return _cardsInHand; }

  auto CardsOnTable() const -> const CardWeakPtrVector &
  { return _cardsOnTable; }

  auto CurrentLife() const -> uint32_t
  { return _currentLife; }

private:
  CardWeakPtr _character = {};
  CardWeakPtrVector _cardsInHand = {};
  CardWeakPtrVector _cardsOnTable = {};
  uint32_t _currentLife = 0u;
};

using PlayerPointer = std::shared_ptr<Player>;
using PlayerPointerVector = std::vector<PlayerPointer>;

} // namespace Bang