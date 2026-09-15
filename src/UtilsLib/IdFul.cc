#include <IdFul.h>

#include <format>
#include <iostream>

namespace Utils
{

IdFul::IdFul()
  : Id { xg::newGuid() }
{
  std::cerr << std::format("IdFul: Id: {}", Id.str()) << std::endl;
}

} // namespace Utils