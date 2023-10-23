#pragma once

#include "BangLib/GameStates.h"

namespace Bang
{

class PlayPhase : public State<GameStates>
{
public:
  PlayPhase() = default;

public:
  auto Update(GameState &gameState) -> bool override;

  auto Type() const -> GameStates override
  { return GameStates::PlayPhase; }
};

} // namespace Bang