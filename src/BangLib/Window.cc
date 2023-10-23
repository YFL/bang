#include "BangLib/Window.h"

#include "BangLib/Exception.h"

#include <memory>
#include <string>

namespace Bang
{

Window::Window(
  const uint32_t windowWidth
  , const uint32_t windowHeight
  , const std::string &title
  , const int32_t positionX
  , const int32_t positionY
  , const SDL_WindowFlags flags)
{
  _window = std::unique_ptr<SDL_Window, void (*)(SDL_Window *)>
  {
    SDL_CreateWindow(title.c_str(), positionX, positionY, windowWidth, windowHeight, flags)
    , SDL_DestroyWindow
  };

  if(!_window)
    throw Exception {"Couldn't create window \"" + title + "\": " + SDL_GetError()};

  renderer = std::unique_ptr<Renderer> {new Renderer {_window.get()}};
}

} // namespace Bang