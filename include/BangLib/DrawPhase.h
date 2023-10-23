#pragma once

#include "BangLib/GameStates.h"

namespace Bang
{

class DrawPhase : public State<GameStates>
{
public:
  DrawPhase() = default;

public:
  auto Update(GameState &gameState) -> bool override;

  auto Type() const -> GameStates override
  { return GameStates::DrawPhase; }
};

} // namespace Bang