#pragma once

#include <2dSize.h>
#include <DrawArea.h>

#include <vector>

namespace Bang
{

using PlayerPositionVector = std::vector<Utils::DrawArea>;

class ConfigComponent
{
public:
  ConfigComponent() = default;
  ConfigComponent(const ConfigComponent &copy) = default;
  ConfigComponent(ConfigComponent &&move) = default;

public:
  auto operator=(const ConfigComponent &copy) -> ConfigComponent & = default;
  auto operator=(ConfigComponent &&move) -> ConfigComponent & = default;

public:
  auto Init(
    const PlayerPositionVector &playerPositions,
    const Utils::TwoDSize &cardSize,
    const uint32_t firstCardToScreenLeftOffset,
    const uint32_t maxCardsNextToEachOtherWithoutOverlapping) -> void
  { 
    _playerPositions = playerPositions;
    _cardSize = cardSize;
    _firstCardToScreenLeftOffset = firstCardToScreenLeftOffset;
    _maxCardsNextToEachOtherWithoutOverlapping = maxCardsNextToEachOtherWithoutOverlapping;
  }

  auto PlayerPositions() const -> PlayerPositionVector
  { return _playerPositions; }

  auto CardSize() const -> Utils::TwoDSize
  { return _cardSize; }

  auto FirstCardToScreenLeftOffset() const -> uint32_t
  { return _firstCardToScreenLeftOffset; }

  auto MaxCardsNextToEachOtherWithoutOverlapping() const -> uint32_t
  { return _maxCardsNextToEachOtherWithoutOverlapping; }

private:
  PlayerPositionVector _playerPositions = {};
  Utils::TwoDSize _cardSize = {};
  uint32_t _firstCardToScreenLeftOffset = 0;
  uint32_t _maxCardsNextToEachOtherWithoutOverlapping = 0;
};

} // namespace Bang
