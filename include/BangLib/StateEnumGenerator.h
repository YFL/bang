#pragma once

#include <cstdint>

#define GENERATE_STATE(stateMachineName, stateName)\
stateName,

#define GENERATE_ENUM(enumName)\
enum class enumName : uint32_t\
{\

#define FINISH_ENUM()\
};