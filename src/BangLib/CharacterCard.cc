#include <CharacterCard.h>

namespace Bang
{

CharacterCard::CharacterCard(
  const std::string &name,
  SDL_Texture *texture,
  const Bang::Suit suit,
  const CardNumber cardNumber,
  const uint32_t maxLives)
  : Card {name, texture, suit, cardNumber}
  , _maxLives {maxLives}
{

}

} // namespace Bang