#pragma once

#include <SDL2/SDL_ttf.h>

#include <string>
#include <unordered_map>

namespace Bang
{

class ContentStorageComponent
{
public:
  ContentStorageComponent() = default;
  ~ContentStorageComponent();
  ContentStorageComponent(const ContentStorageComponent &) = delete;
  ContentStorageComponent(ContentStorageComponent &&) = delete;

public:
  auto operator=(const ContentStorageComponent &) -> const ContentStorageComponent & = delete;
  auto operator=(ContentStorageComponent &&) -> const ContentStorageComponent & = delete;

public:
  auto AddFont(const std::string &name, TTF_Font *font) -> void
  { _fonts[name] = font; }

  auto GetFont(const std::string &name) const -> TTF_Font *;

  auto Fonts() const -> const std::unordered_map<std::string, TTF_Font *> &
  { return _fonts; }

  auto AddTexture(const std::string &name, SDL_Texture *texture) -> void
  { _textures[name] = texture; }

  auto GetTexture(const std::string &name) const -> SDL_Texture *;

  auto Textures() const -> const std::unordered_map<std::string, SDL_Texture *> &
  { return _textures; }

private:
  std::unordered_map<std::string, TTF_Font *> _fonts;
  std::unordered_map<std::string, SDL_Texture *> _textures;

};
  
} // namespace Bang