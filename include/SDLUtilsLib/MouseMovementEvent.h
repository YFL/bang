#pragma once

#include <Position.h>

namespace Utils
{

struct MouseMovementEvent
{
  Position newPos;
  Position relativePos;
};

} // namespace Utils