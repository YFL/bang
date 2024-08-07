#include <SDLWrapper.h>

#include <Exception.h>

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>

namespace Utils
{

SDL::SDL()
{
  SDL_SetMainReady();
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

} // namespace Utils