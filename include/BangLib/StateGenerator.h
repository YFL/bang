#pragma once

#include <memory>

namespace Bang
{

template <typename StateMachineType>
class State;
class GameState;
template <typename StateType>
auto GetNextState(const std::unique_ptr<StateType> &state, const GameState &gameState) -> std::unique_ptr<StateType>
{}

} // namespace Bang

#define GENERATE_NEXT_STATE_FUNCTION(stateMachineName)\
  namespace Bang\
  {\
  \
  template <>\
  auto GetNextState(const std::unique_ptr<State<stateMachineName>> &state, const GameState &gameState) -> std::unique_ptr<State<stateMachineName>>;\
  \
  } // namespace Bang\
  \
