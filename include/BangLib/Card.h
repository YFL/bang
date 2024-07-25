#pragma once

#include <Positionable.h>

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

  auto Positionable() const -> Graphics::PositionablePointer
  { return _positionable; }

  auto ToString() const -> std::string
  {
    return _name;
  }

private:
  const std::string _name = "";
  //! This is drawn to the screen based on _positionable->GetAbsoluteDrawArea().
  SDL_Texture *_texture = nullptr;
  //! The card is positioned on the screen based on this.
  Graphics::PositionablePointer _positionable = nullptr;
};

using CardPointer = std::shared_ptr<Card>;
using CardPointerVector = std::vector<CardPointer>;

} // namespace Bang
