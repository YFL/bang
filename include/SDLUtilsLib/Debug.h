#pragma once

#include <Renderer.h>

namespace Utils
{

auto DrawDebugRect(
  const std::unique_ptr<Renderer> &renderer,
  const SDL_Rect &rect,
  const SDL_Color &color) -> void;

} // namespace Utils`