#pragma once

#include <Position.h>
#include <SDL.h>

#include <string>

#include <cstdint>

namespace Utils
{

struct DrawArea
{
  Position position;
  int32_t w;
  int32_t h;
};

//! @brief Get the "absolute" draw area of b relative to a.
//!
//! The size of the draw area is gotten from b. The position is simply
//! a.position + b.position.
//! @param a The draw area that contains the other draw area. This is the area
//!   that the other area's position is relative to.
//! @param b The draw area whose position we are interested in.
//!   It's position should be relative to a.
//! @return The absolute draw area of b with respect to a. The size of the
//!   draw area is the size of b.
inline auto operator+ (const DrawArea &a, const DrawArea &b) -> DrawArea
{ return { {a.position.x + b.position.x, a.position.y + b.position.y}, b.w, b.h }; }

inline auto operator== (const DrawArea &a, const DrawArea &b) -> bool
{ return a.position == b.position && a.w == b.w && a.h == b.h; }

inline auto DoDrawAreasCollide(const DrawArea &a, const DrawArea &b, bool includeZ = false) -> bool;

inline auto DoesDrawAreaFitAnother(const DrawArea &fits, const DrawArea &toFit) -> bool;

inline auto DrawAreaToSDLRect(const DrawArea &drawArea) -> SDL_Rect
{
  return { drawArea.position.x, drawArea.position.y, drawArea.w, drawArea.h };
}

/**
 * Returns whether a point is inside of the draw area
*/
auto IsPointInDrawArea(
  const DrawArea &area,
  const Position &point,
  bool includeZ = false)
  -> bool;

auto ToString(const DrawArea& drawArea) -> std::string;

} // namespace Utils