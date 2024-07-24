#pragma once

#include <CardBankComponent.h>
#include <ContentStorageComponent.h>
#include <InputComponent.h>
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

private:
  Application(uint32_t windowWidth, uint32_t windowHeight);
  ~Application() = default;
  Application(const Application &) = delete;
  Application(Application &&) = delete;


private:
  auto operator=(const Application &) -> const Application & = delete;
  auto operator=(Application &&) -> const Application & = delete;

private:
  // This has to be higher than the components, because the contentStorageComponent
  // frees the fonts and if TTF_Close is called before that, it causes a
  // segmentation fault.
  Utils::SDL _sdl = {};

public:
  const std::unique_ptr<CardBankComponent> cardBankComponent = nullptr;
  const std::unique_ptr<ContentStorageComponent> contentStorageComponent = nullptr;
  const std::unique_ptr<InputComponent> inputComponent = nullptr;
  const std::unique_ptr<RenderingComponent> renderingComponent = nullptr;
};

} // namespace Bang