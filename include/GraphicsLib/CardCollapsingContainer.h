#pragma once

#include <Positionable.h>

namespace Graphics
{

class CardCollapsingContainer : public Positionable
{
public:
  CardCollapsingContainer(Positionable *parent, const Utils::DrawArea &drawArea)
    : Positionable {parent, drawArea}
  {

  }

protected:
  auto AddChild(Positionable* child) -> void override;

private:
  auto AddCard(Positionable *child) -> void;
};

} // namespace Graphics