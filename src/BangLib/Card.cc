#include <Card.h>

#include <Exception.h>

namespace Bang
{

Card::Card(const std::string &name, SDL_Texture *texture)
  : _name {name}
  , _texture {texture}
  , _positionable { nullptr, {}}
{
  if(!texture)
    throw Utils::Exception {"Invalid texture"};
  
  if(name.empty())
    throw Utils::Exception {"Invalid name"};
}

} // namespace Bang
