#pragma once

#include <Card.h>

#include <Positionable.h>

#include <MouseButtonEvent.h>
#include <MouseMovementEvent.h>

namespace Bang
{

struct CardHovered
{
  CardWeakPtr card;
};

struct CardSelected : public CardHovered {};

class CardCollapsingContainer
  : public Graphics::Positionable
  , public Utils::IEventEmitter<CardSelected>
  , public Utils::IEventEmitter<CardHovered>
  , public Utils::IEventHandler<Utils::MouseButtonEvent>
  , public Utils::IEventHandler<Utils::MouseMovementEvent>
{
public:
  CardCollapsingContainer(
    const Graphics::PositionablePointer &parent,
    const Utils::DrawArea &drawArea)
    : Graphics::Positionable {nullptr, parent, drawArea}
  {

  }

public:
  auto AddCard(const Bang::CardWeakPtr &card) -> void;

public:
  auto Handle(const Utils::MouseButtonEvent &event) -> void override;
  auto Handle(const Utils::MouseMovementEvent &event) -> void override;

protected:
  CardWeakPtrVector _cards = {};
  CardWeakPtr _hoveredChild = {};
};

} // namespace Graphics
