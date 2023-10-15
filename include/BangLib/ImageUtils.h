#pragma once

#include <SDL2/SDL.h>

#include <string>

namespace Bang
{

auto LoadTextureFromJpg(SDL_Renderer *renderer, const std::string &pathToImage) -> SDL_Texture *;

} // namespace Bang