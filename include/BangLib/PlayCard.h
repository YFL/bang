#pragma once

#include <Card.h>
#include <CardNumber.h>
#include <Suit.h>

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