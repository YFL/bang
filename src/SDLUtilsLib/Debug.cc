#include <Debug.h>

#include <SDL.h>

namespace Utils
{

auto DrawDebugRect(
  const std::unique_ptr<Renderer>& renderer,
  const SDL_Rect& rect,
  const SDL_Color& color) -> void
{
  renderer->SetDrawColor(color);
  renderer->DrawRectangle(rect);
}

} // namespace Utils