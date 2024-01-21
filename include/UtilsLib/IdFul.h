#pragma once

#include <cstdint>

namespace Utils
{

class IdFul
{
private:
  static uint64_t Id;
public:
  IdFul()
    : id {Id++}
  {}

public:
  uint64_t id;
};

} // namespace Utils