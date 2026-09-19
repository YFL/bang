#include <DrawArea.h>

#include <format>
#include <iostream>

namespace Utils
{

auto DoDrawAreasCollide(const DrawArea &a, const DrawArea &b, bool includeZ) -> bool
{
  if (includeZ)
    if (a.position.z != b.position.z)
      return false;
  DrawArea newA { a }, newB { b };
  if (a.size.unit != Utils::LengthUnits::px)
  {
    const auto conversion = Utils::ConvertLengthUnit(a.size.unit, Utils::LengthUnits::px);
    newA.size = {
      static_cast<int32_t>(a.size.x * conversion),
      static_cast<int32_t>(a.size.y * conversion)
    };
  }

  if (b.size.unit != Utils::LengthUnits::px)
  {
    const auto conversion = Utils::ConvertLengthUnit(b.size.unit, Utils::LengthUnits::px);
    newB.size = {
      static_cast<int32_t>(b.size.x * conversion),
      static_cast<int32_t>(b.size.y * conversion)
    };
  }

  return !(newA.position.x + newA.size.x < newB.position.x
    || newA.position.x > newB.position.x + newB.size.x
    || newA.position.y + newA.size.y < newB.position.y
    || newA.position.y > newB.position.y + newB.size.y);
}

inline auto DoesDrawAreaFitAnother(const DrawArea &fits, const DrawArea &toFit) -> bool
{
  auto newFits { fits }, newToFit { toFit };
  if (fits.size.unit != Utils::LengthUnits::px)
  {
    const auto conversion = Utils::ConvertLengthUnit(fits.size.unit, Utils::LengthUnits::px);
    newFits.size = {
      static_cast<int32_t>(fits.size.x * conversion),
      static_cast<int32_t>(fits.size.y * conversion)
    };
  }

  if (toFit.size.unit != Utils::LengthUnits::px)
  {
    const auto conversion = Utils::ConvertLengthUnit(toFit.size.unit, Utils::LengthUnits::px);
    newToFit.size = {
      static_cast<int32_t>(toFit.size.x * conversion),
      static_cast<int32_t>(toFit.size.y * conversion)
    };
  }

  return newFits.position.x >= newToFit.position.x
    && newFits.position.x + newFits.size.x <= newToFit.position.x + newToFit.size.x
    && newFits.position.y >= newToFit.position.y
    && newFits.position.y + newFits.size.y <= newToFit.position.y + newToFit.size.y;
}

auto IsPointInDrawArea(
  const DrawArea &area,
  const Position &point,
  bool includeZ) -> bool
{
  if(includeZ && area.position.z != point.z)
    return false;

  const auto conversion = Utils::ConvertLengthUnit(area.size.unit, Utils::LengthUnits::px);
  std::cerr << "conversion: " << conversion << std::endl;
  std::cerr << "area: " << ToString(area) << " point: x: " << point.x << " y: " << point.y << std::endl;
  std::cerr << "area.position.x <= point.x: " << (area.position.x <= point.x)
    << " area.position.x + area.size.x * conversion >= point.x: " << (area.position.x + area.size.x * conversion >= point.x)
    << " area.position.y <= point.y: " << (area.position.y <= point.y)
    << " area.position.y + area.size.y * conversion >= point.y: " << (area.position.y + area.size.y * conversion >= point.y)
    << std::endl;
  return area.position.x <= point.x
    && area.position.x + area.size.x * area.zoom * conversion >= point.x
    && area.position.y <= point.y
    && area.position.y + area.size.y * area.zoom * conversion >= point.y;
}

auto ToString(const DrawArea& drawArea) -> std::string
{
  return std::format(
    "DrawArea: x: {} y: {} z: {} width: {} height: {}, unit: {}, zoom: {}",
    drawArea.position.x,
    drawArea.position.y,
    drawArea.position.z,
    drawArea.size.x,
    drawArea.size.y,
    static_cast<int32_t>(drawArea.size.unit),
    drawArea.zoom);
}

} // namespace Utils