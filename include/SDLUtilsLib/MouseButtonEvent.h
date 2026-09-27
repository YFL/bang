#pragma once

#include <Position.h>

#include <SDL.h>

namespace Utils
{

static constexpr auto mouseLeftButton = SDL_BUTTON_LEFT;
static constexpr auto mouseMiddleButton = SDL_BUTTON_MIDDLE;
static constexpr auto mouseRightButton = SDL_BUTTON_RIGHT;

struct MouseButtonEvent
{
  uint8_t button;
  bool down;
  uint8_t clicks;
  Position position;
};

} // namespace Utils