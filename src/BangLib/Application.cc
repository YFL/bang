#include "BangLib/Application.h"

namespace Bang
{

Application::Application()
  : _sdl {}
  , contentStorageComponent {new ContentStorageComponent}
  , cardBankComponent {new CardBankComponent}
  , renderingComponent {new RenderingComponent}
{

}

} // namespace Bang