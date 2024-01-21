#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <memory>

namespace
{

constexpr auto DefaultRendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

} // namespace 

namespace Bang
{

class Renderer
{
public:
  Renderer(
    SDL_Window *window,
    const int32_t renderingDriverIndex = -1,
    const SDL_RendererFlags flags = static_cast<SDL_RendererFlags>(::DefaultRendererFlags));
  ~Renderer() = default;
  Renderer(const Renderer &) = delete;
  Renderer(Renderer &&) = delete;

public:
  auto operator=(const Renderer &) -> const Renderer & = delete;
  auto operator=(Renderer &&) -> const Renderer & = delete;

public:
  auto ClearRenderer(const SDL_Color &color) const -> void;
  auto RenderPresent() const -> void;
  auto RenderTexture(SDL_Texture *texture,
    const SDL_Rect *source,
    const SDL_Rect *destination) const
    -> void;
  auto SetDrawColor(const SDL_Color &color) const -> void;
  auto LoadImageFromJpg(const std::string &pathToFile) const -> SDL_Texture *;
  auto TextToTexture(
    TTF_Font *font,
    const std::string &text,
    const SDL_Color &color) const
    -> SDL_Texture *;

private:
  std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)> _renderer =
  {nullptr, SDL_DestroyRenderer};
};

} // namespace Bang