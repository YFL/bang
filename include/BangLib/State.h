#pragma once

#include <memory>

namespace Bang
{

class GameState;

template <typename StateMachineType>
class State
{
public:
  State() = default;
  virtual ~State() = default;
  
public:
  /*!
  * @return bool
  *   true - The execution of the state is done, we can move to the next state.
  *   false - The execution of the state is not done, keep this state.
  */
  virtual auto Update(GameState &gameState) -> bool = 0;

  virtual auto Type() const -> StateMachineType = 0;
};

template <typename StateMachineType>
using StatePointer = std::unique_ptr<State<StateMachineType>>;

} // namespace Bang