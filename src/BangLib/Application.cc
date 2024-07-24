#include <Application.h>

namespace Bang
{

Application::Application(const uint32_t windowWidth, const uint32_t windowHeight)
  : _sdl {}
  , cardBankComponent {new CardBankComponent}
  , contentStorageComponent {new ContentStorageComponent}
  , inputComponent {new InputComponent}
  , renderingComponent{ new RenderingComponent { windowWidth, windowHeight, inputComponent } }
{

}

} // namespace Bang