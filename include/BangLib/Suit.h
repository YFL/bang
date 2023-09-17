#pragma once

#include <cstdint>

namespace Bang
{

enum class Suit
  : uint32_t
{
  Spade = 0u,
  Club,
  Heart,
  Diamond,
  NumberOfSuits,
  BlackSuitsEnd = Club,
  RedSuitsEnd = Diamond
};

inline auto IsBlack(Suit s) -> bool
{ return s <= Suit::BlackSuitsEnd; }

inline auto IsRed(Suit s) -> bool
{ return s <= Suit::RedSuitsEnd && s > Suit::BlackSuitsEnd; }

} // namespace Bang