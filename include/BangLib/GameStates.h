#pragma once

#include <StateEnumGenerator.h>
  GENERATE_ENUM(GameStates)
  #include <GameStates.inc>
  NumberOfGameStates
  FINISH_ENUM();
#undef GENERATE_STATE

#include <StateGenerator.h>
  GENERATE_NEXT_STATE_FUNCTION(GameStates)