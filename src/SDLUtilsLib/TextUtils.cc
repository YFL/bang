#include <TextUtils.h>

#include <format>

namespace Utils
{

auto LoadFontFromFile(const std::string &pathToFile, const uint32_t fontSize ) -> TTF_Font *
{
  auto *font = TTF_OpenFont(pathToFile.c_str(), fontSize);
  if(!font)
  {
    std::cerr
      << std::format("Couldn't open font \"{}\": {}", pathToFile.c_str(), TTF_GetError())
      << std::endl;

    return nullptr;
  }

  return font;
}

auto TextToTexture(
  TTF_Font *font,
  SDL_Renderer* renderer,
  const std::string &text,
  const SDL_Color &color)
  -> SDL_Texture *
{
  auto *surface = TTF_RenderText_Solid(font, text.c_str(), color);
  if(!surface)
  {
    std::cerr << std::format("Couldn't render text \"{}\": {}", text, TTF_GetError()) << std::endl;
    return nullptr;
  }

  auto *texture = SDL_CreateTextureFromSurface(renderer, surface);
  if(!texture)
  {
    std::cerr
      << std::format("Couldn't create texture for text \"{}\": {}", text, SDL_GetError())
      << std::endl;

    return nullptr;
  }

  return texture;
}

} // namespace Utils