#pragma once

#include <LengthUnits.h>

#include <cstdint>

namespace Utils
{

/**
 Size in 2 dimensions [cm].
*/
struct TwoDSize
{
  int32_t x;
  int32_t y;
  LengthUnits unit;
};

inline auto operator==(const TwoDSize& l, const TwoDSize& r) -> bool
{
  auto converter = l.unit == r.unit ? 1 : Utils::ConvertLengthUnit(l.unit, r.unit);
  return l.x * converter == r.x && l.y * converter == r.y;
}

} // namespace Utils