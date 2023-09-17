#pragma once

#include <Card.h>

namespace Bang
{

class Player
{
public:
  Player() = default;

public:
  auto Character(Card *character) -> void
  { _character = character; }

  auto CurrentLife(uint32_t newCurrentLife) -> void
  { _currentLife = newCurrentLife; }

public:
  auto Character() const -> Card *
  { return _character; }

  auto CardsInHand() const -> const CardVector &
  { return _cardsInHand; }

  auto CardsOnTable() const -> const CardVector &
  { return _cardsOnTable; }

  auto CurrentLife() const -> uint32_t
  { return _currentLife; }

private:
  Card *_character = nullptr;
  CardVector _cardsInHand = {};
  CardVector _cardsOnTable = {};
  uint32_t _currentLife = 0u;
};

using PlayerVector = std::vector<std::shared_ptr<Player>>;

} // namespace Bang