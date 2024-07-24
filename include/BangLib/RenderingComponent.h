#pragma once

#include <Screen.h>
#include <Window.h>

namespace Bang
{

class RenderingComponent
{
public:
  RenderingComponent(
    const uint32_t windowWidth,
    const uint32_t windowHeight,
    const char *windowTitle,
    std::unique_ptr<InputComponent> &inputComponent);
  ~RenderingComponent() = default;
  RenderingComponent(const RenderingComponent &) = delete;
  RenderingComponent(RenderingComponent &&) = delete;

public:
  auto operator=(const RenderingComponent &) -> const RenderingComponent & = delete;
  auto operator=(RenderingComponent &&) -> const RenderingComponent & = delete;

private:
  std::unique_ptr<Utils::Window> window = nullptr;
  std::shared_ptr<Graphics::Screen> screen = nullptr;
};

} // namespace Bang