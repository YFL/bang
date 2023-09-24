#pragma once

#include <Card.h>

namespace Bang
{

auto LoadFromFile(const std::string &pathToFile) -> CardPointerVector;

} // namespace Bang