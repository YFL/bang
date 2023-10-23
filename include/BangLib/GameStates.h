#pragma once

#define INCLUDE_FILE <BangLib/GameStates.inc>
#define STATE_MACHINE_NAME GameStates

#include "BangLib/StateEnumGenerator.h"

#include "BangLib/StateGenerator.h"

namespace Bang
{
  
auto GetNextState(const StatePointer<GameStates> &state, const GameState &gameState) -> StatePointer<GameStates>;

} // namespace Bang

#undef INCLUDE_FILE
#undef STATE_MACHINE_NAME