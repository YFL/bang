#pragma once

#include <Positionable.h>

#include <ECS.h>

#include <string>
#include <vector>
#include <memory>

struct SDL_Texture;

namespace Bang
{

class Card
{
public:
  Card(const std::string &name, SDL_Texture *texture, const Utils::TwoDSize &size);

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

  auto Entity() const -> const Utils::EntityPointer
  { return _entity; }

  auto Entity() -> Utils::EntityPointer
  { return _entity; }

private:
  const std::string _name = "";
  //! This is drawn to the screen based on _positionable->GetAbsoluteDrawArea().
  SDL_Texture *_texture = nullptr;
  std::shared_ptr<Utils::Entity> _entity;
};

using CardPointer = std::shared_ptr<Card>;
using CardPointerVector = std::vector<CardPointer>;

} // namespace Bang
