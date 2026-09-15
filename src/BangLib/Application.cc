#include <Application.h>

namespace Bang
{

Application::Application()
  : _sdl {}
  , cardBankComponent {new CardBankComponent}
  , configComponent {new ConfigComponent}
  , contentStorageComponent {new ContentStorageComponent}
  , inputComponent {new InputComponent}
  , renderingComponent{new RenderingComponent}
{

}

} // namespace Bang
