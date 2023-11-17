#pragma once

#include <Positionable.h>

namespace Graphics
{

// Describes a fill window worth of content, that is going to be drawn.
class Screen : public Positionable
{
public:
  Screen(int32_t w, int32_t h)
    : Positionable {nullptr, {{0, 0}, w, h}}
  {}

protected:
  auto ChildAdded(Positionable *child) -> void;

private:
  
};

} // namespace Graphics