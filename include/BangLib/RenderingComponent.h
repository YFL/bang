#pragma once

#include <InputComponent.h>

#include <Screen.h>
#include <Window.h>

namespace Bang
{

class RenderingComponent
{
public:
  RenderingComponent() = default;
  ~RenderingComponent() = default;
  RenderingComponent(const RenderingComponent &) = delete;
  RenderingComponent(RenderingComponent &&) = delete;

public:
  auto operator=(const RenderingComponent &) -> const RenderingComponent & = delete;
  auto operator=(RenderingComponent &&) -> const RenderingComponent & = delete;

public:
  auto Init(
    const uint32_t windowWidth,
    const uint32_t windowHeight,
    const char *windowTitle,
    const std::unique_ptr<InputComponent> &inputComponent
  ) -> void;

public:
  std::unique_ptr<Utils::Window> window = nullptr;
  std::shared_ptr<Graphics::Screen> screen = nullptr;
};

} // namespace Bang