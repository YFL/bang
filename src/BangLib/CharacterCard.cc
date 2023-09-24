#include <CharacterCard.h>

namespace Bang
{

CharacterCard::CharacterCard(
  const std::string &name,
  const std::string &description,
  SDL_Texture *texture,
  const uint32_t maxLives)
  : Card {name, texture}
  , _description(description)
  , _maxLives {maxLives}
{

}

} // namespace Bang