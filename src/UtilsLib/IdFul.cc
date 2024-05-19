#include <IdFul.h>

#include <format>
#include <iostream>

namespace Utils
{

uint64_t IdFul::NextId = 0u;

IdFul::IdFul()
  : Id{ NextId++ }
{
  std::cerr << std::format("IdFul: Id: {} NextId: {}", Id, NextId) << std::endl;
}

} // namespace Utils