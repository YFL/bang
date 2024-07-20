#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>
#include <string>

namespace Utils
{

auto LoadFontFromFile(const std::string &pathToFile, const uint32_t fontSize) -> TTF_Font *;
auto TextToTexture(
  TTF_Font *font,
  SDL_Renderer* renderer,
  const std::string &text,
  const SDL_Color &color) -> SDL_Texture *;

} // namespace Utils