#pragma once

#include <CardCollapsingContainer.h>
#include <MouseButtonEvent.h>
#include <MouseMovementEvent.h>

namespace Bang
{

class CardCollapsingHoveredHighlightingContainer
  : public CardCollapsingContainer
  , Utils::IEventHandler<CardHovered>
{
public:
  CardCollapsingHoveredHighlightingContainer(
    const Graphics::PositionablePointer &parent,
    const Utils::DrawArea &area)
    : CardCollapsingContainer(parent, area)
  {

  }

public:
  auto Handle(const CardHovered &event) -> void override;

public:


private:
  CardWeakPtr _zoomedChild = {};
};

} // namespace Bang
