#include <Card.h>

#include <Exception.h>

namespace Bang
{

Card::Card(const std::string &name, SDL_Texture *texture, const Bang::Suit suit, const CardNumber cardNumber)
  : _name {name}
  , _texture {texture}
  , _suit {suit}
  , _number {cardNumber}
{
  if(cardNumber == CardNumber::NumberOfCardNumbers)
    throw Exception {"Invalid card number"};
  
  if(_suit >= Bang::Suit::NumberOfSuits)
    throw Exception {"Invalid suit"};

  if(!texture)
    throw Exception {"Invalid texture"};
  
  if(name.empty())
    throw Exception {"Invalid name"};
}

} // namespace Bang