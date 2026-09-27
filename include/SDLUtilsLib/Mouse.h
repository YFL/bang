#pragma once

#include <EventEmitter.h>
#include <MouseButtonEvent.h>
#include <MouseMovementEvent.h>
#include <Position.h>
#include <SDL_events.h>

namespace Utils
{

class Mouse
  : public IEventEmitter<MouseButtonEvent>
  , public IEventEmitter<MouseMovementEvent>
  , public IEventHandler<SDL_MouseButtonEvent>
  , public IEventHandler<SDL_MouseMotionEvent>
{
public:
  static constexpr auto leftButton = SDL_BUTTON(SDL_BUTTON_LEFT);
  static constexpr auto middleButton = SDL_BUTTON(SDL_BUTTON_MIDDLE);
  static constexpr auto rightButton = SDL_BUTTON(SDL_BUTTON_RIGHT);

public:
  Mouse()
    : IEventEmitter<MouseButtonEvent>{}
    , IEventEmitter<MouseMovementEvent> {}
  {}

public:
  auto Handle(const SDL_MouseButtonEvent &event) -> void override;
  auto Handle(const SDL_MouseMotionEvent &event) -> void override;

private:
  Position position = {};
};

} // namespace Utils
