#pragma once

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
  std::unique_ptr<Utils::Window> window = nullptr;
};

} // namespace Bang