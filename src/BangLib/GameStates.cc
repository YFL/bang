#include <GameStates.h>

#include <GenerateCharacters.h>
#include <DealInitialHand.h>
#include <DrawPhase.h>
#include <PlayPhase.h>
#include <DropPhase.h>

namespace Bang
{

auto GetNextState(const std::unique_ptr<State<GameStates>> &state, const GameState &gameState) -> std::unique_ptr<State<GameStates>>
{
  #define GENERATE_STATE(stateMachineName, stateName)\
    case DOUBLE_COLON_CONCAT_HELPER(stateMachineName, stateName):\
      return GetNextState<stateMachineName, DOUBLE_COLON_CONCAT_HELPER(stateMachineName, stateName)>(state, gameState);
  
  switch(state->Type())
  {
    #include <GameStates.inc>
    default:
      return nullptr;
  }
  
  #undef GENERATE_STATE
}

} // namespace Bang