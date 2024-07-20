#pragma once

#include <cstdint>

namespace Utils
{

struct Position
{
  int32_t x;
  int32_t y;
  int32_t z;
};

inline auto operator== (const Position &a, const Position &b) -> bool
{ return a.x == b.x && a.y == b.y && a.z == b.z; }

} // namespace Utils