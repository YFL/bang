#include "BangLib/Card.h"

#include "BangLib/Exception.h"

namespace Bang
{

Card::Card(const std::string &name, SDL_Texture *texture)
  : _name {name}
  , _texture {texture}
{
  if(!texture)
    throw Exception {"Invalid texture"};
  
  if(name.empty())
    throw Exception {"Invalid name"};
}

} // namespace Bang