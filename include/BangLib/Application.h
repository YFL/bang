#pragma once

#include <ContentStorageComponent.h>
#include <RenderingComponent.h>
#include <SDL.h>

#include <memory>

namespace Bang
{

class Application
{
public:
  static auto Get() -> Application &
  {
    static Application app;
    return app;
  }

public:
  ~Application() = default;

private:
  Application();
  Application(const Application &) = delete;
  Application(Application &&) = delete;

private:
  auto operator=(const Application &) -> const Application & = delete;
  auto operator=(Application &&) -> const Application & = delete;

public:
  const std::unique_ptr<ContentStorageComponent> contentStorageComponent = nullptr;
  const std::unique_ptr<RenderingComponent> renderingComponent = nullptr;

private:
  SDL sdl = {};
};

} // namespace Bang