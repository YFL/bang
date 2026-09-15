#include <PlayCard.h>

#include <Application.h>

namespace Bang
{

PlayCard::PlayCard(
  const std::string &name,
  SDL_Texture *texture,
  const Bang::CardNumber cardNumber,
  const Bang::Suite suite)
  : Card{ name, texture, Application::Get().configComponent->CardSize()}
{
  Entity()->AddComponent<PlayCardComponent>(cardNumber, suite);
}

} // namespace Bang