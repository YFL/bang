#pragma once

#include <CardBankComponent.h>
#include <ContentStorageComponent.h>
#include <RenderingComponent.h>
#include <SDLWrapper.h>

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

private:
  // This has to be higher than the components, because the contentStorageComponent
  // frees the fonts and if TTF_Close is called before that, it causes a
  // segmentation fault.
  SDL _sdl = {};

public:
  const std::unique_ptr<ContentStorageComponent> contentStorageComponent = nullptr;
  const std::unique_ptr<CardBankComponent> cardBankComponent = nullptr;
  const std::unique_ptr<RenderingComponent> renderingComponent = nullptr;
};

} // namespace Bang