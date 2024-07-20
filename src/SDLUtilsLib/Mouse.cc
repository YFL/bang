#include <Mouse.h>

#include <SDL.h>

namespace Utils
{

auto Mouse::Handle(const SDL_MouseButtonEvent & event) -> void
{
  std::cerr << this << " Mouse emitting Button event" << std::endl;
  position = Position { event.x, event.y, 0 };
  IEventEmitter<MouseButtonEvent>::Emit(
    {
      event.button,
      static_cast<bool>(event.state),
      event.clicks,
      position
    });
}

auto Mouse::Handle(const SDL_MouseMotionEvent &event) -> void
{
  std::cerr << this << " Mouse emitting Motion event" << std::endl;
  position = { event.x, event.y, 0 };
  IEventEmitter<MouseMovementEvent>::Emit(
    {
      position,
      {
        event.xrel,
        event.yrel,
        0
      }
    });
}

} // namespace Utils