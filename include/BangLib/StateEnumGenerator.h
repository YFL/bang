#ifndef _STATE_ENUM_GENERATOR_H_
#define _STATE_ENUM_GENERATOR_H_

#include <cstdint>

#endif

#define GENERATE_STATE(stateMachineName, stateName)\
stateName,

#define NUMBER_OF_ENUM_MEMBER NumberOf##STATE_MACHINE_NAME

enum class STATE_MACHINE_NAME : uint32_t
{
  #include INCLUDE_FILE
  NUMBER_OF_ENUM_MEMBER
};

#undef GENERATE_STATE