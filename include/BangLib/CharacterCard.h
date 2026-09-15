#pragma once

#include <Card.h>

#include <cstdint>

namespace Bang
{

class CharacterCardComponent : public Utils::Component
{
public:
  CharacterCardComponent(const Utils::EntityPointer &parent, const std::string &description, const uint32_t maxLives)
    : Utils::Component {parent}
    , _description { description }
    , _maxLives { maxLives }
  { }

public:
  auto Description() const -> const std::string &
  {
    return _description;
  }

  auto MaxLives() const -> uint32_t
  {
    return _maxLives;
  }

private:
  const std::string _description = {};
  const uint32_t _maxLives = {};
};

class CharacterCard
  : public Card
{
public:
  CharacterCard(
    const std::string &name,
    const std::string &descrioption,
    SDL_Texture *texture,
    const uint32_t maxLives);
};

} // namespace Bang