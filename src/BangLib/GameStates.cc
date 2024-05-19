#include <GameStates.h>

namespace Bang
{

auto GetNextState(const StatePointer<GameStates> &state, const GameState &gameState)
  -> StatePointer<GameStates>
{
  #define GENERATE_STATE(stateMachineName, stateName)\
    case DOUBLE_COLON_CONCAT_HELPER(stateMachineName, stateName):\
      return GetNextState<\
        stateMachineName,\
        DOUBLE_COLON_CONCAT_HELPER(stateMachineName, stateName)>\
        (state, gameState);
  
  switch(state->Type())
  {
    #include <GameStates.inc>
    default:
      return nullptr;
  }
  
  #undef GENERATE_STATE
}

} // namespace Bang