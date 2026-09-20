#pragma once

#include <cstdint>
#include <cmath>

namespace Utils
{

enum class LengthUnits : int32_t
{
  mm = -1,
  cm = 0,
  dm = 1,
  m = 2,
  km = 5,
  px = 2
};

inline auto ConvertLengthUnit(LengthUnits from, LengthUnits to) -> float {
  if (from == to)
    return 1;
  const int32_t magnitude =
    std::powf(10, static_cast<int32_t>(from)) * std::powf(10, static_cast<int32_t>(to));
  return to > from ? 1.f / magnitude : magnitude;
}

} // namespace Utils