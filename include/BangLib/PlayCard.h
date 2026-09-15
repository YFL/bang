#pragma once

#include <Card.h>
#include <CardNumber.h>
#include <Suite.h>

namespace Bang
{

class PlayCardComponent : public Utils::Component
{
public:
  PlayCardComponent(
    const Utils::EntityPointer &parent,
    const Bang::CardNumber cardNumber,
    const Bang::Suite suite)
    : Component { parent }
    , _cardNumber { cardNumber }
    , _suite { suite }
  {

  }

public:
  auto CardNumber() const -> Bang::CardNumber
  {
    return _cardNumber;
  }

  auto Suite() const -> Bang::Suite
  {
    return _suite;
  }

private:
  const Bang::CardNumber _cardNumber;
  const Bang::Suite _suite;
};

class PlayCard : public Card
{
public:
  PlayCard(
    const std::string &name,
    SDL_Texture *texture,
    const Bang::CardNumber cardNumber,
    const Suite suite);
};

} // namespace Bang