#pragma once

#include <Positionable.h>

#include <EventHandler.h>
#include <MouseButtonEvent.h>
#include <MouseMovementEvent.h>

namespace Graphics
{

// Describes a full window worth of content, that is going to be drawn.
class Screen
  : public Positionable
  , public Utils::IEventHandler<Utils::MouseButtonEvent>
  , public Utils::IEventHandler<Utils::MouseMovementEvent>
{
public:
  Screen(int32_t w, int32_t h)
    : Positionable {nullptr, {{0, 0}, w, h}}
    , Utils::IEventHandler<Utils::MouseButtonEvent> {}
    , Utils::IEventHandler<Utils::MouseMovementEvent> {}
  {}

public:
  auto Handle(const Utils::MouseButtonEvent &event) -> void override;
  auto Handle(const Utils::MouseMovementEvent &event) -> void override;

protected:
  auto ChildAdded(Positionable *child) -> void;

private:
  
};

} // namespace Graphics