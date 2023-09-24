#pragma once

#include <Exception.h>
#include <GameStates.h>

#include <iostream>
#include <memory>

namespace Bang
{

template <typename StateType>
class StateManager
{
public:
  StateManager(std::unique_ptr<StateType> &&initialState)
  {
    if(!initialState)
      throw Exception {"Couldn't initialize StateManager with null initial state"};
    
    _state = std::move(initialState);
  }

public:
  auto Update(GameState &gameState) -> void
  {
    if(!_state)
      return;

    if(!_state->Update(gameState))
    {
      std::cerr << "Update finished. Setting new state." << std::endl;
      _state = GetNextState(_state, gameState);
      std::cerr << "New state set." << std::endl;
    }
  }

private:
  std::unique_ptr<StateType> _state = nullptr;
};

} // namespace Bang