#include <ImageUtils.h>

#include <SDL_image.h>

#include <iostream>

namespace Bang
{

auto LoadTextureFromJpg(SDL_Renderer *renderer, const std::string &pathToFile) -> SDL_Texture *
{
  auto *surface = IMG_Load(pathToFile.c_str());
  if(!surface)
  {
    std::cerr << "Couldn't load image: " << IMG_GetError() << std::endl;
    return nullptr;
  }

  auto *texture = SDL_CreateTextureFromSurface(renderer, surface);
  if(!texture)
  {
    std::cerr << "Couldn't create texture: " << SDL_GetError() << std::endl;
    return nullptr;
  }

  return texture;
}

} // namespace Bang