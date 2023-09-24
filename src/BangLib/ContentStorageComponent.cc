#include <ContentStorageComponent.h>

#include <iostream>

namespace Bang
{

ContentStorageComponent::~ContentStorageComponent()
{
  for(auto &pair : _fonts)
  {
    TTF_CloseFont(pair.second);
    pair.second = nullptr;
  }

  for(auto &pair : _textures)
  {
    SDL_DestroyTexture(pair.second);
    pair.second = nullptr;
  }
}

auto ContentStorageComponent::GetFont(const std::string &name) const -> TTF_Font *
{
  const auto it = _fonts.find(name);
  if(it == _fonts.cend())
  {
    std::cerr << "Couldn't find font with name \"" << name << "\"." << std::endl;
    return nullptr;
  }

  return it->second;
}

auto ContentStorageComponent::GetTexture(const std::string &name) const -> SDL_Texture *
{
  const auto it = _textures.find(name);
  if(it == _textures.cend())
  {
    std::cerr << "Couldn't find texture with name \"" << name << "\". " << std::endl;
    return nullptr;
  }

  return it->second;
}

} // namespace Bang