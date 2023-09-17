#include <BangLib/GenerateCharacters.h>
#include <BangLib/GameState.h>
#include <BangLib/GameStates.h>
#include <BangLib/StateManager.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

auto main() -> int
{

  if(SDL_Init(SDL_INIT_EVERYTHING))
  {
    std::cerr << "Couldn't initialize SDL2: " << SDL_GetError() << std::endl;
    return -1;
  }

  if(IMG_Init(IMG_INIT_JPG) != IMG_INIT_JPG)
  {
    std::cerr << "Couldn't initialize SDL2 image: " << IMG_GetError() << std::endl;
    return -1;
  }

  auto *window = SDL_CreateWindow("Bang", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN);
  if(!window)
  {
    std::cerr << "Couldn't create window: " << SDL_GetError() << std::endl;
    return -1;
  }

  auto *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if(!renderer)
  {
    std::cerr << "Couldn't create renderer: " << SDL_GetError() << std::endl;
    return -1;
  }

  auto *surface = IMG_Load("image.jpg");
  if(!surface)
  {
    std::cerr << "Couldn't load image: " << IMG_GetError() << std::endl;
    return -1;
  }

  auto *texture = SDL_CreateTextureFromSurface(renderer, surface);
  if(!texture)
  {
    std::cerr << "Couldn't create texture: " << SDL_GetError() << std::endl;
    return -1;
  }

  Bang::StateManager<Bang::State<GameStates>> stateManager {std::unique_ptr<Bang::GenerateCharacters> {new Bang::GenerateCharacters}};
  Bang::GameState gameState;

  SDL_Event event;
  while(event.type != SDL_QUIT)
  {
    if(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
        break;
      else if(event.type == SDL_KEYDOWN)
      {
        if(event.key.keysym.sym == SDLK_ESCAPE)
        break;
      }
    }

    stateManager.Update(gameState);

    SDL_Rect rect {0, 0, 100, 100};
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(texture);

  SDL_FreeSurface(surface);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  IMG_Quit();
  SDL_Quit();
  return 0;
}