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

template<typename NumericType>
inline auto operator*(const TwoDSize &l, const NumericType n) -> TwoDSize
{
  if constexpr (!std::is_same_v<NumericType, int32_t> && !std::is_same_v<NumericType, uint32_t>
    && !std::is_same_v<NumericType, int64_t> && !std::is_same_v<NumericType, uint64_t>
    && !std::is_same_v<NumericType, float> && !std::is_same_v<NumericType, double>)
    static_assert(false, "Unexpected type of n");

  auto newSize = l;
  newSize.x *= n;
  newSize.y *= n;

  return newSize;
}

} // namespace Utils