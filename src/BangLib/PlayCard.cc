#include <PlayCard.h>

namespace Bang
{

PlayCard::PlayCard(
  const std::string &name,
  SDL_Texture *texture,
  const Bang::CardNumber cardNumber,
  const Bang::Suit suit)
  : Card {name, texture}
  , cardNumber {cardNumber}
  , suit {suit}
{
  
}

} // namespace Bang