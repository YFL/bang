#include <DrawArea.h>

#include <format>

namespace Graphics
{

auto DoDrawAreasCollide(const DrawArea &a, const DrawArea &b, bool includeZ) -> bool
{
  if (includeZ)
    if (a.position.z != b.position.z)
      return false;
    
  return !(a.position.x + a.w < b.position.x
    || a.position.x > b.position.x + b.w
    || a.position.y + a.h < b.position.y
    || a.position.y > b.position.y + b.h);
}

inline auto DoesDrawAreaFitAnother(const DrawArea &fits, const DrawArea &toFit) -> bool
{
  return fits.position.x >= toFit.position.x
    && fits.position.x + fits.w <= toFit.position.x + toFit.w
    && fits.position.y >= toFit.position.y
    && fits.position.y + fits.h <= toFit.position.y + toFit.h;
}

inline auto IsPointInDrawArea(const DrawArea &area, const Position &point, bool includeZ) -> bool
{
  if(includeZ && area.position.z != point.z)
    return false;

  return area.position.x <= point.x
    && area.position.x + area.w >= point.x
    && area.position.y <= point.y
    && area.position.y + area.h >= point.y;
}

auto ToString(const DrawArea& drawArea) -> std::string
{
  return std::format(
    "DrawArea: x: {} y: {} z: {} widht: {} height: {}",
    drawArea.position.x,
    drawArea.position.y,
    drawArea.position.z,
    drawArea.w,
    drawArea.h);
}

} // namespace Graphics