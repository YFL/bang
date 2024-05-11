#pragma once

#include <Positionable.h>

namespace Graphics
{

class CardCollapsingContainer : public Positionable
{
public:
  CardCollapsingContainer(Positionable *parent, const DrawArea &drawArea)
    : Positionable {parent, drawArea}
  {

  }

public:
  auto AddCard(Positionable *child) -> void;
};

} // namespace Graphics