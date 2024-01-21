#include <SDL.h>

#include <Exception.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

namespace Bang
{

SDL::SDL()
{
  if(SDL_Init(SDL_INIT_EVERYTHING))
  {
    throw Utils::Exception {std::string("Couldn't initialize SDL2: ") + SDL_GetError()};
  }

  if(IMG_Init(IMG_INIT_JPG) != IMG_INIT_JPG)
  {
    throw Utils::Exception {std::string("Couldn't initialize SDL2 image: ") + IMG_GetError()};
  }

  if(TTF_Init() == -1)
  {
    throw Utils::Exception {std::string("Couldn't initialize SDL2 ttf: ") + TTF_GetError()};
  }
}

SDL::~SDL()
{
  std::cout << "Destructing SDL" << std::endl;
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

} // namespace Bang