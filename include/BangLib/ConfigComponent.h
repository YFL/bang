#pragma once

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
  auto Init(const PlayerPositionVector &playerPositions) -> void
  { _playerPositions = playerPositions; }

  auto PlayerPositions() const -> PlayerPositionVector
  { return _playerPositions; }

private:
  PlayerPositionVector _playerPositions = {};
};

} // namespace Bang
