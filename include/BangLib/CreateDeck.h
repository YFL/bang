#pragma once

#include <GameStates.h>

namespace Bang
{

class CreateDeck
  : public State<GameStates>
{
public:
  auto Update(GameState &gameState) -> bool override;
  auto Type() const -> GameStates override
  {
    return GameStates::CreateDeck;
  }
};

} // namespace Bang