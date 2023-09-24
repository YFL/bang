#pragma once

#include <unordered_map>

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

} // namespace Bang


namespace
{

auto suitToString = std::unordered_map<Bang::Suit, std::string> {
  {Bang::Suit::Spade, {"Spade"}},
  {Bang::Suit::Club, {"Club"}},
  {Bang::Suit::Heart, {"Heart"}},
  {Bang::Suit::Diamond, {"Diamond"}}
};

} // namespace 


namespace Bang
{

inline auto IsBlack(Suit s) -> bool
{ return s <= Suit::BlackSuitsEnd; }

inline auto IsRed(Suit s) -> bool
{ return s <= Suit::RedSuitsEnd && s > Suit::BlackSuitsEnd; }

inline auto ToString(const Suit s) -> std::string
{ return ::suitToString[s]; }

} // namespace Bang