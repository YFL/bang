#include <Card.h>

#include <Application.h>
#include <Exception.h>

#include <Positionable.h>

namespace Bang
{

Card::Card(const std::string &name, SDL_Texture *texture, const Utils::TwoDSize &cardSize)
  : _name {name}
  , _texture {texture}
  , _entity { std::make_shared<Utils::Entity>() }
{
  if(!texture)
    throw Utils::Exception {"Invalid texture"};

  if(name.empty())
    throw Utils::Exception {"Invalid name"};

  Utils::ComponentPointer positionable = std::make_shared<Graphics::Positionable>(
    _entity,
    nullptr,
    Utils::DrawArea{{0, 0, 0}, cardSize});
  _entity->AddComponent<Graphics::Positionable>(positionable);
}

} // namespace Bang
