#pragma once

#include <CardNumber.h>
#include <Suit.h>

#include <string>
#include <vector>
#include <memory>

struct SDL_Texture;

namespace Bang
{

class Card
{
public:
  Card(const std::string &name, SDL_Texture *texture, const Bang::Suit suit, const CardNumber cardNumber);

public:
  operator std::string () const
  { return _name; }

public:
  auto Name() const -> const std::string &
  { return _name; }

  auto Texture() const -> SDL_Texture *
  { return _texture; }

  auto Suit() const -> Suit
  { return _suit; }

  auto Number() const -> CardNumber
  { return _number; }

  auto ToString() const -> std::string
  {
    return _name + " " + Bang::ToString(_suit) + " " + Bang::ToString(_number);
  }

private:
  const std::string _name = "";
  SDL_Texture *_texture = nullptr;
  Bang::Suit _suit = Suit::NumberOfSuits;
  CardNumber _number = CardNumber::NumberOfCardNumbers;
};

using CardPointer = std::shared_ptr<Card>;
using CardPointerVector = std::vector<CardPointer>;

} // namespace Bang