#pragma once

#include "BangLib/GameStates.h"

namespace Bang
{

class DealInitialHand : public State<GameStates>
{
public:
  DealInitialHand() = default;
  
public:
  auto Update(GameState &gameState) -> bool override;

  auto Type() const -> GameStates override
  { return GameStates::DealInitialHand; }
};

} // namespace Bang