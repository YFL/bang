#include <Screen.h>

namespace Graphics
{

auto Screen::Handle(const Utils::MouseButtonEvent &event) -> void
{
  std::cerr << "Screen received MouseButtonEvent" << std::endl;
}

auto Screen::Handle(const Utils::MouseMovementEvent &event) -> void
{
  std::cerr << "Screen received MouseMovementEvent" << std::endl;
}

} // namespace Graphics