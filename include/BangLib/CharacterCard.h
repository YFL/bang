#pragma once

#include <Card.h>

#include <cstdint>

namespace Bang
{

class CharacterCard
  : public Card
{
public:
  CharacterCard(const std::string &name, SDL_Texture *texture, const Bang::Suit suit, const CardNumber cardNumber, const uint32_t maxLives);

private:
  uint32_t _maxLives = {};
};

} // namespace Bang