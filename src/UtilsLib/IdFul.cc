#include <IdFul.h>

namespace Utils
{

uint64_t IdFul::NextId = 0u;

IdFul::IdFul()
  : Id{ NextId++ }
{}

} // namespace Utils