#include <RenderingComponent.h>

#include <InputComponent.h>

namespace Bang
{

auto RenderingComponent::Init(
  const uint32_t windowWidth,
  const uint32_t windowHeight,
  const char *windowTitle,
  const std::unique_ptr<InputComponent> &inputComponent) -> void
{
  std::cout << "Creating window." << std::endl;
  window = std::unique_ptr<Utils::Window> {
    new Utils::Window { windowWidth, windowHeight, windowTitle }};

  std::cout << "Creating screen." << std::endl;
  screen = std::make_shared<Graphics::Screen>(windowWidth, windowHeight);

  auto *mouse = &(inputComponent->mouse);
  // Static cast didn't work here and I'm not sure why.
  dynamic_cast<Utils::IEventEmitter<Utils::MouseButtonEvent> *>(mouse)->RegisterHandler(screen);
  dynamic_cast<Utils::IEventEmitter<Utils::MouseMovementEvent> *>(mouse)->RegisterHandler(screen);
}

} // namespace Bang