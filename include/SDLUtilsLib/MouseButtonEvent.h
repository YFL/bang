#pragma once

#include <Position.h>

namespace Utils
{

struct MouseButtonEvent
{
  uint8_t button;
  bool down;
  uint8_t clicks;
  Position position;
};

} // namespace Utils