#include <Application.h>

namespace Bang
{

Application::Application()
  : contentStorageComponent {new ContentStorageComponent}
  , renderingComponent {new RenderingComponent}
{

}

} // namespace Bang