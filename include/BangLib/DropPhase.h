#pragma once

#include <GameStates.h>

namespace Bang
{

class DropPhase : public State<GameStates>
{
public:
  DropPhase() = default;

public:
  auto Update(GameState &gameState) -> bool override;

  auto Type() const -> GameStates override
  { return GameStates::DropPhase; }
};

} // namespace Bang