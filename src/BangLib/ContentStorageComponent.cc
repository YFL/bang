#include "BangLib/ContentStorageComponent.h"

#include <iostream>

namespace Bang
{

ContentStorageComponent::~ContentStorageComponent()
{
  static auto counter = 0;

  std::cout << "Called " << counter++ << " times." << std::endl;
  std::cout << "Destructing ContentStorageComponent." << std::endl;

  std::cout << "Textures size: " << _textures.size() << std::endl;
  for(auto &[_, texture] : _textures)
  {
    std::cout << "Closing texture " << _ << " " << texture << std::endl;
    SDL_DestroyTexture(texture);
    texture = nullptr;
  }

  std::cout << "Fonts size: " << _fonts.size() << std::endl;
  for(auto &[_, font] : _fonts)
  {
    std::cout << "Closing font " << _ << " " << font << std::endl;
    TTF_CloseFont(font);
    font = nullptr;
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