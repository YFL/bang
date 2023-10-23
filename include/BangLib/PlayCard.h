#pragma once

#include "BangLib/Card.h"
#include "BangLib/CardNumber.h"
#include "BangLib/Suit.h"

namespace Bang
{

class PlayCard : public Card
{
public:
  PlayCard(const std::string &name, SDL_Texture *texture, const Bang::CardNumber cardNumber, const Suit suit);

public:
  auto CardNumber() const -> Bang::CardNumber
  { return cardNumber; }

  auto Suit() const -> Bang::Suit
  { return suit; }

private:
  const Bang::CardNumber cardNumber;
  const Bang::Suit suit;
};

} // namespace Bang