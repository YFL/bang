#include <Renderer.h>

#include <Exception.h>
#include <ImageUtils.h>
#include <TextUtils.h>

namespace Bang
{

Renderer::Renderer(SDL_Window *window, const int32_t renderingDriverIndex , const SDL_RendererFlags flags)
{
  _renderer = {SDL_CreateRenderer(window, renderingDriverIndex, flags), SDL_DestroyRenderer};
  if(!_renderer)
    throw Exception {std::string {"Couldn't create renderer: "} + SDL_GetError()};
}

auto Renderer::ClearRenderer(const SDL_Color &color) const -> void
{
  SetDrawColor(color);
  SDL_RenderClear(_renderer.get());
}

auto Renderer::RenderPresent() const -> void
{
  SDL_RenderPresent(_renderer.get());
}

auto Renderer::RenderTexture(SDL_Texture *texture, const SDL_Rect *source, const SDL_Rect *destination) const -> void
{
  SDL_RenderCopy(_renderer.get(), texture, source, destination);
}

auto Renderer::SetDrawColor(const SDL_Color &color) const -> void
{
  SDL_SetRenderDrawColor(_renderer.get(), color.r, color.g, color.b, color.a);
}

auto Renderer::LoadImageFromJpg(const std::string &pathToFile) const -> SDL_Texture *
{
  return LoadTextureFromJpg(_renderer.get(), pathToFile);
}

auto Renderer::TextToTexture(TTF_Font *font, const std::string &text, const SDL_Color &color) const -> SDL_Texture *
{
  return Bang::TextToTexture(font, _renderer.get(), text, color);
}


} // namespace Bang