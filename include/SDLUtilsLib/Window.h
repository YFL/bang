#pragma once

#include <Renderer.h>

#include <SDL.h>

#include <string>

namespace
{

constexpr auto DefaultWindowFlags =
  SDL_WINDOW_OPENGL
  | SDL_WINDOW_BORDERLESS
  | SDL_WINDOW_FULLSCREEN;

} // namespace

namespace Utils
{

class Window
{
public:
  Window(
    uint32_t windowWidth,
    uint32_t windowHeight,
    const std::string &title = "",
    int32_t positionX = SDL_WINDOWPOS_CENTERED,
    int32_t positionY = SDL_WINDOWPOS_CENTERED,
    SDL_WindowFlags flags = static_cast<SDL_WindowFlags>(::DefaultWindowFlags));
  ~Window() = default;
  Window(const Window &) = delete;
  Window(Window &&) = delete;

public:
  auto operator=(const Window &) -> const Window & = delete;
  auto operator=(Window &&) -> const Window & = delete;

public:
  std::unique_ptr<Renderer> renderer = nullptr;

private:
  std::unique_ptr<SDL_Window, void (*)(SDL_Window *)> _window = {nullptr, SDL_DestroyWindow};
};

} // namespace Utils