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

  auto CardsInHand(const CardPointerVector &cards) -> void
  { _cardsInHand = cards; }

  auto CurrentLife(uint32_t newCurrentLife) -> void
  { _currentLife = newCurrentLife; }

public:
  auto Character() const -> CardPointer
  { return _character; }

  auto CardsInHand() const -> const CardPointerVector &
  { return _cardsInHand; }

  auto CardsOnTable() const -> const CardPointerVector &
  { return _cardsOnTable; }

  auto CurrentLife() const -> uint32_t
  { return _currentLife; }

private:
  CardPointer _character = nullptr;
  CardPointerVector _cardsInHand = {};
  CardPointerVector _cardsOnTable = {};
  uint32_t _currentLife = 0u;
};

using PlayerPointer = std::shared_ptr<Player>;
using PlayerPointerVector = std::vector<PlayerPointer>;

} // namespace Bang