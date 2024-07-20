#pragma once

#include <Mouse.h>

namespace Bang
{

class InputComponent
{
public:
  InputComponent() = default;
  InputComponent(const InputComponent&) = delete;
  InputComponent(InputComponent&&) = delete;
  ~InputComponent() = default;

public:
  auto operator=(const InputComponent&) -> const InputComponent & = delete;
  auto operator=(InputComponent&&) -> const InputComponent & = delete;

public:
  Utils::Mouse mouse = {};
};

} // namespace Bang