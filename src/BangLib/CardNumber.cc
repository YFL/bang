#include <CardNumber.h>

#include <string>

namespace
{

const std::unordered_map<Bang::CardNumber, std::string> cardNumberToString {
  {Bang::CardNumber::Two, "Two"},
  {Bang::CardNumber::Three, "Three"},
  {Bang::CardNumber::Four, "Four"},
  {Bang::CardNumber::Five, "Five"},
  {Bang::CardNumber::Six, "Six"},
  {Bang::CardNumber::Seven, "Seven"},
  {Bang::CardNumber::Eight, "Eight"},
  {Bang::CardNumber::Nine, "Nine"},
  {Bang::CardNumber::Ten, "Ten"},
  {Bang::CardNumber::Jack, "Jack"},
  {Bang::CardNumber::Queen, "Queen"},
  {Bang::CardNumber::King, "King"},
  {Bang::CardNumber::Ace, "Ace"}
};

} // namespace

namespace Bang
{

auto ToString(const CardNumber cardNumber) -> std::string
{
  const auto it = ::cardNumberToString.find(cardNumber);
  if(it == ::cardNumberToString.cend())
  {
    return "Unkown card number";
  }

  return it->second;
}

} // namespace Bang