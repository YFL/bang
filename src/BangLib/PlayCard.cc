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
  Utils::ComponentPointer playCardComponent = std::make_shared<PlayCardComponent>(
    Entity(),
    cardNumber,
    suite);
  Entity()->AddComponent<PlayCardComponent>(playCardComponent);
}

} // namespace Bang