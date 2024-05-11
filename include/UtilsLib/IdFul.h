#pragma once

#include <cstdint>

namespace Utils
{

class IdFul
{
private:
  static uint64_t NextId;

public:
  IdFul();

public:
  const uint64_t Id;
};

} // namespace Utils