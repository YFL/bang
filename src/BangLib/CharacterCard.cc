#include <CharacterCard.h>

#include <Application.h>

namespace Bang
{

CharacterCard::CharacterCard(
  const std::string &name,
  const std::string &description,
  SDL_Texture *texture,
  const uint32_t maxLives)
  : Card {name, texture, Application::Get().configComponent->CardSize()}
{
  Entity()->AddComponent<CharacterCardComponent>(description, maxLives);
}

} // namespace Bang