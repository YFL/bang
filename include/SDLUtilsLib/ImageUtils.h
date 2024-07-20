#pragma once

#include <SDL.h>

#include <string>

namespace Utils
{

auto LoadTextureFromJpg(
  SDL_Renderer *renderer,
  const std::string &pathToImage) -> SDL_Texture *;

} // namespace Utils