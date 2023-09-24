#pragma once

#include <string>
#include <vector>
#include <memory>

struct SDL_Texture;

namespace Bang
{

class Card
{
public:
  Card(const std::string &name, SDL_Texture *texture);

public:
  operator std::string () const
  { return _name; }

public:
  auto Name() const -> const std::string &
  { return _name; }

  auto Texture() const -> SDL_Texture *
  { return _texture; }

  auto ToString() const -> std::string
  {
    return _name;
  }

private:
  const std::string _name = "";
  SDL_Texture *_texture = nullptr;
};

using CardPointer = std::shared_ptr<Card>;
using CardPointerVector = std::vector<CardPointer>;

} // namespace Bang