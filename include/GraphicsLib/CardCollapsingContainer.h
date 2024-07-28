#pragma once

#include <Positionable.h>

namespace Graphics
{

class CardCollapsingContainer : public Positionable
{
public:
  CardCollapsingContainer(const PositionablePointer &parent, const Utils::DrawArea &drawArea)
    : Positionable {parent, drawArea}
  {

  }

public:
  auto AddChild(const PositionablePointer &child) -> void override;

private:
  auto AddCard(const PositionablePointer &child) -> void;
};

} // namespace Graphics
