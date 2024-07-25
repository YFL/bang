#pragma once

#include <CardCollapsingContainer.h>
#include <MouseMovementEvent.h>

namespace Graphics
{

class CardCollapsingHoveredHighlightingContainer
  : public CardCollapsingContainer
  , public Utils::IEventHandler<Utils::MouseMovementEvent>
{
public:
  CardCollapsingHoveredHighlightingContainer(
    const PositionablePointer &parent,
    const Utils::DrawArea &area)
    : CardCollapsingContainer(parent, area)
  {

  }

public:
  auto Handle(const Utils::MouseMovementEvent &event) -> void override;
};

} // namespace Graphics
