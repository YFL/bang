#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <string>

namespace Bang
{

auto LoadFontFromFile(const std::string &pathToFIle, const uint32_t fontSize) -> TTF_Font *;
auto TextToTexture(TTF_Font *font, SDL_Renderer* renderer, const std::string &text, const SDL_Color &color) -> SDL_Texture *;

} // namespace Bang