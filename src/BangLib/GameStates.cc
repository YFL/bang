#include <GameStates.h>

#include <GenerateCharacters.h>
#include <DealInitialHand.h>
#include <DrawPhase.h>
#include <PlayPhase.h>
#include <DropPhase.h>

namespace Bang
{

template <>
auto GetNextState(const std::unique_ptr<State<GameStates>> &state, const GameState &GameState) -> std::unique_ptr<State<GameStates>>
{
  switch(state->Type())
  {
    case GameStates::GenerateCharacters:
      return std::unique_ptr<State<GameStates>> {new DealInitialHand};

    case GameStates::DealInitialHand:
      return std::unique_ptr<State<GameStates>> {new PlayPhase};

    case GameStates::PlayPhase:
      return std::unique_ptr<State<GameStates>> {new DropPhase};
    
    case GameStates::DropPhase:
      return std::unique_ptr<State<GameStates>> {new DrawPhase};

    case GameStates::DrawPhase:
      return std::unique_ptr<State<GameStates>> {new PlayPhase};
    
    default:
      return nullptr;
  }
}

} // namespace Bang