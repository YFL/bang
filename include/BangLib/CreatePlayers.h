#pragma once

#include "BangLib/GameStates.h"

namespace Bang
{


class CreatePlayers
  : public State<GameStates>
{
public:
  auto Update(GameState &gameState) -> bool override;

  auto Type() const -> GameStates override
  { return GameStates::CreatePlayers; }
};

} // namespace Bang