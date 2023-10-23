#pragma once

#include "BangLib/GameStates.h"

namespace Bang
{

class GenerateCharacters : public State<GameStates>
{
public:
  GenerateCharacters() = default;

public:
  auto Update(GameState &gameState) -> bool override;

  auto Type() const -> GameStates override
  { return GameStates::GenerateCharacters; }
};

} // namespace Bang