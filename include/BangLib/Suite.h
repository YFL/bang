#pragma once

#include <unordered_map>

#include <cstdint>

namespace Bang
{

enum class Suite
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

auto suitToString = std::unordered_map<Bang::Suite, std::string> {
  {Bang::Suite::Spade, {"Spade"}},
  {Bang::Suite::Club, {"Club"}},
  {Bang::Suite::Heart, {"Heart"}},
  {Bang::Suite::Diamond, {"Diamond"}}
};

} // namespace 


namespace Bang
{

inline auto IsBlack(Suite s) -> bool
{ return s <= Suite::BlackSuitsEnd; }

inline auto IsRed(Suite s) -> bool
{ return s <= Suite::RedSuitsEnd && s > Suite::BlackSuitsEnd; }

inline auto ToString(const Suite s) -> std::string
{ return ::suitToString[s]; }

} // namespace Bang