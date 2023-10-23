#pragma once

#include "BangLib/GameStates.h"

namespace Bang
{

class SwitchPlayers
  : public State<GameStates>
{
public:
  auto Update(GameState &gameState) -> bool;

public:
  auto Type() const -> GameStates
  { return GameStates::SwitchPlayers; }
};

} // namespace Bang