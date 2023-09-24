#ifndef _STATE_GENERATOR_H_
#define _STATE_GENERATOR_H_

#include <MacroUtils.h>
#include <State.h>

namespace Bang
{

class GameState;
template <typename StateMachinType, StateMachinType enumValue>
auto GetNextState(const StatePointer<StateMachinType> &state, const GameState &gameState) -> StatePointer<StateMachinType>
{}

} // namespace Bang

#endif

#define GENERATE_STATE(stateMachineName, stateName)\
  namespace Bang\
  {\
  \
  template <>\
  auto GetNextState<stateMachineName, DOUBLE_COLON_CONCAT_HELPER(stateMachineName, stateName)>(\
    const StatePointer<stateMachineName> &state,\
    const GameState &gameState) -> StatePointer<stateMachineName>;\
  \
  } // namespace Bang\
  \

#include INCLUDE_FILE

#undef GENERATE_STATE