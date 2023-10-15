#include <TextUtils.h>

namespace Bang
{

auto LoadFontFromFile(const std::string &pathToFIle, const uint32_t fontSize ) -> TTF_Font *
{
  auto *font = TTF_OpenFont(pathToFIle.c_str(), fontSize);
  if(!font)
  {
    std::cerr << "Couldn't open font \"" << pathToFIle << "\": " << TTF_GetError() << std::endl;
    return nullptr;
  }

  return font;
}

auto TextToTexture(TTF_Font *font, SDL_Renderer* renderer, const std::string &text, const SDL_Color &color) -> SDL_Texture *
{
  auto *surface = TTF_RenderText_Solid(font, text.c_str(), color);
  if(!surface)
  {
    std::cerr << "Couldn't render text \"" << text << "\": " << TTF_GetError() << std::endl;
    return nullptr;
  }

  auto *texture = SDL_CreateTextureFromSurface(renderer, surface);
  if(!texture)
  {
    std::cerr << "Couldn't create texture for text \"" << text << "\": " << SDL_GetError() << std::endl;
    return nullptr;
  }

  return texture;
}

} // namespace Bang