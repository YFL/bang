#pragma once

#include <string>
#include <unordered_map>

#include <cstdint>

namespace Bang
{

enum class CardNumber
  : uint32_t
{
  Two = 2,
  Three,
  Four,
  Five,
  Six,
  Seven,
  Eight,
  Nine,
  Ten,
  Jack,
  Queen,
  King,
  Ace,
  // Ace - 1 would be the value of Ace, if Two would be equal to 1,
  // in which case, the value of Ace would correspond to the number of
  // CardNumbers (13 - 1 + 1).
  NumberOfCardNumbers = Ace - 1
};

auto ToString(const CardNumber cardNumber) -> std::string;

} // namespace Bang
